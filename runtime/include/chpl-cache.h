/*
 * Copyright 2004-2017 Cray Inc.
 * Other additional copyright holders may be indicated within.
 * 
 * The entirety of this work is licensed under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License.
 * 
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _chpl_cache_h_
#define _chpl_cache_h_

#include "chpltypes.h"
#include "chpl-atomics.h"
#include "chpl-comm.h" // to get HAS_CHPL_CACHE_FNS via chpl-comm-task-decls.h
#include "chpl-tasks.h"

#ifdef HAS_CHPL_CACHE_FNS
// This is a cache for remote data.

// Is the cache enabled? (set at compile time)
extern const int CHPL_CACHE_REMOTE;

typedef int64_t cache_seqn_t;
static inline
int chpl_cache_enabled(void)
{
  return CHPL_CACHE_REMOTE && chpl_task_supportsRemoteCache();
}

#define USE_CUSTOM_SYNCH 0

#if USE_CUSTOM_SYNCH
#define PF_PAGE_STATE_NUM_BITS 32
#define PF_PAGE_IDLE 0
#define PF_PAGE_READ_MASK 1<<(PF_PAGE_STATE_NUM_BITS-2)
#define PF_PAGE_WRITE_MASK PF_PAGE_READ_MASK<<1
#define PF_PAGE_SINGLE_READER (PF_PAGE_READ_MASK&1)
#define PF_PAGE_SINGLE_WRITER PF_PAGE_WRITE_MASK

#define pfpage_state_t atomic_uint_least32_t
#endif //USE_CUSTOM_SYNC

#define PF_PAGE_SIZE 4096
#define CHECK_PFENTRY_INTEGRITY 0

#define PF_CONSISTENT 1
#define PF_CANREAD 2
#define PF_CANWRITE 4
#define PF_PERSISTENT 8

#define PF_DEFAULT (PF_CONSISTENT|PF_CANREAD|PF_PERSISTENT)
#define PF_INCONSISTENT 0
#define PF_INIT 0
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
  void *data_start;
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
  bool strided_reprefetch; // if static_domain && !strided then do get


#if CHECK_PFENTRY_INTEGRITY
  void *base_data;
#endif
  // buffer data structure
  struct __prefetch_entry_t *next;
  struct __prefetch_entry_t *prev;
} _prefetch_entry_t, *prefetch_entry_t;

void* get_data_from_prefetch_entry(prefetch_entry_t entry);
// Initialize the remote data cache layer. 
void chpl_cache_init(void);
void chpl_cache_exit(void);

void chpl_prefetch_init(void);
void chpl_prefetch_exit(void);
// If release is set, waits on any pending puts in the cache.
// If acquire is set, sets this task's last acquire fence to 
// the cache's current request number.
void chpl_cache_fence(int acquire, int release, int ln, int32_t fn);

// "acquire" barrier or fence -> discard pre-fetched GET values
static inline
void chpl_cache_acquire(int ln, int32_t fn)
{
  if (chpl_cache_enabled()) chpl_cache_fence(1, 0, ln, fn);
}
// "release" barrier or fence -> complete pending PUTs
static inline
void chpl_cache_release(int ln, int32_t fn)
{
  if (chpl_cache_enabled()) chpl_cache_fence(0, 1, ln, fn);
}


// These are the functions that the generated code should be eventually
// calling on a put or a get.
void chpl_cache_comm_put(void* addr, c_nodeid_t node, void* raddr,
                         size_t size, int32_t typeIndex,
                         int ln, int32_t fn);
void chpl_cache_comm_get(void *addr, c_nodeid_t node, void* raddr,
                         size_t size, int32_t typeIndex,
                         int ln, int32_t fn);
void chpl_cache_comm_prefetch(c_nodeid_t node, void* raddr,
                              size_t size, int32_t typeIndex,
                              int ln, int32_t fn);
void  chpl_cache_comm_get_strd(
                   void *addr, void *dststr, c_nodeid_t node, void *raddr,
                   void *srcstr, void *count, int32_t strlevels,
                   size_t elemSize, int32_t typeIndex,
                   int ln, int32_t fn);
void  chpl_cache_comm_put_strd(
                      void *addr, void *dststr, c_nodeid_t node, void *raddr,
                      void *srcstr, void *count, int32_t strlevels,
                      size_t elemSize, int32_t typeIndex,
                      int ln, int32_t fn);

// For debugging.
void chpl_cache_print(void);
void chpl_cache_assert_released(void);

//struct __prefetch_entry_t *chpl_comm_prefetch(c_nodeid_t node, 
    //void* raddr, size_t size, size_t serialized_base_idx);
//struct __prefetch_entry_t *chpl_comm_request_prefetch(c_nodeid_t node,
    //void* robjaddr, void* slice_desc, size_t slice_desc_size,
    //bool consistent);
void chpl_prefetch_comm_get(void *addr, c_nodeid_t node, void* raddr,
    size_t size, int32_t typeIndex, int ln, int32_t fn);
void chpl_prefetch_comm_get_fast(void *addr, c_nodeid_t node, void*
    raddr, size_t size, int32_t typeIndex, int ln, int32_t fn);
int64_t is_prefetched(c_nodeid_t node, void* raddr, size_t size);
int64_t is_prefetched_in_entry(struct __prefetch_entry_t* entry,
    c_nodeid_t node, void* raddr, size_t size);
int64_t get_data_offset(struct __prefetch_entry_t* prefetch_entry,
    size_t size, size_t serialized_idx);
//int64_t get_prefetched_data(struct __prefetch_entry_t* prefetch_entry,
    //size_t size, size_t serialized_idx, void* dest);
void get_prefetched_data(void *accessor,
    struct __prefetch_entry_t* prefetch_entry, size_t size, void* idx,
    int64_t* found, void *dest);
void *get_prefetched_data_addr(void *accessor,
    struct __prefetch_entry_t* prefetch_entry, size_t size, void* idx,
    int64_t* found);
void chpl_comm_pbuf_acq(void);
void chpl_comm_reprefetch(struct __prefetch_entry_t *entry);
void prefetch_entry_init_seqn_n(struct __prefetch_entry_t *entry,
    cache_seqn_t offset);
void prefetch_update(void);
bool entry_has_data(struct __prefetch_entry_t *entry);
void reprefetch_single_entry(struct __prefetch_entry_t *entry);
void *initialize_prefetch_handle(void* owner_obj, c_nodeid_t
    origin_node, void* robjaddr, struct __prefetch_entry_t **new_entry,
    size_t prefetch_size, void *slice_desc, size_t slice_desc_size, bool
    consistent, bool static_domain, int64_t data_start_offset);
void *update_prefetch_handle(void* owner_obj, c_nodeid_t
    origin_node, void* robjaddr, struct __prefetch_entry_t **new_entry,
    size_t prefetch_size, void *slice_desc, size_t slice_desc_size, bool
    consistent);
void create_prefetch_handle(struct __prefetch_entry_t **entry);
int32_t get_lock_offset(struct __prefetch_entry_t *entry, void * addr);
void prefetch_get(void *dst, int32_t lock_offset, void *src,
    size_t size, int32_t typeIndex, int ln, int32_t fn);

void *get_entry_data(struct __prefetch_entry_t *entry);
void *get_entry_data_start(struct __prefetch_entry_t *entry);
void set_entry_data_start(struct __prefetch_entry_t *entry, void *start);
void *get_entry_remote_data_start(struct __prefetch_entry_t *entry);
void set_entry_remote_data_start(struct __prefetch_entry_t *entry, void *start);
size_t get_entry_size(struct __prefetch_entry_t *entry);
size_t get_entry_data_actual_size(struct __prefetch_entry_t *entry);
void acquire_prefetch_buffer(int ln, int fn);
#endif
// ifdef HAS_CHPL_CACHE_FNS


#endif

