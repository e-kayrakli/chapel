#include "chplrt.h"
#include "chpl-al-prefetch.h"
#include "chpl-comm.h"
#include "chpl-tasks.h"
#include "chpl-mem.h"
#include "chpl-atomics.h"
#include "chpl-thread-local-storage.h" // CHPL_TLS_DECL etc
#include "chpl-cache.h"
#include "chpl-linefile-support.h"
#include "sys.h" // sys_page_size()
#include "chpl-comm-no-warning-macros.h" // No warnings for chpl_comm_get etc.
/*#include "chpl-cache-support.c"*/

#include <string.h> // memcpy, memset, etc.
#include <assert.h>

// ----------  SUPPORT FUNCTIONS 
// directly taken from chpl-cache-support.c to avoid including a whole c
// file
#define NO_SEQUENCE_NUMBER 0
static inline
cache_seqn_t seqn_min(cache_seqn_t a, cache_seqn_t b)
{
  if( a != NO_SEQUENCE_NUMBER && a < b ) return a;
  return b;
}
static inline
cache_seqn_t seqn_max(cache_seqn_t a, cache_seqn_t b)
{
  if( a != NO_SEQUENCE_NUMBER && a > b ) return a;
  return b;
}

chpl_prefetch_taskPrvData_t* task_private_prefetch_data(void)
{
  chpl_task_prvData_t* task_local = chpl_task_getPrvData();
  return &task_local->comm_data.prefetch_data;
}

//these locks are managed from PrefetchHooks
static inline
void start_read(struct __prefetch_entry_t *entry, int page_idx) {
  //assert entry?
  //we only need to lock if the entry is marked consistent
  //we are assuming that the user will call updatePrefetch only from a
  //sequential context from one locale, similar to our assumption that
  //data will be prefetch only from single task from one locale

#if USE_CUSTOM_SYNCH
  uint_least32_t *state_addr = &(entry->states[page_idx]);

  if(atomic_compare_exchange_strong_explicit_uint_least32_t(state_addr,
        PF_PAGE_IDLE, PF_PAGE_SINGLE_READER, _defaultOfMemoryOrder())){
    // page was idle, it is now single reader
    /*printf("First reader\n");*/
  }
  else {
    while(atomic_compare_exchange_strong_explicit_uint_least32_t(state_addr,
          PF_PAGE_SINGLE_WRITER, PF_PAGE_SINGLE_WRITER, _defaultOfMemoryOrder())){
      // there was a writer and there still is
      /*printf("\t waiting for write\n");*/
      chpl_task_yield();
    }
    // I will be one of the many readers
    /*printf("Non-first reader\n");*/
    atomic_fetch_add_explicit_uint_least32_t(state_addr, 1,
        _defaultOfMemoryOrder());
  }
  /*printf("Acquired read lock\n");*/
#else
  while(pthread_rwlock_tryrdlock(&(entry->rwl[page_idx])))
    chpl_task_yield();
#endif
}

static inline
void stop_read(struct __prefetch_entry_t *entry, int page_idx) {
  //assert entry?
#if USE_CUSTOM_SYNCH
  uint_least32_t *state_addr = &(entry->states[page_idx]);
  if(atomic_compare_exchange_strong_explicit_uint_least32_t(state_addr,
        PF_PAGE_SINGLE_READER, PF_PAGE_IDLE, _defaultOfMemoryOrder())){
  }
  else {
    atomic_fetch_sub_explicit_uint_least32_t(state_addr, 1,
        _defaultOfMemoryOrder());
  }
  /*printf("Released read lock\n");*/
#else
  pthread_rwlock_unlock(&(entry->rwl[page_idx]));
#endif
}

