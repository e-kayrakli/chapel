module ChapelContextSupport {

  pragma "context type"
  record Context {
    param rank: int;

    type idType = if rank==1 then int else rank*int;
    var taskId: idType;
    var numTasks: idType;

    proc init(param rank, taskId, numTasks) {
      this.rank=rank;
      this.complete();
      this.taskId = taskId;
      this.numTasks = numTasks;
    }
  }

  /*export "always resolve function"*/
  /*proc resetBarrierAtContext(n: int, ref barrier: Barrier) {*/
    /*try! barrier.reset(((barrier.bar):(unmanaged aBarrier)).n*n);*/
  /*}*/
}
