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
    chpl_comm_request_prefetch(node, robjaddr: c_void_ptr,
        slice_desc, slice_desc_size, consistent): prefetch_entry_t;

  /*extern proc */
    /*chpl_comm_prefetch(node, raddr, size,*/
      /*serialized_base_idx): prefetch_entry_t;*/
  
  extern proc
    entry_has_data(handle): bool;
  /*extern proc */
    /*get_prefetched_data(handle, offset, size, ref dest): c_int;*/

  extern proc
    get_prefetched_data(accessor: c_void_ptr, handle, size, ref idx,
        ref isPrefetched, ref data);

  extern proc 
    reprefetch_single_entry(handle);

  extern proc
    get_data_from_prefetch_entry(handle): c_void_ptr;
  extern proc
    prefetch_entry_init_seqn_n(handle, offset);

  extern proc
    start_read(handle);

  extern proc
    stop_read(handle);

  inline proc getData(handle) {
    return get_data_from_prefetch_entry(handle);
  }

  class PrefetchHook {
    var x = 10;

    iter dsiSerialize() {
      halt("This shouldn't have been called", x);
      var dummyPtr: c_void_ptr;
      var dummySize: size_t;
      yield (dummyPtr, dummySize, false);
    }

    proc dsiGetSerializedObjectSize(): size_t {
      halt("This shouldn't have been called", x);
      var val: size_t;
      return val;
    }

    iter dsiSerialize(slice_desc) {
      halt("This shouldn't have been called", x);
      var dummyPtr: c_void_ptr;
      var dummySize: size_t;
      yield (dummyPtr, dummySize, false);
    }

    proc dsiGetSerializedObjectSize(slice_desc): size_t {
      halt("This shouldn't have been called", x);
      var val: size_t;
      return val;
    }

    proc requestPrefetch(nodeId, otherObj, consistent=true) {
      halt("This shouldn't have been called");
    }

    proc requestPrefetch(nodeId, otherObj, sliceDesc,
        consistent=true) {
      halt("This shouldn't have been called");
    }

    proc updatePrefetch() {
      halt("This shouldn't have been called");
    }

    inline proc accessPrefetchedData(localeId, idx) {
      halt("This shouldn't have been called");
      var isPrefetched = false;
      var dummyPtr: c_ptr(real);
      return (isPrefetched, dummyPtr);
    }

    proc finalizePrefetch() {
      halt("This shouldn't have been called");
    }

    proc getByteIndex(data: c_void_ptr, __idx: c_void_ptr) {
      halt("This shouldn't have been called");
      var dummy: uint(64);
      return dummy;
    }

    proc test() {
      writeln("Superclass", x);
    }
  }

  class GenericPrefetchHook:PrefetchHook {
    var obj;
    var handles: c_ptr(prefetch_entry_t);
    //FIXME this is a dangerous field now, since we can evict data with
    //no callback to this object
    var hasData: [Locales.domain] bool = false; // only to be use for reprefetch

    proc GenericPrefetchHook(obj) {
      handles = c_calloc(prefetch_entry_t, numLocales);
      x = 20;
    }

    iter dsiSerialize(slice_desc) {
      for val in obj.dsiSerialize(slice_desc:c_ptr(obj.idxType)) do yield val;
    }
    proc dsiGetSerializedObjectSize(slice_desc): size_t {
      var size = 0: size_t;
      for v in 
          obj.dsiGetSerializedObjectSize(slice_desc:c_ptr(obj.idxType)) {
        size += v;
      }
      return size;
    }

    iter dsiSerialize() {
      for val in obj.dsiSerialize() do yield val;
    }
    proc dsiGetSerializedObjectSize(): size_t {
      var size: size_t;
      for v in obj.dsiGetSerializedObjectSize() {
        size += v;
      }
      return size;
    }

    // here obj needs to be a wide class refernece to another hook
    proc requestPrefetch(nodeId, otherObj, consistent=true) {
      var robjaddr = __primitive("_wide_get_addr",
          otherObj.prefetchHook);

      if nodeId!=here.id {
        handles[nodeId] = chpl_comm_request_prefetch(nodeId, robjaddr,
            c_nil, 0, consistent);
        hasData[nodeId] = true;
      }
    }

    proc requestPrefetch(nodeId, otherObj, sliceDesc,
        consistent=true) {
      var robjaddr = __primitive("_wide_get_addr",
          otherObj.prefetchHook);

      if nodeId!=here.id {
        /*writeln(here, " ", sliceDesc);*/
        /*halt("REACHED END");*/
        var (sliceDescPtr, sliceDescSize, dummyBool) =
          convertToSerialChunk(sliceDesc);
        handles[nodeId] = chpl_comm_request_prefetch(nodeId, robjaddr,
            sliceDescPtr, sliceDescSize, consistent);
        hasData[nodeId] = true;
      }
    }

    proc updatePrefetch() {
      for i in 0..#numLocales {
        if hasData[i] {
          /*writeln(here.id, " will update from ", i);*/
          reprefetch_single_entry(handles[i]);
        }
      }
    }

    inline proc accessPrefetchedData(localeId, idx) {
      var localIdx = idx;
      const handle = handles[localeId];
      /*start_read(handles[localeId]);*/
      /*if is_c_nil(handles[localeId]) || !hasData[localeId] {*/
      if(!entry_has_data(handle)) {
        /*writeln(here, " doesn't have prefetched data from ", */
            /*localeId, " with index ", idx);*/
        /*stop_read(handles[localeId]);*/
        var dummy: obj.eltType;
        return (false, dummy);
      }

      // TODO here data must be accessed only once therefore
      // getByteIndex must be called from runtime from insde
      // get_prefetched_data_addr

      /*const __data = getData(handle);*/
      /*const deserialIdx = obj.getByteIndex(getData(handle), idx);*/
      var isPrefetched: int;
      var thisaddr = __primitive("_wide_get_addr", this);
      var data: obj.eltType;
      get_prefetched_data(thisaddr, handle, 8, localIdx, isPrefetched,
          data);

      /*if isPrefetched == 0 {*/
        /*const cast_data = __data:c_ptr(int);*/
        /*writeln("First two data: ", cast_data[0], " ", cast_data[1]);*/
        /*writeln(here, " have prefetched data from ", */
            /*localeId, " but not with serial index ", deserialIdx, */
            /*" for index ", idx);*/
        /*stop_read(handles[localeId]);*/
      /*}*/
      /*stop_read(handles[localeId]);*/
      return (isPrefetched!=0, data);
    }

    proc finalizePrefetch() {
      for i in 0..#numLocales {
        // 2 acquires are added by the current finalization logic
        // this may not be necessary
        prefetch_entry_init_seqn_n(handles[i], 0);
      }
    }

    inline proc getByteIndex(data: c_void_ptr, __idx: c_void_ptr) {
      var idx = __idx:c_ptr(obj.rank*obj.idxType);

      return obj.getByteIndex(data, idx.deref());
    }

    proc test() {
      writeln("Subclass", x);
    }
  }

  export proc __get_byte_idx_wrapper(__obj: c_void_ptr,
      data: c_void_ptr, idx: c_void_ptr) {
    var obj = __obj:PrefetchHook;
    return obj.getByteIndex(data, idx);
  }

  export proc __serialized_obj_size_wrapper(__obj: c_void_ptr,
      slice_desc: c_void_ptr, slice_desc_size: size_t): size_t {
    var obj = __obj:PrefetchHook;
    if slice_desc_size > 0 then
      return obj.dsiGetSerializedObjectSize(slice_desc);
    else
      return obj.dsiGetSerializedObjectSize();

  }

  export proc __serialize_wrapper(__obj: c_void_ptr, __buf: c_void_ptr,
      bufsize: size_t, slice_desc: c_void_ptr, slice_desc_size: size_t) {

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
    if slice_desc_size > 0 {
      for chunk in obj.dsiSerialize(slice_desc) {
        const chunkSize = chunk[2];
        //memcpy to buffer
        c_memcpy(c_ptrTo(buf[curBufferSize]), //there was a cast here
            chunk[1]:c_ptr(bufferEltType), chunkSize);

        if chunk[3] {
          c_free(chunk[1]:c_ptr(bufferEltType));
        }

        curBufferSize += chunkSize;
      }
    }
    else {
      for chunk in obj.dsiSerialize() {
        const chunkSize = chunk[2];
        //memcpy to buffer
        c_memcpy(c_ptrTo(buf[curBufferSize]), //there was a cast here
            chunk[1]:c_ptr(bufferEltType), chunkSize);

        curBufferSize += chunkSize;
      }
    }
  }

  // TODO this needs some error checking
  // this will be dsi-facing helper
  inline proc convertToSerialChunk(a: []) {
    const startIdx = a.domain.low; // or first?
    return (c_ptrTo(a[startIdx]):c_void_ptr,
        getSize(a.size, a._value.eltType),
        false); //buffer needs to be freed?

  }

  // TODO this needs some error checking
  // this will be dsi-facing helper
  inline proc convertToSerialChunk(a: [], count) {
    const startIdx = a.domain.low; // or first?
    return (c_ptrTo(a[startIdx]):c_void_ptr,
        getSize(count, a._value.eltType),
        false); //buffer needs to be freed?

  }

  inline proc convertToSerialChunk(a: integral) {
    var dyn_mem = c_malloc(a.type, 1);
    dyn_mem[0] = a;
    return (dyn_mem:c_void_ptr,
        getSize(1, a.type),
        true); //buffer needs to be freed?

  }

  inline proc getElementArrayAtOffset(data: c_void_ptr, offset, 
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
