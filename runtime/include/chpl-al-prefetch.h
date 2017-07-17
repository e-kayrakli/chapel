#ifndef _chpl_al_prefetch_h_
#define _chpl_al_prefetch_h_

#include <stdbool.h>
#include "chpltypes.h"
#include "chpl-atomics.h"
#include "chpl-comm.h" // to get HAS_CHPL_CACHE_FNS via chpl-comm-task-decls.h
#include "chpl-tasks.h"

#define PF_PAGE_SIZE 4096
#define CHECK_PFENTRY_INTEGRITY 0

#define PF_CONSISTENT 1
#define PF_CANREAD 2
#define PF_CANWRITE 4
#define PF_PERSISTENT 8

#define PF_DEFAULT (PF_CONSISTENT|PF_CANREAD|PF_PERSISTENT)
#define PF_INCONSISTENT 0
#define PF_INIT 0

struct prefetch_buffer_s* pbuf;

// TODO I am not sure if we need this
typedef int64_t cache_seqn_t;

chpl_prefetch_taskPrvData_t* task_private_prefetch_data(void);

struct prefetch_buffer_s {
  void *fast_access_addr;
  struct __prefetch_entry_t *head;

  // incremented with acquire fence
  cache_seqn_t prefetch_sequence_number;

  //minimum task sequence number
  cache_seqn_t min_task_seqn;
  chpl_sync_aux_t min_task_seqn_lock;

  bool being_updated;
  chpl_sync_aux_t update_lock;
};

// Note on throttling: Currently I am choosing to keep a big monolithic
// chunk of data where active messages fill up gradually.
//
// However, I'd like to move to a world where chunks brought in by
// active messages go to separate locations where we expose done objects
// to prefetch functions in chpl-cache. I think this would allow us to
// do something that we can call a prefetch stream.
//
// With throttling, we can even start freeing up some memory if we can
// guarantee that prefetch data is accessed only once.
//
// OTOH, such application brings up other questions: how much does this
// change affect higher layers of the stack? I think one implication is
// that we have to separate metadata and data in the prefetch_entry
// (albeit we can still pack them before sending). This would probably
// lead to having dsiSerializeData dsiSerializeMetadata on the sender
// side. And on the prefetcher side I think we can hide some of this
// complexity.
typedef struct __prefetch_entry_t{
  c_nodeid_t origin_node;
  void* owner_obj;
  void* robjaddr;
  size_t size;

  size_t elemsize; // necessary for strided gets

  //we need to store and atomic state of the entry if it's marked to be
  //consistent I couldn't figure out a way to do that with an atomic
  //variable/c intrinsics. So I am relying on locks
  int16_t state_counter;
  chpl_sync_aux_t *state_lock;
  bool should_lock;

  int page_count;
  pthread_rwlock_t *rwl; //array of locks for pages

#if USE_CUSTOM_SYNCH
  pfpage_state_t *states;
#endif

  // prefetch type controls consistency protocol on a sync event
  uint8_t pf_type;

  cache_seqn_t sn;
  bool sn_updated;

  // we need to keep slice info, in case we need to reprefetch
  void *slice_desc;
  size_t slice_desc_size;

  // when data is allocated the chunk will start with a backlink to the
  // prefetch entry
  void **back_link;
  void *data;

  //fields used in optimizations

  // we need to store the beginning of the actual data for fast
  // reprefetch in static domains
  bool static_domain;
  void *data_start; // TODO change to local_data_start
  void *remote_data_start;
  size_t actual_data_size;

  /*
   if static_domain && !strided_reprefetch then
    array_get
   else if static_domain && strided_prefetch then
    strided_array_get
   else if !static_domain then
    on statement
  */
  bool strided_remote_data; // if static_domain && !strided then do get
  bool consec_remote_data;

  // meaningful iff strided_remote_data && static_domain
  int32_t stridelevels;
  size_t *dststrides;
  size_t *srcstrides;
  size_t *counts;

#if CHECK_PFENTRY_INTEGRITY
  void *base_data;
#endif
  // buffer data structure
  struct __prefetch_entry_t *next;
  struct __prefetch_entry_t *prev;
} _prefetch_entry_t, *prefetch_entry_t;

void* get_data_from_prefetch_entry(prefetch_entry_t entry);
void chpl_prefetch_init(void);
void chpl_prefetch_exit(void);

// TODO are we using these?
void chpl_prefetch_comm_get_fast(void *addr, c_nodeid_t node, void*
    raddr, size_t size, int32_t typeIndex, int ln, int32_t fn);
void get_prefetched_data(void *accessor,
    struct __prefetch_entry_t* prefetch_entry, size_t size, void* idx,
    int64_t* found, void *dest);
void chpl_comm_pbuf_acq(void);
void prefetch_update(void);


void *get_prefetched_data_addr(void *accessor,
    struct __prefetch_entry_t* prefetch_entry, size_t size, void* idx,
    int64_t* found);
void chpl_comm_reprefetch(struct __prefetch_entry_t *entry);
void prefetch_entry_init_seqn_n(struct __prefetch_entry_t *entry,
    cache_seqn_t offset);
bool entry_has_data(struct __prefetch_entry_t *entry);
void reprefetch_single_entry(struct __prefetch_entry_t *entry);
void *initialize_prefetch_handle(void* owner_obj, c_nodeid_t
    origin_node, void* robjaddr, struct __prefetch_entry_t **new_entry,
    size_t prefetch_size, void *slice_desc, size_t slice_desc_size, bool
    consistent, bool static_domain, int64_t data_start_offset,
    size_t elemsize);
void *update_prefetch_handle(void* owner_obj, c_nodeid_t
    origin_node, void* robjaddr, struct __prefetch_entry_t **new_entry,
    size_t prefetch_size, void *slice_desc, size_t slice_desc_size, bool
    consistent);
void create_prefetch_handle(struct __prefetch_entry_t **entry);
int32_t get_lock_offset(struct __prefetch_entry_t *entry, void * addr);
void prefetch_get(void *dst, int32_t lock_offset, void *src,
    size_t size, int32_t typeIndex, int ln, int32_t fn);
void prefetch_put(void *dst, int32_t lock_offset, void *src,
    size_t size, int32_t typeIndex, int ln, int32_t fn);

void *get_entry_data(struct __prefetch_entry_t *entry);
void *get_entry_data_start(struct __prefetch_entry_t *entry);
void set_entry_data_start(struct __prefetch_entry_t *entry, void *start);
void *get_entry_remote_data_start(struct __prefetch_entry_t *entry);
void set_entry_remote_data_start(struct __prefetch_entry_t *entry, void *start);
size_t get_entry_size(struct __prefetch_entry_t *entry);
size_t get_entry_data_actual_size(struct __prefetch_entry_t *entry);
void acquire_prefetch_buffer(int ln, int fn);
void initialize_opt_fields(struct __prefetch_entry_t *entry,
    bool strided_remote_data, bool consec_remote_data,
    int32_t stridelevels, size_t *dstStrides, size_t *srcStrides,
    size_t *counts);
void prefetch_consec_entry(struct __prefetch_entry_t *entry);
void prefetch_strided_entry(struct __prefetch_entry_t *entry);

#endif
