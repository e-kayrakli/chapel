/*
 * Copyright 2004-2016 Cray Inc.
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

static inline
int chpl_cache_enabled(void)
{
  return CHPL_CACHE_REMOTE && chpl_task_supportsRemoteCache();
}

typedef struct __prefetch_entry_t{
  c_nodeid_t origin_node;
  void* robjaddr;
  size_t size;
  size_t serialized_base_idx;

  void *data;
  struct __prefetch_entry_t *next;
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
struct __prefetch_entry_t *chpl_comm_request_prefetch(c_nodeid_t node,
    void* robjaddr);
void chpl_prefetch_comm_get(void *addr, c_nodeid_t node, void* raddr,
    size_t size, int32_t typeIndex, int ln, int32_t fn);
void chpl_prefetch_comm_get_fast(void *addr, c_nodeid_t node, void*
    raddr, size_t size, int32_t typeIndex, int ln, int32_t fn);
int64_t is_prefetched(c_nodeid_t node, void* raddr, size_t size);
int64_t is_prefetched_in_entry(struct __prefetch_entry_t* entry,
    c_nodeid_t node, void* raddr, size_t size);
int64_t get_data_offset(struct __prefetch_entry_t* prefetch_entry,
    size_t size, size_t serialized_idx);
int64_t get_prefetched_data(struct __prefetch_entry_t* prefetch_entry,
    size_t size, size_t serialized_idx, void* dest);
void *get_prefetched_data_addr(struct __prefetch_entry_t* 
    prefetch_entry, size_t size, size_t serialized_idx, int64_t* dest);
#endif
// ifdef HAS_CHPL_CACHE_FNS


#endif

