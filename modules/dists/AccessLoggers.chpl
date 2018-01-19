require "/home/ngnk/code/chapel/versions/fork_dev2/chapel/modules/dists/log_buffer/byte_buffer.c", 
        "/home/ngnk/code/chapel/versions/fork_dev2/chapel/modules/dists/log_buffer/log_buffer.c",
        "/home/ngnk/code/chapel/versions/fork_dev2/chapel/modules/dists/log_buffer/log_buffer.h",
        "/home/ngnk/build/lz4/lib/lz4.c",
        "/home/ngnk/build/lz4/lib/lz4frame.c",
        "/home/ngnk/build/lz4/lib/lz4hc.c",
        "/home/ngnk/build/lz4/lib/xxhash.c",
        "/home/ngnk/build/lz4/lib/lz4frame.h",
        "/home/ngnk/build/lz4/lib/lz4frame_static.h",
        "/home/ngnk/build/lz4/lib/lz4.h",
        "/home/ngnk/build/lz4/lib/lz4hc.h",
        /*"/home/ngnk/build/lz4/lib/lz4opt.h",*/
        "/home/ngnk/build/lz4/lib/xxhash.h";

extern type log_buffer_t;
extern proc init_log_buffer(ref lbuf, num_buffers: uint(32),
                            rank: uint(8));
extern proc destroy_log_buffer(ref lbuf);
extern proc flush_buffer(ref lbuf);
extern proc append_index(ref lbuf, args...);

class AccessLogger {
  var buf: log_buffer_t;

  proc init(rank, numBuffers=here.maxTaskPar) {
    init_log_buffer(buf, numBuffers:uint(32), rank:uint(8));
  }

  proc destroy() {
    destroy_log_buffer(buf);
  }

  inline proc log(idx) where isTuple(idx) {
    append_index(buf, (...idx));
  }

  inline proc log(idx) where !isTuple(idx) {
    append_index(buf, idx);
  }

  proc flush() {
    flush_buffer(buf);
  }
}

/*var l = new AccessLogger(rank=1);*/
/*forall idx in {0..1000000} do*/
  /*l.log(idx);*/

/*l.flush();*/



