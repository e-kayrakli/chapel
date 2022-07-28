/*
 * Copyright 2020-2022 Hewlett Packard Enterprise Development LP
 * Copyright 2004-2019 Cray Inc.
 * Other additional copyright holders may be indicated within.  *
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

#include "sys_basic.h"
#include "chplrt.h"
#include "chpl-linefile-support.h"
#include "chpl-mem.h"
#include "chpl-gpu.h"
#include "chpl-gpu-diags.h"
#include "chpl-tasks.h"
#include "error.h"
#include "chplcgfns.h"

#ifdef HAS_GPU_LOCALE

/*
 * Enable this 'define' to use Unified Virtual Addressing for all GPU
 * allocations. As UVA uses page-locked memory on the host-side, accesses to
 * "GPU" memory from inside kernels will result in fine-grained access over the
 * PCI. So, this will cause a significant performance issue. We might want to
 * enable this when we're working on GPU-driven communication. Although, in the
 * long term we'll probably want UVA memory to be limited to things like
 * communication signal buffers etc. 
*/
#define CHPL_GPU_MEM_UVA

#include <cuda.h>
#include <cuda_runtime.h>
#include <assert.h>
#include <stdbool.h>

static void CHPL_GPU_DEBUG(const char *str, ...) {
  if (verbosity >= 2) {
    va_list args;
    va_start(args, str);
    vfprintf(stdout, str, args);
    va_end(args);
    fflush(stdout);
  }
}

static void chpl_gpu_cuda_check(int err, const char* file, int line) {
  if(err != CUDA_SUCCESS) {
    const int msg_len = 256;
    char msg[msg_len];

    snprintf(msg, msg_len,
             "%s:%d: Error calling CUDA function: %s (Code: %d)",
             file, line, cudaGetErrorString(err), err);

    chpl_internal_error(msg);
  }
}

#define CUDA_CALL(call) do {\
  chpl_gpu_cuda_check((int)call, __FILE__, __LINE__);\
} while(0);

CUcontext *chpl_gpu_primary_ctx;
CUcontext *chpl_gpu_parent_ctx;

void chpl_gpu_init() {
  int         num_devices;

  // CUDA initialization
  CUDA_CALL(cuInit(0));

  CUDA_CALL(cuDeviceGetCount(&num_devices));

  chpl_gpu_primary_ctx = chpl_malloc(sizeof(CUcontext)*num_devices);

  int i;
  for (i=0 ; i<num_devices ; i++) {
    CUdevice device;
    CUcontext context;

    CUDA_CALL(cuDeviceGet(&device, i));
    CUDA_CALL(cuDevicePrimaryCtxSetFlags(device, CU_CTX_SCHED_BLOCKING_SYNC));
    CUDA_CALL(cuDevicePrimaryCtxRetain(&context, device));

    chpl_gpu_primary_ctx[i] = context;
  }
}

static void chpl_gpu_ensure_context() {
  CUcontext next_context = chpl_gpu_primary_ctx[chpl_task_getRequestedSubloc()];

  if (!chpl_gpu_has_context()) {
    CUDA_CALL(cuCtxPushCurrent(next_context));
  }
  else {
    CUcontext cur_context = NULL;
    cuCtxGetCurrent(&cur_context);
    if (cur_context == NULL) {
      chpl_internal_error("Unexpected GPU context error");
    }

    if (cur_context != next_context) {
      CUcontext popped;
      CUDA_CALL(cuCtxPopCurrent(&popped));
      CUDA_CALL(cuCtxPushCurrent(next_context));
    }
  }
}

static void* chpl_gpu_getKernel(const char* fatbinData, const char* kernelName) {
  chpl_gpu_ensure_context();

  CUmodule    cudaModule;
  CUfunction  function;

  // Create module for object
  CUDA_CALL(cuModuleLoadData(&cudaModule, fatbinData));

  // Get kernel function
  CUDA_CALL(cuModuleGetFunction(&function, cudaModule, kernelName));

  return (void*)function;
}