static inline
void start_update(struct __prefetch_entry_t *entry, int page_idx) {

  //this is currently only called from a context where we check if the
  //entry is marked consistent, so I am not repeating that check here
  /*bool done = false;*/
  /*do {*/
    /*chpl_sync_lock(entry->state_lock);*/
    /*if(entry->state_counter == 0){*/
      /*entry->state_counter = -1;*/
      /*done = true;*/
      /*//the lock should be unlocked by stop_update*/
      /*[>printf("%d Started update\n", chpl_nodeID);<]*/
    /*}*/
    /*else {*/
      /*// we only unlock if we weren't able to start the update*/
      /*chpl_sync_unlock(entry->state_lock);*/
      /*chpl_task_yield();*/
    /*}*/
  /*} while(!done);*/

#if USE_CUSTOM_SYNCH
  int i,j;
  for(j = 0, i = page_idx ; j < entry->page_count ; j++, i=page_idx+j) {
    uint_least32_t *state_addr = &(entry->states[i]);
    if(atomic_compare_exchange_strong_explicit_uint_least32_t(state_addr,
          PF_PAGE_SINGLE_WRITER, PF_PAGE_SINGLE_WRITER, _defaultOfMemoryOrder())){
      /*printf("Writer writer contention\n");*/
    }
    while(!atomic_compare_exchange_strong_explicit_uint_least32_t(state_addr,
          PF_PAGE_IDLE, PF_PAGE_SINGLE_WRITER, _defaultOfMemoryOrder())){
      chpl_task_yield();
    }
  }
  /*printf("Acquired write lock\n");*/
#else
  int i;
  for(i = 0 ; i < entry->page_count ; i++) {
    while(pthread_rwlock_trywrlock(&(entry->rwl[i]))) {
      chpl_task_yield();
    }
    /*printf("%d locked %p\n", chpl_nodeID, &(entry->rwl[i]));*/
  }
#endif
}

static inline
void stop_update(struct __prefetch_entry_t *entry, int page_idx) {
  // here we are assuming that state_counter is -1 and there is
  // definitely no readers in the entry
  /*assert(entry->state_counter == -1);*/
  /*entry->state_counter = 0;*/
  /*chpl_sync_unlock(entry->state_lock);*/
#if USE_CUSTOM_SYNCH
  int i;
  for(i = 0 ; i < entry->page_count ; i++) {
    uint_least32_t *state_addr = &(entry->states[i]);
    atomic_store_explicit_uint_least32_t(state_addr,
        PF_PAGE_IDLE, _defaultOfMemoryOrder());
  }
  /*printf("Released write lock\n");*/
#else
  int i;
  for(i = 0 ; i < entry->page_count ; i++) {
    /*printf("%d unlocking %p\n", chpl_nodeID, &(entry->rwl[i]));*/
    pthread_rwlock_unlock(&(entry->rwl[i]));
  }
#endif
}

extern uint64_t __get_byte_idx_wrapper(void*, void*, void*);
// FIXME how de store pbuf, global or pass as argument
static
void remove_from_prefetch_buffer(struct prefetch_buffer_s* pbuf,
    struct __prefetch_entry_t *entry) {
  assert(pbuf);
  if(entry->prev) {
    entry->prev->next = entry->next;
  }
  else {
    assert(pbuf->head == entry);
    pbuf->head = entry->next;
  }
  if(entry->next) {
    entry->next->prev = entry->prev;
  }


  chpl_free(entry->data);
  entry->data = NULL;
  chpl_free(entry->slice_desc); // ..ugh
  chpl_free(entry);
  entry = NULL;
}

void chpl_prefetch_comm_get_fast(void *addr, c_nodeid_t node, void*
    raddr, size_t size, int32_t typeIndex, int ln, int32_t fn) {

  /*struct prefetch_buffer_s* pbuf = tls_prefetch_remote_data();*/
  if (chpl_verbose_comm) 
    printf("%d: %s:%d: remote put to (chpl_prefetch_comm_get) %d %p\n",
        chpl_nodeID, chpl_lookupFilename(fn), ln, node, raddr);

  memcpy(addr, pbuf->fast_access_addr, size);
}

void* get_data_from_prefetch_entry(struct __prefetch_entry_t *entry) { assert(entry);
  if(entry)
    return entry->data;
  else
    return NULL;
}

static
void chpl_prefetch_do_init(void)
{
  static int inited = 0;
  if( ! inited ) {
    pbuf = chpl_malloc(sizeof(struct prefetch_buffer_s));
    pbuf->head = NULL;
    pbuf->min_task_seqn = 0;
    chpl_sync_initAux(&(pbuf->update_lock));
    pbuf->being_updated = false;
    inited = 1;
  }
}

static
void prefetch_destroy(struct prefetch_buffer_s *pbuf) {

  struct __prefetch_entry_t *cur = pbuf->head;
  struct __prefetch_entry_t *next = NULL;

  while(cur) {
    next = cur->next;
    /*printf("Hello!\n");*/
    chpl_free(cur->data);
    chpl_free(cur);
    cur = next;
  }
  chpl_free(pbuf);
}
void chpl_prefetch_init(void) {

  chpl_prefetch_do_init();
}

