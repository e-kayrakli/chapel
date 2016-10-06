module PrefetchHooks {
  use BlockDist;
  // this is currently a totatlly random value
  config param initSerializeBufSize = 1024;
  config param serializeBufferGrowthFactor = 1.5;

  extern type c_nodeid_t;
  /*extern class prefetch_entry_t {*/
    /*var data: c_void_ptr;*/
  /*}*/
  extern type prefetch_entry_t;
  extern proc
    chpl_comm_request_prefetch(node, robjaddr: c_void_ptr):
      prefetch_entry_t;

  /*extern proc */
    /*chpl_comm_prefetch(node, raddr, size,*/
      /*serialized_base_idx): prefetch_entry_t;*/
  
  extern proc 
    get_prefetched_data(handle, offset, size, ref dest): c_int;

  extern proc 
    get_prefetched_data_addr(handle, offset, size, ref isPrefetched):
      c_void_ptr;

  extern proc
    get_data_from_prefetch_entry(handle): c_void_ptr;

  inline proc getData(handle) {
    return get_data_from_prefetch_entry(handle);
  }

  class PrefetchHook {
    var x = 10;

    iter dsiSerialize() {
      halt("This shouldn't have been called", x);
      var dummyPtr: c_void_ptr;
      var dummySize: size_t;
      yield (dummyPtr, dummySize);
    }

    proc dsiGetSerializedObjectSize(): size_t {
      halt("This shouldn't have been called", x);
      var val: size_t;
      return val;
    }

    proc requestPrefetch(nodeId, otherObj) {
      halt("This shouldn't have been called");
    }
    proc accessPrefetchedData(localeId, idx) {
      halt("This shouldn't have been called");
      var isPrefetched = false;
      var dummyPtr: c_ptr(real);
      return (isPrefetched, dummyPtr);
    }

    proc test() {
      writeln("Superclass", x);
    }
  }

  class GenericPrefetchHook:PrefetchHook {
    var obj;
    var handles: c_ptr(prefetch_entry_t);

    proc GenericPrefetchHook(obj) {
      handles = c_calloc(prefetch_entry_t, numLocales);
      x = 20;
    }

    iter dsiSerialize() {
      for val in obj.dsiSerialize() do yield val;
    }
    proc dsiGetSerializedObjectSize(): size_t {
      return + reduce obj.dsiGetSerializedObjectSize();
    }

    // here obj needs to be a wide class refernece to another hook
    proc requestPrefetch(nodeId, otherObj) {
      var robjaddr = __primitive("_wide_get_addr",
          otherObj.prefetchHook);

      if nodeId!=here.id {
        handles[nodeId] = chpl_comm_request_prefetch(nodeId, robjaddr);
      }
    }

    proc accessPrefetchedData(localeId, idx) {
      const handle = handles[localeId];
      const deserialIdx = obj.getByteIndex(getData(handle), idx);
      var isPrefetched: int;
      const data = get_prefetched_data_addr(handle, 8, deserialIdx,
          isPrefetched);

      return (isPrefetched, data:c_ptr(obj.eltType));
    }

    proc test() {
      writeln("Subclass", x);
    }
  }

  // I dont like obj being passed here
  proc accessPrefetchedData(obj, handle, idx) {
    const deserialIdx = obj.getByteIndex(getData(handle), idx);
    var isPrefetched: int;
    const data = get_prefetched_data_addr(handle, 8, deserialIdx,
        isPrefetched);

    return (isPrefetched, data:c_ptr(obj.eltType));
  }

  class OtherClass {
    proc someProc() {
      halt("do nothing");
    }
  }

  export proc __serialized_obj_size_wrapper(__obj: c_void_ptr): size_t {
    /*writeln("Exported proc called");*/
    var obj = __obj:PrefetchHook;
    /*__obj.test();*/

    /*halt(" REACHED END ");*/
    /*var dummy: size_t;*/
    /*return dummy;*/
    return obj.dsiGetSerializedObjectSize();
  }

  export proc __serialize_wrapper(__obj: c_void_ptr, __buf: c_void_ptr,
      bufsize: size_t) {

    type bufferEltType = uint(8);
    var obj = __obj:PrefetchHook;
    var buf = __buf:c_ptr(bufferEltType);

    var curBufferSize = 0:uint;

    // chunk will be a heterogeneous tuple of
    //
    // (ref to first index:void, numBytes)
    //
    // currently I am providing a helper convertToSerialChunk that takes
    // a rectangular array and returns the tuple we need. if the format
    // is changed, only implementation of that function should change
    for chunk in obj.dsiSerialize() {
      const chunkSize = chunk[2];
      //memcpy to buffer
      c_memcpy(c_ptrTo(buf[curBufferSize]), //there was a cast here
          chunk[1]:c_ptr(bufferEltType), chunkSize);

      curBufferSize += chunkSize;
    }
 
  }

  // TODO this needs some error checking
  // this will be dsi-facing helper
  inline proc convertToSerialChunk(a: []) {
    const startIdx = a.domain.low; // or first?
    return (c_ptrTo(a[startIdx]):c_void_ptr,
        getSize(a.size, a._value.eltType));

  }

  proc getElementArrayAtOffset(data: c_void_ptr, offset: int, 
      type eltType) {

    var castPtr = data:c_ptr(uint(8));
    return c_ptrTo(castPtr[offset]):c_ptr(eltType);
  }


  // a sizeof alternative
  inline proc getSize(numElems, type eltType) {
    extern proc sizeof(type x): size_t;
    return numElems.safeCast(size_t)*sizeof(eltType);
  }

}