bool chpl_gpu_is_device_ptr(void* ptr) {
  //chpl_gpu_ensure_context();

  unsigned int res;

#ifdef CHPL_GPU_MEM_UVA
  // We call CUDA_CALL later, because we want to treat some error codes
  // separately
  CUresult ret_val = cuPointerGetAttribute(&res, CU_POINTER_ATTRIBUTE_MAPPED,
                                           (CUdeviceptr)ptr);

  if (ret_val == CUDA_SUCCESS) {
    return res;
#else
  // We call CUDA_CALL later, because we want to treat some error codes
  // separately
  CUresult ret_val = cuPointerGetAttribute(&res, CU_POINTER_ATTRIBUTE_MEMORY_TYPE,
                                           (CUdeviceptr)ptr);

  if (ret_val == CUDA_SUCCESS) {
    return res == CU_MEMORYTYPE_DEVICE || res == CU_MEMORYTYPE_UNIFIED;
#endif
  }
  else if (ret_val == CUDA_ERROR_INVALID_VALUE ||
           ret_val == CUDA_ERROR_NOT_INITIALIZED ||
           ret_val == CUDA_ERROR_DEINITIALIZED) {
    return false;  // this is a cpu pointer that CUDA doesn't even know about
  }

  // there must have been an error in calling the cuda function. report that.
  CUDA_CALL(ret_val);

  return false;
}

size_t chpl_gpu_get_alloc_size(void* ptr) {
  chpl_gpu_ensure_context();

  CUdeviceptr base;
  size_t size;
  CUDA_CALL(cuMemGetAddressRange(&base, &size, (CUdeviceptr)ptr));

  return size;
}

bool chpl_gpu_running_on_gpu_locale() {
  return chpl_task_getRequestedSubloc()>=0;
}

static void chpl_gpu_launch_kernel_help(int ln,
                                        int32_t fn,
                                        const char* fatbinData,
                                        const char* name,
                                        int grd_dim_x,
                                        int grd_dim_y,
                                        int grd_dim_z,
                                        int blk_dim_x,
                                        int blk_dim_y,
                                        int blk_dim_z,
                                        int nargs,
                                        va_list args) {
  chpl_gpu_ensure_context();

  CHPL_GPU_DEBUG("Kernel launcher called. (subloc %d)\n"
               "\tKernel: %s\n"
               "\tGrid: %d,%d,%d\n"
               "\tBlock: %d,%d,%d\n"
               "\tNumArgs: %d\n",
               chpl_task_getRequestedSubloc(),
               name,
               grd_dim_x, grd_dim_y, grd_dim_z,
               blk_dim_x, blk_dim_y, blk_dim_z,
               nargs);

  int i;
  void* function = chpl_gpu_getKernel(fatbinData, name);
  // TODO: this should use chpl_mem_alloc
  void*** kernel_params = chpl_malloc(nargs*sizeof(void**));

  assert(function);
  assert(kernel_params);

  CHPL_GPU_DEBUG("Creating kernel parameters\n");

  int* gpu_alloc_map = chpl_malloc(nargs*sizeof(int));

  for (i=0 ; i<nargs ; i++) {
    void* cur_arg = va_arg(args, void*);
    size_t cur_arg_size = va_arg(args, size_t);

    if (cur_arg_size > 0) {
      gpu_alloc_map[i] = 1;
      // TODO this allocation needs to use `chpl_mem_alloc` with a proper desc
      kernel_params[i] = chpl_malloc(1*sizeof(CUdeviceptr));

      *kernel_params[i] = chpl_gpu_mem_alloc(cur_arg_size,
                                             CHPL_RT_MD_GPU_KERNEL_ARG,
                                             ln, fn);

      chpl_gpu_copy_host_to_device(*kernel_params[i], cur_arg, cur_arg_size);

      CHPL_GPU_DEBUG("\tKernel parameter %d: %p (device ptr)\n",
                   i, *kernel_params[i]);
    }
    else {
      gpu_alloc_map[i] = 0;
      kernel_params[i] = cur_arg;
      CHPL_GPU_DEBUG("\tKernel parameter %d: %p\n",
                   i, kernel_params[i]);
    }
  }

  chpl_gpu_diags_verbose_launch(ln, fn, chpl_task_getRequestedSubloc(),
      blk_dim_x, blk_dim_y, blk_dim_z);
  chpl_gpu_diags_incr(kernel_launch);

  CHPL_GPU_DEBUG("Calling gpu function named %s\n", name);

  CUDA_CALL(cuLaunchKernel((CUfunction)function,
                           grd_dim_x, grd_dim_y, grd_dim_z,
                           blk_dim_x, blk_dim_y, blk_dim_z,
                           0,  // shared memory in bytes
                           0,  // stream ID
                           (void**)kernel_params,
                           NULL));  // extra options

  CHPL_GPU_DEBUG("Call returned %s\n", name);

  CUDA_CALL(cudaDeviceSynchronize());

  CHPL_GPU_DEBUG("Synchronization complete %s\n", name);

  for (i=0 ; i<nargs ; i++) {
    if (gpu_alloc_map[i] == 1) {
      chpl_gpu_mem_free(*kernel_params[i], 0, 0);
    }
    else {
    }
  }


  CHPL_GPU_DEBUG("Args freed and returning %s\n", name);
}

static bool chpl_gpu_allocated_on_host(void* memAlloc) {
  unsigned int res;
  CUresult ret_val = cuPointerGetAttribute(&res, CU_POINTER_ATTRIBUTE_MEMORY_TYPE,
      (CUdeviceptr)memAlloc);

  if (ret_val != CUDA_SUCCESS) {
    if (ret_val == CUDA_ERROR_INVALID_VALUE ||
        ret_val == CUDA_ERROR_NOT_INITIALIZED ||
        ret_val == CUDA_ERROR_DEINITIALIZED) {
      return true;
    }
    else {
      CUDA_CALL(ret_val);
    }
  }
  else {
    return res == CU_MEMORYTYPE_HOST;
  }

  return true;
}


void chpl_gpu_memmove(void* dst, void* src, size_t n) {
  if (!chpl_gpu_allocated_on_host(dst)) {
    assert(chpl_gpu_allocated_on_host(src) && "D to D not supported");
    chpl_gpu_copy_host_to_device(dst, src, n);
  }
  else if (!chpl_gpu_allocated_on_host(src)) {
    assert(chpl_gpu_allocated_on_host(dst) && "D to D not supported");
    chpl_gpu_copy_device_to_host(dst, src, n);
  }
  else {
    assert(chpl_gpu_allocated_on_host(src) &&
           chpl_gpu_allocated_on_host(dst));
    memmove(dst, src, n);
  }
}

void chpl_gpu_copy_device_to_host(void* dst, void* src, size_t n) {
  // This'll get confused as these functions can be called from a non-gpu
  // sublocale. Should we worry about multi-gpu nodes? Should we grab the
  // device/context info from the device pointer?
  /*chpl_gpu_ensure_context();*/

  assert(chpl_gpu_is_device_ptr(src));

  CHPL_GPU_DEBUG("Copying %zu bytes from device to host\n", n);

  CUDA_CALL(cuMemcpyDtoH(dst, (CUdeviceptr)src, n));
}

void chpl_gpu_copy_host_to_device(void* dst, void* src, size_t n) {
  /*chpl_gpu_ensure_context();*/

  assert(chpl_gpu_is_device_ptr(dst));

  CHPL_GPU_DEBUG("Copying %zu bytes from host to device\n", n);

  CUDA_CALL(cuMemcpyHtoD((CUdeviceptr)dst, src, n));
}

void chpl_gpu_launch_kernel(int ln, int32_t fn,
                            const char* fatbinData, const char* name,
                            int grd_dim_x, int grd_dim_y, int grd_dim_z,
                            int blk_dim_x, int blk_dim_y, int blk_dim_z,
                            int nargs, ...) {
  va_list args;
  va_start(args, nargs);
  chpl_gpu_launch_kernel_help(ln, fn,
                              fatbinData, name,
                              grd_dim_x, grd_dim_y, grd_dim_z,
                              blk_dim_x, blk_dim_y, blk_dim_z,
                              nargs, args);
  va_end(args);
}

void chpl_gpu_launch_kernel_flat(int ln, int32_t fn,
                                 const char* fatbinData, const char* name,
                                 int num_threads, int blk_dim, int nargs, ...) {
  int grd_dim = (num_threads+blk_dim-1)/blk_dim;

  va_list args;
  va_start(args, nargs);
  chpl_gpu_launch_kernel_help(ln, fn,
                              fatbinData, name,
                              grd_dim, 1, 1,
                              blk_dim, 1, 1,
                              nargs, args);
  va_end(args);
}

bool chpl_gpu_has_context() {
  CUcontext cuda_context = NULL;

  CUresult ret = cuCtxGetCurrent(&cuda_context);

  if (ret == CUDA_ERROR_NOT_INITIALIZED || ret == CUDA_ERROR_DEINITIALIZED) {
    return false;
  }
  else {
    return cuda_context != NULL;
  }
}

static bool chpl_gpu_device_alloc = false;

void chpl_gpu_enable_device_alloc() {
  chpl_gpu_device_alloc = true;
}

void chpl_gpu_disable_device_alloc() {
  chpl_gpu_device_alloc = false;
}

void* chpl_gpu_mem_array_alloc(size_t size, chpl_mem_descInt_t description,
                               int32_t lineno, int32_t filename) {
  chpl_gpu_ensure_context();

  CHPL_GPU_DEBUG("chpl_gpu_mem_array_alloc called. Size:%d file:%s line:%d\n", size,
               chpl_lookupFilename(filename), lineno);

  CUdeviceptr ptr = 0;
  if (size > 0) {
    chpl_memhook_malloc_pre(1, size, description, lineno, filename);
#ifdef CHPL_GPU_MEM_UVA
    if (chpl_gpu_device_alloc) {
      CUDA_CALL(cuMemAlloc(&ptr, size));
    }
    else {
      void* mem = chpl_mem_alloc(size, description, lineno, filename);
      CHPL_GPU_DEBUG("\tregistering %p\n", mem);
      CUDA_CALL(cuMemHostRegister(mem, size, CU_MEMHOSTREGISTER_PORTABLE));
      CUDA_CALL(cuMemHostGetDevicePointer(&ptr, mem, 0));
    }
#else
    CUDA_CALL(cuMemAllocManaged(&ptr, size, CU_MEM_ATTACH_GLOBAL));
#endif
    chpl_memhook_malloc_post((void*)ptr, 1, size, description, lineno, filename);

    CHPL_GPU_DEBUG("chpl_gpu_mem_array_alloc returning %p\n", (void*)ptr);
  }
  else {
    CHPL_GPU_DEBUG("chpl_gpu_mem_array_alloc returning NULL (size was 0)\n");
  }


  return (void*)ptr;

}

void* chpl_gpu_mem_alloc(size_t size, chpl_mem_descInt_t description,
                         int32_t lineno, int32_t filename) {
  chpl_gpu_ensure_context();

  CHPL_GPU_DEBUG("chpl_gpu_mem_alloc called. Size:%d file:%s line:%d\n", size,
               chpl_lookupFilename(filename), lineno);

  CUdeviceptr ptr = 0;
  if (size > 0) {
    chpl_memhook_malloc_pre(1, size, description, lineno, filename);
#ifdef CHPL_GPU_MEM_UVA
    void* mem = chpl_mem_alloc(size, description, lineno, filename);
    CHPL_GPU_DEBUG("\tregistering %p\n", mem);
    CUDA_CALL(cuMemHostRegister(mem, size, CU_MEMHOSTREGISTER_PORTABLE));
    CUDA_CALL(cuMemHostGetDevicePointer(&ptr, mem, 0));
#else
    CUDA_CALL(cuMemAllocManaged(&ptr, size, CU_MEM_ATTACH_GLOBAL));
#endif
    chpl_memhook_malloc_post((void*)ptr, 1, size, description, lineno, filename);

    CHPL_GPU_DEBUG("chpl_gpu_mem_alloc returning %p\n", (void*)ptr);
  }
  else {
    CHPL_GPU_DEBUG("chpl_gpu_mem_alloc returning NULL (size was 0)\n");
  }


  return (void*)ptr;

}

void* chpl_gpu_mem_calloc(size_t number, size_t size,
                          chpl_mem_descInt_t description,
                          int32_t lineno, int32_t filename) {
  chpl_gpu_ensure_context();

  CHPL_GPU_DEBUG("chpl_gpu_mem_calloc called. Size:%d\n", size);

  CUdeviceptr ptr = (CUdeviceptr)chpl_gpu_mem_alloc(number*size, description,
                                                    lineno, filename);
  CUDA_CALL(cuMemsetD8(ptr, 0, size));
  return (void*)ptr;
}

void* chpl_gpu_mem_realloc(void* memAlloc, size_t size,
                           chpl_mem_descInt_t description,
                           int32_t lineno, int32_t filename) {
  chpl_gpu_ensure_context();

  CHPL_GPU_DEBUG("chpl_gpu_mem_realloc called. Size:%d\n", size);

  assert(chpl_gpu_is_device_ptr(memAlloc));

  size_t cur_size = chpl_gpu_get_alloc_size(memAlloc);

  if (size == cur_size) {
    return memAlloc;
  }

  // TODO we could probably do something smarter, especially for the case where
  // the new allocation size is smaller than the original allocation size.
  CUdeviceptr ptr = (CUdeviceptr)chpl_gpu_mem_alloc(size, description, lineno,
                                                    filename);
  CUDA_CALL(cuMemcpyDtoD(ptr, (CUdeviceptr)memAlloc, cur_size));
  CUDA_CALL(cuMemFree((CUdeviceptr)memAlloc));

  return (void*)ptr;
}

void* chpl_gpu_mem_memalign(size_t boundary, size_t size,
                            chpl_mem_descInt_t description,
                            int32_t lineno, int32_t filename) {
  chpl_gpu_ensure_context();

  CHPL_GPU_DEBUG("chpl_gpu_mem_memalign called. Size:%d\n", size);
  chpl_internal_error("Not ready to allocate aligned memory on GPU, yet.");

  // ENGIN: I don't know if it is possible to allocate memory with custom
  // alignment on GPU. It looks like GPUs typically have a default alignment
  // (512?) that cannot be changed. I don't think we'd need more than that
  // today, and if we want, we can play some pointer games to return something
  // with a larger alignment here.
  // In any case, if 512 is the default alignment, we can just malloc and return
  // the result as long as the boundary is <=512 and power of 2?

  return NULL;
}

void chpl_gpu_mem_free(void* memAlloc, int32_t lineno, int32_t filename) {
  chpl_gpu_ensure_context();

  CHPL_GPU_DEBUG("chpl_gpu_mem_free called. Ptr:%p file:%s line:%d\n", memAlloc,
               chpl_lookupFilename(filename), lineno);

  chpl_memhook_free_pre(memAlloc, 0, lineno, filename);

  if (memAlloc != NULL) {
    assert(chpl_gpu_is_device_ptr(memAlloc));
#ifdef CHPL_GPU_MEM_UVA
    if (!chpl_gpu_allocated_on_host(memAlloc)) {
      CUDA_CALL(cuMemFree((CUdeviceptr)memAlloc));
    }
    else {
      CUDA_CALL(cuMemHostUnregister(memAlloc));
      chpl_mem_free(memAlloc, lineno, filename);
    }
#else
    CUDA_CALL(cuMemFree((CUdeviceptr)memAlloc));
#endif
  }
}

#endif // HAS_GPU_LOCALE