void chpl_prefetch_exit(void)
{
   prefetch_destroy(pbuf);
}

void get_prefetched_data(void *accessor,
    struct __prefetch_entry_t* prefetch_entry, size_t size, void* idx,
    int64_t* found, void *dest) {

}

#define LOG_IDX 0

void *get_prefetched_data_addr(void *accessor,
    struct __prefetch_entry_t* prefetch_entry, size_t size, void* idx,
    int64_t* back_link_offset) {

  int64_t offset; //this can be negative in current logic
  void *retaddr=NULL;

  if(!prefetch_entry) {
    return NULL;
  }

  offset = (int64_t)(__get_byte_idx_wrapper(accessor,
        prefetch_entry->data, idx));

  // NULL check for prefetch entry has been handled by PrefethcHooks
  if(offset < 0 ||
      (intptr_t)size > ((intptr_t)prefetch_entry->size)-offset) {
    /*DEBUG_PRINT(("\t offset=%ld, size=%zd, origin=%d, entry_size=%zd\n",*/
        /*offset, size, prefetch_entry->origin_node,*/
        /*prefetch_entry->size));*/
    /**found = 0;*/
  }
  else {
    *back_link_offset = -offset-sizeof(struct __prefetch_entry_t *);
    /*DEBUG_PRINT(("%ld %ld %ld FOUND > offset=%ld, entry_size=%zd, \*/
        /*metadata=%ld %ld %ld %ld %ld %ld\n",*/
        /*((int64_t*)idx)[0],((int64_t*)idx)[1],((int64_t*)idx)[2],*/
        /*offset, prefetch_entry->size,*/
        /*((int64_t*)prefetch_entry->data)[0],*/
        /*((int64_t*)prefetch_entry->data)[1],*/
        /*((int64_t*)prefetch_entry->data)[2],*/
        /*((int64_t*)prefetch_entry->data)[3],*/
        /*((int64_t*)prefetch_entry->data)[4],*/
        /*((int64_t*)prefetch_entry->data)[5]));*/
    retaddr = (void *)((uintptr_t)prefetch_entry->data+offset);
  }
  return retaddr;
}

void chpl_comm_pbuf_acq() {
  struct __prefetch_entry_t *cur = pbuf->head;
  assert(pbuf);
  while(cur) {
    // TODO we are keeping everything consistent but this will cause a
    // big hit in the benchmarks we don't really need consistency
    // so inconsistency should be allowed
    chpl_comm_reprefetch(cur);
    cur = cur->next;
  }
}

extern void __reprefetch_wrapper(void* owner_obj, c_nodeid_t
    dest_node_id, c_nodeid_t src_node_id, void* robjaddr, void*
    slice_desc, size_t slice_desc_size, bool consistent, bool
    static_domain);

void chpl_comm_reprefetch(struct __prefetch_entry_t *entry) {

  if(entry->static_domain) {
    if(entry->consec_remote_data) {
      /*printf("%d Reprefetching from %d %p - Using bulk\*/
          /*get\n", chpl_nodeID, entry->origin_node, entry);*/
      prefetch_consec_entry(entry);
      return;
    }
    else if(entry->strided_remote_data) {
      /*printf("%d Reprefetching from %d %p - Using strided\*/
          /*get\n", chpl_nodeID, entry->origin_node, entry);*/
      prefetch_strided_entry(entry);
      return;
    }
  }
  /*printf("%d Reprefetching from %d %p - Using on stmt\*/
      /*\n", chpl_nodeID, entry->origin_node, entry);*/
  __reprefetch_wrapper(entry->owner_obj, chpl_nodeID,
      entry->origin_node, entry->robjaddr, entry->slice_desc,
      entry->slice_desc_size, entry->pf_type & PF_CONSISTENT,
      entry->static_domain);
}

