module ChapelContextSupport {

  pragma "context type"
  record Context {
    var taskId: int;
    var numTasks: int;
  }

  /*export "always resolve function"*/
  /*proc resetBarrierAtContext(n: int, ref barrier: Barrier) {*/
    /*try! barrier.reset(((barrier.bar):(unmanaged aBarrier)).n*n);*/
  /*}*/
}
