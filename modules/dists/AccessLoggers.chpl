require "/home/ngnk/code/chapel/versions/fork_dev2/chapel/modules/dists/log_buffer/byte_buffer.c", 
        "/home/ngnk/code/chapel/versions/fork_dev2/chapel/modules/dists/log_buffer/log_buffer.c",
        "/home/ngnk/code/chapel/versions/fork_dev2/chapel/modules/dists/log_buffer/log_buffer.h",
        "/home/ngnk/code/chapel/versions/fork_dev2/chapel/modules/dists/log_buffer/compress.c",
        "/home/ngnk/code/chapel/versions/fork_dev2/chapel/modules/dists/log_buffer/compress.h",
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
                            rank: uint(8), byte_buf_size: c_int);
extern proc destroy_log_buffer(ref lbuf);
extern proc flush_buffer(ref lbuf);
extern proc append_index(ref lbuf, args...);
extern proc get_compression_stats(ref lbuf, 
                                  ref uncomp_size, ref comp_size): c_int;

config const defaultByteBufferSize = 10000000;
class AccessLogger {
  var buf: log_buffer_t;

  var samplingCounter = 0;
  var samplingPeriod = 1;

  proc init(rank, numBuffers=here.maxTaskPar,
            byteBufferSize=defaultByteBufferSize, samplingRate) {

    if samplingRate <= 0 then
      halt("sampling rate must be positive and <=1.0");
    if samplingRate > 1.0 then
      halt("sampling rate must be positive and <=1.0");

    init_log_buffer(buf, numBuffers:uint(32), rank:uint(8),
                    byteBufferSize:int(32));

    samplingPeriod = (1/samplingRate):int;
  }

  proc destroy() {
    flush();
    var uncompSize: size_t;
    var compSize: size_t;
    var collected = get_compression_stats(buf, uncompSize, compSize);
    if collected {
      writeln(here);
      writeln("Uncompressed size : ", uncompSize);
      writeln("Compressed size : ", compSize);
      writeln("Compression ratio : ", 1.0*compSize/uncompSize);
    }
    destroy_log_buffer(buf);
  }

  inline proc log(idx) {
    if samplingCounter % samplingPeriod == 0 then
      __do_log(idx);
    samplingCounter += 1;
  }

  inline proc __do_log(idx) where isTuple(idx) {
    append_index(buf, (...idx));
  }

  inline proc __do_log(idx) where !isTuple(idx) {
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