void prefetch_entry_init_seqn_n(struct __prefetch_entry_t *entry,
    cache_seqn_t offset) {
  if(entry) {
    /*printf("%p has new sn = %ld\n", entry,*/
        /*pbuf->prefetch_sequence_number);*/
    cache_seqn_t sn = pbuf->prefetch_sequence_number;
    pbuf->prefetch_sequence_number++;
    entry->sn = seqn_max(entry->sn, sn);
    /*printf("Locale %d Task %d has set sn. (entry->sn: %ld)\n",*/
        /*chpl_nodeID, chpl_task_getId(), entry->sn);*/
    entry->sn_updated = true;
  }
  else {
    printf("Null entry\n");
  }
}

static
struct __prefetch_entry_t *add_to_prefetch_buffer(
    struct prefetch_buffer_s* pbuf, c_nodeid_t origin_node,
    void* robjaddr, size_t prefetch_size, void *slice_desc,
    size_t slice_desc_size, bool consistent, bool static_domain,
    int64_t data_start_offset, size_t elemsize){

  struct __prefetch_entry_t *head;
  struct __prefetch_entry_t *new_entry;
  void *data_bundle;
  int i;

  assert(pbuf);
  assert(elemsize);

  head = pbuf->head;

  //currently just add to the head
  new_entry = chpl_malloc(sizeof(struct __prefetch_entry_t)*1);

  new_entry->origin_node = origin_node;
  new_entry->robjaddr = robjaddr;
  new_entry->slice_desc = chpl_malloc(slice_desc_size);
  chpl_memcpy(new_entry->slice_desc, slice_desc, slice_desc_size);
  new_entry->slice_desc_size = slice_desc_size;
  new_entry->pf_type = PF_INIT;
  new_entry->elemsize = elemsize;

  data_bundle = chpl_malloc(
      sizeof(struct __prefetch_entry *) +
      prefetch_size);

  new_entry->back_link = data_bundle;
  new_entry->data = (char *)data_bundle +
    sizeof(struct __prefetch_entry *);

  new_entry->data_start = (char *)new_entry->data + data_start_offset;

  // optimization properties
  new_entry->static_domain = static_domain;
  new_entry->strided_remote_data = false;
  new_entry->consec_remote_data = false;

  // this should probably be handled by DSI
  new_entry->actual_data_size = prefetch_size - data_start_offset;

  *(new_entry->back_link) = new_entry;

  if(consistent) {
    new_entry->pf_type |= (PF_CONSISTENT|PF_PERSISTENT);
  }

  // TODO I am not sure if should lock is necessary
  // TODO think about persistency
  new_entry->should_lock = (new_entry->pf_type &
    (PF_CONSISTENT|PF_PERSISTENT)) == (PF_CONSISTENT|PF_PERSISTENT) ;

  /*new_entry->should_lock = true;*/
  // currently everything has canread and nothing can have canwrite
  new_entry->pf_type |= PF_CANREAD;
  new_entry->sn = NO_SEQUENCE_NUMBER;

  if(consistent) {
    prefetch_entry_init_seqn_n(new_entry, 0);
  }
  
  // runtime assumes that prefetching happens with one task per
  // locale
  
  if(consistent) {
    new_entry->state_counter = 0;
    new_entry->state_lock = chpl_malloc(sizeof(chpl_sync_aux_t));
    chpl_sync_initAux(new_entry->state_lock);

    new_entry->page_count = prefetch_size/PF_PAGE_SIZE+1;

    new_entry->rwl = chpl_malloc(sizeof(pthread_rwlock_t) *
        (new_entry->page_count));

    for(i = 0 ; i < new_entry->page_count ; i++) {
      pthread_rwlock_init(&(new_entry->rwl[i]), NULL);
    }
#if USE_CUSTOM_SYNCH
    new_entry->states =
      chpl_calloc(sizeof(pfpage_state_t), new_entry->page_count);
#endif
  }

  // make sure that thype of prefetch is somethin reasonable
  // at least one of these must be set
  assert(new_entry->pf_type & (PF_CANREAD|PF_CANWRITE));

  // TODO if not consistent, rest doesn't really matter, but we are not
  // checking it. Maybe we should for sanity?
  

  // currentyl we are always adding to head
  if(head != NULL) {
    /*new_entry->next = head->next;*/
    /*if(head->next) {*/
      /*head->next->prev = new_entry;*/
    /*}*/
    new_entry->next = head;
    head->prev = new_entry;
  }
  else {
    new_entry->next = NULL;
  }

  new_entry->prev = NULL;
  pbuf->head = new_entry;

  return new_entry;
}

