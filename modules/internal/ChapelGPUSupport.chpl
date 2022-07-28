module ChapelGPUSupport {
  use ChapelBase;

  extern var chpl_gpu_debug: bool;

  config const debugGPU = false;

  // by virtue of module initialization:
  chpl_gpu_debug = debugGPU;
}