// assumed to be called from a thread-safe context
void reprefetch_single_entry(struct __prefetch_entry_t *entry) {
  if(entry) {
#if CHECK_PFENTRY_INTEGRITY
    check_integrity(entry);
#endif
    chpl_comm_reprefetch(entry);
    prefetch_entry_init_seqn_n(entry, 0);
  }
}

void prefetch_update() {

  if(pbuf->head) {
    /*full_memory_barrier();*/
    /*chpl_comm_barrier("prefetch update");*/

    //here only one task will get the lock
    // is there a CAS for runtime?
    chpl_sync_lock(&pbuf->update_lock);
    if(!pbuf->being_updated) {
      struct __prefetch_entry_t *cur = pbuf->head;

      pbuf->being_updated = true;
      chpl_sync_unlock(&pbuf->update_lock);

      assert(pbuf);
      /*printf("prefe3tch update on node %d started\n",*/
          /*chpl_nodeID);*/
      while(cur) {
        //we don't care at all if the entry is inconsistent
        if(cur->pf_type&PF_CONSISTENT) {
          //currently we don't have module support for write-back
          //prefetch
          if(cur->pf_type&PF_CANWRITE) {
            //unimplemented
            assert(0);
          }
          if(cur->pf_type&PF_CANREAD) {
            //if the data is stale
            if(cur->sn >= 0 &&
                cur->sn < pbuf->prefetch_sequence_number-1) {
              if(cur->pf_type&PF_PERSISTENT) {
                //keep the data in buffer but update it by reprefetching
                /*printf("data was found stale, updating : %p\n", cur);*/
                /*chpl_comm_reprefetch(cur);*/
                /*cur->sn_updated = false;*/
                
                // if the data was prefetched with persistent flag, then
                // updates to it must be done whenever a task tries to
                // read that data and realizes that it was stale
              }
              else {
                /*printf("data was found stale, evicting : %p\n", cur);*/
                //simply evict the data from the buffer
                remove_from_prefetch_buffer(pbuf, cur);
                // .. or do nothing? - don't think so
                // this way, next read to this entry will invalidate it
              }
            }
          }
          else {
            //with unimplemented write-back we shouldn't end up here
            assert(0);
          }
        }
        cur = cur->next;
      }
      //we updated the data in the buffer, now it's time to update
      //sequence numbers
      cur = pbuf->head;
      while(cur) {
        // TODO function should be update not init
        // TODO we can choose to update only the ones that we prefetched
        // again
        //
        if(!cur->sn_updated) {
          prefetch_entry_init_seqn_n(cur, 0);
        }
        cur = cur->next;
      }
    }
    else {
      // nothing to do but hit the barrier
      chpl_sync_unlock(&pbuf->update_lock);
    }

    /*full_memory_barrier();*/
    /*chpl_comm_barrier("prefetch update exit");*/
    pbuf->being_updated = false;
    /*printf("prefech update on %d complete\n", chpl_nodeID);*/
  }
}

bool entry_has_data(struct __prefetch_entry_t *entry) {
  if(entry) {
    return entry->data!=NULL;
  }
  return false;
}

void acquire_prefetch_buffer(int ln, int fn) {
  struct __prefetch_entry_t *cur = pbuf->head;
  chpl_prefetch_taskPrvData_t* task_local =
    task_private_prefetch_data();

  while(cur) {
    if(task_local->last_acquire > cur->sn) {

      start_update(cur, -1);
      // someone might have already updated the entry, so check again if
      // it's still stale
      if(task_local->last_acquire > cur->sn) {
        /*printf("Locale %d Task %d acquiring. (entry: %p, next: %p\*/
          /*entry->sn: %ld, buf->sn: %ld) %d %d\n", chpl_nodeID, chpl_task_getId(),*/
            /*cur, cur->next, cur->sn, pbuf->prefetch_sequence_number, ln, fn);*/
        reprefetch_single_entry(cur);
      }
      stop_update(cur, -1);
    }
    cur = cur->next;
  }
}



// If this is called we know that data is prefetch consistently.
// Therefore no need to check it again.
static
void prefetch_get_consistent(struct __prefetch_entry_t* prefetch_entry,
    void *dst, void *src, size_t size, int page_idx, int ln, int fn) {

  chpl_prefetch_taskPrvData_t* task_local =
    task_private_prefetch_data();

  if(task_local->last_acquire > prefetch_entry->sn) {

    start_update(prefetch_entry, page_idx);
    // someone might have already updated the entry, so check again if
    // it's still stale
    if(task_local->last_acquire > prefetch_entry->sn) {
      /*printf("\t>\t");*/
      /*int i;*/
      /*double * tmp_data = (double *)get_entry_data_start(prefetch_entry);*/
      /*for(i = 0 ; i < 8 ; i++) {*/
        /*printf("%f ", tmp_data[i]);*/
      /*}*/
      /*printf("\n");*/
      /*printf("Locale %d Task %d reprefetching. (entry: %p, \*/
        /*entry->sn: %ld, buf->sn: %ld) %d %d\n", chpl_nodeID, chpl_task_getId(),*/
          /*prefetch_entry, prefetch_entry->sn,*/
          /*pbuf->prefetch_sequence_number, ln, fn);*/
      reprefetch_single_entry(prefetch_entry);

      /*if(chpl_nodeID == 1) {*/
        /*printf("\t>\t");*/
        /*for(i = 0 ; i < 8 ; i++) {*/
          /*printf("%f ", tmp_data[i]);*/
        /*}*/
        /*printf("\n");*/
        /*for(i = 8 ; i < 16 ; i++) {*/
          /*printf("%f ", tmp_data[i]);*/
        /*}*/
        /*printf("\n");*/
      /*}*/
    }
    stop_update(prefetch_entry, page_idx);
  }

  start_read(prefetch_entry, page_idx);
  chpl_memcpy(dst, src, size);
  /*printf("Locale %d read %f\n", chpl_nodeID, *((double *)(src)));*/
  stop_read(prefetch_entry, page_idx);
}
//
// this is intended to be a thin wrapper around add_to_prefetch_buffer
// that should only be used from PrefetchHook code
//
// TODO revise this function and add_to_prefetch_buffer TODO
void *initialize_prefetch_handle(void* owner_obj, c_nodeid_t
    origin_node, void* robjaddr, struct __prefetch_entry_t **new_entry,
    size_t prefetch_size, void *slice_desc, size_t slice_desc_size, bool
    consistent, bool static_domain, int64_t data_start_offset,
    size_t elemsize) {

  *new_entry = add_to_prefetch_buffer(pbuf, origin_node, robjaddr,
      prefetch_size, slice_desc, slice_desc_size, consistent,
      static_domain, data_start_offset, elemsize);

  /*printf("%d creating new handle %p\n", chpl_nodeID, *new_entry);*/
  (*new_entry)->owner_obj = owner_obj;
  (*new_entry)->size = prefetch_size;

  return (*new_entry)->data;
}

void *update_prefetch_handle(void* owner_obj, c_nodeid_t
    origin_node, void* robjaddr, struct __prefetch_entry_t **new_entry,
    size_t prefetch_size, void *slice_desc, size_t slice_desc_size, bool
    consistent) {

  if(prefetch_size != (*new_entry)->size) {
    /*printf("%d reallocating old handle\n", chpl_nodeID);*/
    //reallocate space
    /*chpl_free((*new_entry)->data);*/
    (*new_entry)->size = prefetch_size;
    (*new_entry)->data = chpl_malloc(prefetch_size);
  }
  else {
    /*printf("%d reusing old handle\n", chpl_nodeID);*/
  }
  return (*new_entry)->data;
}

// TODO why do we need this?
void create_prefetch_handle(struct __prefetch_entry_t **entry) {
  *entry = NULL;
}

// TODO make this safer
int32_t get_lock_offset(struct __prefetch_entry_t *entry, void *addr) {
  return ((char *)entry->back_link)-((char *)addr);
}

static inline
void prefetch_get_inconsistent(void *dst, void *src, size_t size) {
  chpl_memcpy(dst,src,size);
}

// TODO dst->addr, src->raddr
void prefetch_get(void *dst, int32_t lock_offset, void *src,
    size_t size, int32_t typeIndex, int ln, int32_t fn) {

  struct __prefetch_entry_t* prefetch_entry =
    *((struct __prefetch_entry_t **)((char *)src+lock_offset));

  if(prefetch_entry->should_lock) {
    int page_idx = (-1*lock_offset)/PF_PAGE_SIZE;
    prefetch_get_consistent(prefetch_entry, dst, src, size, page_idx,
         ln, fn);
  }
  else {
    prefetch_get_inconsistent(dst,src,size);
  }
}

extern void __writethrough_wrapper(c_nodeid_t node, void *entry,
    void* data, int64_t offset);
void prefetch_put(void *addr, int32_t lock_offset, void *raddr,
    size_t size, int32_t typeIndex, int ln, int32_t fn) {

  struct __prefetch_entry_t* prefetch_entry =
    *((struct __prefetch_entry_t **)((char *)raddr+lock_offset));

  __writethrough_wrapper(prefetch_entry->origin_node, 
      prefetch_entry->owner_obj, addr, (-1*lock_offset));
}

void *get_entry_data(struct __prefetch_entry_t *entry) {
  return entry->data;
}
void *get_entry_data_start(struct __prefetch_entry_t *entry) {
  return entry->data_start;
}

void *get_entry_remote_data_start(struct __prefetch_entry_t *entry) {
  return entry->remote_data_start;
}
void set_entry_remote_data_start(struct __prefetch_entry_t *entry,
    void *start) {
  entry->remote_data_start = start;
}
size_t get_entry_size(struct __prefetch_entry_t *entry) {
  return entry->size;
}
size_t get_entry_data_actual_size(struct __prefetch_entry_t *entry) {
  return entry->actual_data_size;
}

void initialize_opt_fields(struct __prefetch_entry_t *entry,
    bool strided_remote_data, bool consec_remote_data,
    int32_t stridelevels, size_t *dststrides, size_t *srcstrides,
    size_t *counts) {

  entry->strided_remote_data = strided_remote_data;
  entry->consec_remote_data = consec_remote_data;

  entry->stridelevels = stridelevels;

  if(stridelevels != 0) {
    entry->dststrides = chpl_calloc(stridelevels, sizeof(size_t));
    memcpy(entry->dststrides, dststrides, sizeof(size_t)*stridelevels);
    entry->srcstrides = chpl_calloc(stridelevels, sizeof(size_t));
    memcpy(entry->srcstrides, srcstrides, sizeof(size_t)*stridelevels);
    entry->counts = chpl_calloc(stridelevels+1, sizeof(size_t));
    /*printf("%d Init %d %d\n", chpl_nodeID, counts[0], counts[1]);*/
    memcpy(entry->counts, counts,
        sizeof(size_t)*(stridelevels+1));
  }
  else {
    entry->dststrides = NULL;
    entry->srcstrides = NULL;
    entry->counts = NULL;
  }
}

void prefetch_consec_entry(struct __prefetch_entry_t *entry) {

  if(!entry->consec_remote_data) {
    chpl_internal_error("Remote data is not strided\n");
  }

  chpl_comm_get(entry->data_start, entry->origin_node,
      entry->remote_data_start, entry->actual_data_size, -1, 0, 0, 0);
}

void prefetch_strided_entry(struct __prefetch_entry_t *entry) {

  if(!entry->strided_remote_data) {
    chpl_internal_error("Remote data is not strided\n");
  }
  if(entry->stridelevels > 1) {
    chpl_internal_error("Cannot strided-prefetch where stridelevels >\
        1\n");
  }

  assert(entry);
  assert(entry->remote_data_start);

  /*uint8_t *data_temp = (uint8_t *)(entry->data_start);*/
  /*printf("\t\t%d pre-strd pref: %d %d %d %d\n\*/
      /*\t\t\tstridelevels:%d, counts: %d %d, srcstride: %d,\*/
      /*dststride: %d", chpl_nodeID, data_temp[0],*/
                                             /*data_temp[1],*/
                                             /*data_temp[2],*/
                                             /*data_temp[3],*/
           /*entry->stridelevels, entry->counts[0], entry->counts[1],*/
           /*entry->srcstrides[0], entry->dststrides[0]);*/
  chpl_comm_get_strd(entry->data_start, entry->dststrides,
      entry->origin_node, entry->remote_data_start, entry->srcstrides,
      entry->counts, entry->stridelevels, entry->elemsize, -1, 0, 0, 0);
  /*printf("\t\t%d pre-strd pref: %d %d %d %d\n", chpl_nodeID, data_temp[0],*/
                                             /*data_temp[1],*/
                                             /*data_temp[2],*/
                                             /*data_temp[3]);*/
}

