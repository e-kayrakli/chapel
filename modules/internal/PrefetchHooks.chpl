module PrefetchHooks {
  use BlockDist;
  use Time;
  // this is currently a totatlly random value
  config param initSerializeBufSize = 1024;
  config param serializeBufferGrowthFactor = 1.5;
  config param measureTime = false;
  config param debugPrefetch = false;
  config param prefetchTiming = false;

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
    get_prefetched_data_addr(accessor: c_void_ptr, handle, size, ref idx,
        ref isPrefetched): c_void_ptr;
  extern proc 
    reprefetch_single_entry(handle);

  extern proc
    get_data_from_prefetch_entry(handle): c_void_ptr;
  extern proc
    prefetch_entry_init_seqn_n(handle, offset);

  extern proc create_prefetch_handle(ref handle);

  extern proc initialize_prefetch_handle(owner_obj, origin_node,
      robjaddr, new_entry, prefetch_size, slice_desc, slice_desc_size,
      consistent): c_void_ptr;

  extern proc update_prefetch_handle(owner_obj, origin_node,
      robjaddr, new_entry, prefetch_size, slice_desc, slice_desc_size,
      consistent): c_void_ptr;

  extern proc get_lock_offset(handle, addr): int(32);

  inline proc getData(handle) {
    return get_data_from_prefetch_entry(handle);
  }

  private inline proc debug_writeln(args...) {
    if debugPrefetch then
      writeln((...args));
  }

  class PrefetchHook {
    var x = 10;

    proc reportPrefetchTimes() {
      halt("This shouldn't have been called", x);
    }

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

    proc requestPrefetch(localeIdx, otherObj, consistent=true) {
      halt("This shouldn't have been called");
    }

    proc requestPrefetch(localeIdx, otherObj, sliceDesc,
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

    inline proc accessPrefetchedDataRef(h, idx) {
      halt("This shouldn't have been called");
      var isPrefetched = false;
      var dummyPtr: c_ptr(uint(8));
      return (dummyPtr, -1);
    }

    proc finalizePrefetch() {
      halt("This shouldn't have been called");
    }

    proc getByteIndex(data: c_void_ptr, __idx: c_void_ptr) {
      halt("This shouldn't have been called");
      var dummy: uint(64);
      return dummy;
    }

    inline proc hasPrefetchedFrom(localeId) {
      halt("This shouldn't have been called");
      return false;;
    }

    proc doPrefetch(destLocaleId, srcLocaleId, srcObj, slice_desc,
        slice_desc_size: size_t, consistent) {
      halt("This shouldn't have been called");
      var new_handle_ptr: prefetch_entry_t;
      return new_handle_ptr;
    }
    proc reprefetch(destLocaleId, srcLocaleId, srcObj, slice_desc,
        slice_desc_size: size_t, consistent) {
      halt("This shouldn't have been called");
    }
    /*inline proc getUnpackedData(localeIdx) {*/
      /*halt("This shouldn't have been called");*/
      /*var c: c_void_ptr;*/
      /*return c;*/
    /*}*/

    proc test() {
      writeln("Superclass", x);
    }

    pragma "no local return"
    proc unifiedAccessPrefetchedData(locIdx, i) {
      halt("This shouldn't have been called");
      var dummy: c_void_ptr;
      return (false, dummy);
    }
  }

  inline proc getNewPrefetchHook(obj, type unpackType, localeContainer) {
    return new GenericPrefetchHook(obj, unpackType, true,
        localeContainer);
  }

  inline proc getNewPrefetchHook(obj) {
    return new GenericPrefetchHook(obj, int, false); //int is dummy
  }

  inline proc getNewPrefetchHook(obj, localeContainer) {
    return new GenericPrefetchHook(obj, int, false,
        localeContainer);
  }

  class GenericPrefetchHook:PrefetchHook {
    var obj;
    type unpackType;
    param unpackAccess;

    var hasLocaleContainer = false;
    var localeDom: domain(obj.rank);
    var localeIDs: [localeDom] int;

    // for performance debugging
    var accessPrepTime = 0.0;
    var accessRealTime = 0.0;
    var accessOutTime = 0.0;
    var t = new Timer();

    var prefetchTimer = new Timer();
    var reprefetchTimer = new Timer();
    var accessTimer = new Timer();

    /*var handles: c_ptr(prefetch_entry_t);*/
    /*var handles: [localeDom] prefetch_entry_t;*/
    var handles: c_ptr(prefetch_entry_t);
    var localeDomDimSize: localeDom.rank*int;
    var localeDomSize: int;

    var unpackedData: [localeDom] unpackType;
    //FIXME this is a dangerous field now, since we can evict data with
    //no callback to change this array
    var hasData: [localeDom] bool = false; // only to be use for reprefetch
    
    var commInProgress: [localeDom] sync bool;


    /*proc GenericPrefetchHook(obj, type unpackType, param unpackAccess) {*/
      /*handles = c_calloc(prefetch_entry_t, numLocales);*/
      /*unpackedData = c_calloc(unpackType, numLocales);*/
      /*localeD = {1..0};*/
      /*x = 20;*/
    /*}*/

    proc GenericPrefetchHook(obj, type unpackType, param unpackAccess,
        localeContainer: [?D] locale) {
      localeDomSize = D.numIndices;
      handles = c_calloc(prefetch_entry_t, localeDomSize);
      /*unpackedData = c_calloc(unpackType, numLocales);*/
      localeDom = D;
      forall (i,l) in zip(localeIDs, localeContainer) do i = l.id;
      hasLocaleContainer = true;

      for (idx,dim) in zip(1..localeDomDimSize.size, D.dims()) {
        localeDomDimSize[idx] = dim.size;
      }

      for i in 0..#localeDomSize do create_prefetch_handle(handles[i]);
    }

    pragma "no local return"
    inline proc unifiedAccessPrefetchedData(locIdx, i,
        out prefetched: bool) ref {
      local {
        if prefetchTiming then accessTimer.start();
        if unpackAccess {
          if hasPrefetchedFrom(locIdx) {
            ref unpackedDataTmp = unpackedData[locIdx];
            if unpackedDataTmp.domain.member(i) {
              ref retTmp = unpackedDataTmp[i];
              prefetched = true;
              // NOTE: I am not sure why we always get a wide pointer out
              // of this. Maybe the whole method whould be `local`ized.
              // TODO but first, we can use C arrays for internal arrays
              // like handles and unpackedData. I believe there will be
              // significant speedup un prefetched data accesses
              if __primitive("is wide pointer", retTmp) {
                const lockOffset = get_lock_offset(
                    handleFromLocaleIdx(locIdx),
                    __primitive("_wide_get_addr", retTmp));
                if prefetchTiming then accessTimer.stop();
                return __primitive("gen prefetch ptr", retTmp, lockOffset);
              }
            }
          }
        }
        else {
          const h = handleFromLocaleIdx(locIdx);
          var (data, backLinkOffset) = accessPrefetchedDataRef(h, i);
          prefetched = !is_c_nil(data);
          if prefetchTiming then accessTimer.stop();
          return __primitive("gen prefetch ptr", data, backLinkOffset);
        }
        prefetched = false;
        var dummyPtr: c_ptr(obj.eltType);
        if prefetchTiming then accessTimer.stop();
        return __primitive("gen prefetch ptr", dummyPtr, -1);
      }
    }

    iter dsiSerialize(slice_desc) {
      for val in obj.dsiSerialize(slice_desc:c_ptr(obj.idxType)) do
        yield val;
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
      debug_writeln("getting size on ", here);
      var size = 0: size_t;
      for v in obj.dsiGetSerializedObjectSize() {
        size += v;
      }
      return size;
    }

    //prefetch-reprefetch helpers
    pragma "no remote memory fence"
    inline proc __getSerializedSize(destLocaleId, srcLocaleId, srcObj,
        slice_desc, slice_desc_size) {
      var size = 0: size_t;

      on Locales[srcLocaleId] {
        // write size to destLocales handle's size

        var slice_desc_local: c_ptr(uint(8));

        if slice_desc_size > 0 {
          slice_desc_local =
            c_malloc(uint(8), slice_desc_size);
          __primitive("chpl_comm_array_get", slice_desc_local[0],
              destLocaleId, (slice_desc:c_ptr(uint(8)))[0],
              slice_desc_size);
        }

        size = __serialized_obj_size_wrapper(srcObj,
            slice_desc_local, slice_desc_size);
      }

      return size;
    }

    pragma "no remote memory fence"
    inline proc __getSerializedData(destLocaleId, srcLocaleId, srcObj,
        slice_desc, slice_desc_size: size_t, data, size) {

      on Locales[srcLocaleId] {
        // write data to destLocales handle's data
        const size_local = size;
        var slice_desc_local: c_ptr(uint(8));

        if slice_desc_size > 0 {
          slice_desc_local = c_malloc(uint(8),
              slice_desc_size);
          __primitive("chpl_comm_array_get", slice_desc_local[0],
              destLocaleId, (slice_desc:c_ptr(uint(8)))[0],
              slice_desc_size);
        }

        //NOTE for now we are serializing the data ad hoc. previously,
        //when we relied on AM's data serialization used to start right
        //after responding to size query. This is a TODO for now
        var local_buffer = c_malloc(uint(8), size_local):c_ptr(uint(8));

        __serialize_wrapper(srcObj, local_buffer, size_local,
            slice_desc_local, slice_desc_size);
        __primitive("chpl_comm_array_put", local_buffer[0], destLocaleId,
            data[0], size_local);
      }
    }

    // this is only used for reprefetching, where all we have is locale
    // ID. FIXME this can be optimized
    inline proc handleFromLocaleID(id) {
      for idx in localeDom {
        if localeIDs[idx] == id then return handleFromLocaleIdx(idx);
      }

      halt("This shouldn't have happened");
      var dummy: prefetch_entry_t;
      return dummy;
    }

    inline proc handleFromLocaleIdx(idx) {
      var _idx = -1;
      if isTuple(idx) {
        if idx.size == 1 {
          return handles[idx];
        }
        if idx.size == 2 {
          return handles[idx[1]*localeDomDimSize[2]+idx[2]];
        }
        if idx.size == 3 {
          return handles[idx[1]*localeDomDimSize[2]*
            localeDomDimSize[3]+idx[2]*localeDomDimSize[3]+idx[3]];
        }
      }
      else {
        return handles[idx];
      }
      halt("not ready for this - handleFromLocaleIdx");
      return handles[0];
    }
    inline proc handleFromLocaleIdx(idx) ref {
      var _idx = -1;
      if isTuple(idx) {
        if idx.size == 1 {
          return handles[idx];
        }
        if idx.size == 2 {
          return handles[idx[1]*localeDomDimSize[2]+idx[2]];
        }
        if idx.size == 3 {
          return handles[idx[1]*localeDomDimSize[2]*
            localeDomDimSize[3]+idx[2]*localeDomDimSize[3]+idx[3]];
        }
      }
      else {
        return handles[idx];
      }
      halt("not ready for this - handleFromLocaleIdx");
      return handles[0];
    }

    pragma "no remote memory fence"
    proc reprefetch(destLocaleId, srcLocaleId, srcObj, slice_desc,
        slice_desc_size: size_t, consistent) {

      if prefetchTiming then reprefetchTimer.start();

      if destLocaleId != here.id {
        halt("doPrefetch can only be called from the prefetching \
            locale");
      }

      /*writeln(here, " prereprefetch  : ",*/
          /*(slice_desc:c_ptr(int))[0],*/
          /*(slice_desc:c_ptr(int))[1],*/
          /*(slice_desc:c_ptr(int))[2],*/
          /*(slice_desc:c_ptr(int))[3]);*/

      var data: _ddata(uint(8));
      var handle = handleFromLocaleID(srcLocaleId);
      var size = __getSerializedSize(destLocaleId, srcLocaleId, srcObj,
          slice_desc, slice_desc_size);

      data = __primitive("cast", _ddata(uint(8)),
          update_prefetch_handle(this, srcLocaleId, srcObj,
            c_ptrTo(handle), size, slice_desc:c_void_ptr,
            slice_desc_size, consistent));


      __getSerializedData(destLocaleId, srcLocaleId, srcObj,
          slice_desc, slice_desc_size, data, size);

      /*writeln(here, " postreprefetch  : ",*/
          /*(slice_desc:c_ptr(int))[0],*/
          /*(slice_desc:c_ptr(int))[1],*/
          /*(slice_desc:c_ptr(int))[2],*/
          /*(slice_desc:c_ptr(int))[3]);*/

      if prefetchTiming then reprefetchTimer.stop();
    }

    //srcObj is the remote PrefetchHook
    proc doPrefetch(destLocaleId, srcLocaleId, srcObj, slice_desc,
        slice_desc_size: size_t, consistent) {

      if destLocaleId != here.id {
        halt("doPrefetch can only be called from the prefetching \
            locale");
      }

      // here we could also use actual fields in the prefetch_entry_t
      var new_handle_ptr: prefetch_entry_t;
      var data: _ddata(uint(8));

      var size = __getSerializedSize(destLocaleId, srcLocaleId, srcObj,
          slice_desc, slice_desc_size);

      //TODO rewrite for clarity
      data = __primitive("cast", _ddata(uint(8)),
          initialize_prefetch_handle(this, srcLocaleId, srcObj,
            c_ptrTo(new_handle_ptr), size, slice_desc:c_void_ptr,
            slice_desc_size, consistent));

      /*writeln(here, " after size slice details : ",*/
          /*(slice_desc:c_ptr(int))[0],*/
          /*(slice_desc:c_ptr(int))[1],*/
          /*(slice_desc:c_ptr(int))[2],*/
          /*(slice_desc:c_ptr(int))[3]);*/

      __getSerializedData(destLocaleId, srcLocaleId, srcObj,
          slice_desc, slice_desc_size, data, size);

      return new_handle_ptr;
    }

    // here obj needs to be a wide class refernece to another hook
    proc requestPrefetch(localeIdx, otherObj, consistent=true) {

      if prefetchTiming then prefetchTimer.start();

      var robjaddr = __primitive("_wide_get_addr",
          otherObj.prefetchHook);
      const nodeId = localeIDs[localeIdx];
      /*writeln(here, " prefetching from nodeID ", nodeId, " localeIdx ",*/
          /*localeIdx);*/

      if nodeId!=here.id {
        /*handles[localeIdx] = chpl_comm_request_prefetch(nodeId, robjaddr,*/
            /*c_nil, 0, consistent);*/
        handleFromLocaleIdx(localeIdx) = doPrefetch(here.id, nodeId, robjaddr,
            c_nil, 0, consistent);

        if unpackAccess {
          var dataReceived = getData(handleFromLocaleIdx(localeIdx));
          assignUnpackContainer(localeIdx,
              obj.getUnpackContainerDirect(dataReceived));

          unpackedData[localeIdx].setData(
                getElementArrayAtOffset(dataReceived,
                  obj.getDataStartByteIndex(dataReceived),
                  obj.eltType));
        }
        hasData[localeIdx] = true;
      }
      if prefetchTiming then prefetchTimer.stop();
    }

    proc requestPrefetch(localeIdx, otherObj, sliceDesc,
        consistent=true) {

      if prefetchTiming then prefetchTimer.start();

      var robjaddr = __primitive("_wide_get_addr",
          otherObj.prefetchHook);
      
      const nodeId = localeIDs[localeIdx];

      if nodeId!=here.id {
        debug_writeln(here, " prefetching ", sliceDesc);
        var (sliceDescPtr, sliceDescSize, dummyBool) =
          convertToSerialChunk(sliceDesc);
        /*handles[localeIdx] = chpl_comm_request_prefetch(nodeId, robjaddr,*/
            /*sliceDescPtr, sliceDescSize, consistent);*/
        debug_writeln(here, " prefetching ",
            (sliceDescPtr:c_ptr(obj.idxType))[0], " size ",
            sliceDescSize);
        handleFromLocaleIdx(localeIdx) = doPrefetch(here.id, nodeId, robjaddr,
            sliceDescPtr, sliceDescSize, consistent);

        if unpackAccess {
          var dataReceived = getData(handleFromLocaleIdx(localeIdx));
          assignUnpackContainer(localeIdx,
              obj.getUnpackContainerDirect(dataReceived));

          unpackedData[localeIdx].setData(
                getElementArrayAtOffset(dataReceived,
                  obj.getDataStartByteIndex(dataReceived),
                  obj.eltType));

        }
        hasData[localeIdx] = true;
      }
      if prefetchTiming then prefetchTimer.stop();
    }

    inline proc assignUnpackContainer(localeIdx, container) {
      pragma "no auto destroy"
      var localCopy: container.type;

      __primitive("=", unpackedData[localeIdx], localCopy);
    }

    proc reportPrefetchTimes() {
      if prefetchTiming {
        writeln("------------------");
        writeln(here);
        writeln("Prefetch Time : ", prefetchTimer.elapsed());
        writeln("RePrefetch Time : ", reprefetchTimer.elapsed());
        writeln("Access Time : ", accessTimer.elapsed());
        writeln("------------------");
      }
    }

    proc updatePrefetch() {
      local for i in localeDom {
        if hasData[i] {
          /*commInProgress[i] = true;*/
          /*if allowPrefetchUnpacking {*/
            /*if here.id == 0 {*/
              /*for idx in unpackedData[i].dom {*/
                /*writeln(here.id, " ", idx, " was ",*/
                    /*unpackedData[i].dsiAccess(idx));*/
              /*}*/
            /*}*/
            /*else if here.id == 1 {*/
              /*for idx in unpackedData[i].dom {*/
                /*writeln("\t", here.id, " ", idx, " was ",*/
                    /*unpackedData[i].dsiAccess(idx));*/
              /*}*/
            /*}*/
            /*else if here.id == 2 {*/
              /*for idx in unpackedData[i].dom {*/
                /*writeln("\t\t", here.id, " ", idx, " was ",*/
                    /*unpackedData[i].dsiAccess(idx));*/
              /*}*/
            /*}*/
            /*else if here.id == 3 {*/
              /*for idx in unpackedData[i].dom {*/
                /*writeln("\t\t\t", here.id, " ", idx, " was ",*/
                    /*unpackedData[i].dsiAccess(idx));*/
              /*}*/
            /*}*/
          /*}*/
          reprefetch_single_entry(handles[i]);
          /*if allowPrefetchUnpacking {*/
            /*if here.id == 0 {*/
              /*for idx in unpackedData[i].dom {*/
                /*writeln(here.id, " ", idx, " is ",*/
                    /*unpackedData[i].dsiAccess(idx));*/
              /*}*/
            /*}*/
            /*else if here.id == 1 {*/
              /*for idx in unpackedData[i].dom {*/
                /*writeln("\t", here.id, " ", idx, " is ",*/
                    /*unpackedData[i].dsiAccess(idx));*/
              /*}*/
            /*}*/
            /*else if here.id == 2 {*/
              /*for idx in unpackedData[i].dom {*/
                /*writeln("\t\t", here.id, " ", idx, " is ",*/
                    /*unpackedData[i].dsiAccess(idx));*/
              /*}*/
            /*}*/
            /*else if here.id == 3 {*/
              /*for idx in unpackedData[i].dom {*/
                /*writeln("\t\t\t", here.id, " ", idx, " is ",*/
                    /*unpackedData[i].dsiAccess(idx));*/
              /*}*/
            /*}*/
          /*}*/
          /*commInProgress[i];*/
        }
      }
    }
/*
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
      var data: obj.eltType;
      if !unpackAccess {
        var isPrefetched: int;
        var thisaddr = __primitive("_wide_get_addr", this);
        get_prefetched_data(thisaddr, handle, getSize(1,obj.eltType),
            localIdx, isPrefetched, data);

        debug_writeln("accessing packed data");
        return (isPrefetched!=0, data);
      }
      else {
        /*return (true, data);*/
        debug_writeln("accessing unpacked data");
        return (true, unpackData[localeId].dsiAccess(idx));
      }
    }
*/
    inline proc hasPrefetchedFrom(localeIdx) {
      return entry_has_data(handleFromLocaleIdx[localeIdx]);
    }

    inline proc accessPrefetchedDataRef(handle, idx) {
      local{
        var localIdx = idx;
        var backLinkOffset: int;
        var thisaddr = __primitive("_wide_get_addr", this);
        var data = get_prefetched_data_addr(thisaddr, handle,
            getSize(1, obj.eltType), localIdx, backLinkOffset);
        return (data:c_ptr(obj.eltType), backLinkOffset);
      }
    }

    proc hasPrefetchedFrom(locIdx, i) {
      if unpackAccess {
        return unpackedData[locIdx].domain.member(i);
      }
      halt("Not ready for this yet");
      return false;
    }

/*
    proc accessUnpackedData(locIdx, i) ref {
      // start_read
      /*start_read(handles(locIdx));*/
      ref data = unpackedData[locIdx][i];
      /*stop_read(handles(locIdx));*/
      return data;
      /*return unpackedData[locIdx][i];*/
      // stop_read
    }
*/
    inline proc getUnpackedData(localeIdx) {
      return unpackedData[localeIdx];
    }

    proc printTimeStats() {
      writeln("Hook access prep time : ", accessPrepTime);
      writeln("Hook access real time : ", accessRealTime);
      writeln("Hook access out time : ", accessOutTime);
    }
    proc finalizePrefetch() {
      /*for h in handles {*/
        // 2 acquires are added by the current finalization logic
        // this may not be necessary
        /*prefetch_entry_init_seqn_n(h, 0);*/
      /*}*/
    }

    inline proc getByteIndex(data: c_void_ptr, __idx: c_void_ptr) {
      var idx = __idx:c_ptr(obj.rank*obj.idxType);

      return obj.getByteIndex(data, idx.deref());
    }

    proc test() {
      writeln("Subclass", x);
    }
  }

  export proc __reprefetch_wrapper(__obj: c_void_ptr, destLocaleId:
      int(64), srcLocaleId: int(64), src_obj: c_void_ptr, slice_desc:
      c_void_ptr, slice_desc_size: size_t, consistent: bool) {

    var obj = __obj:PrefetchHook;

    obj.reprefetch(destLocaleId, srcLocaleId, src_obj, slice_desc,
        slice_desc_size, consistent);
  }

  export proc __get_byte_idx_wrapper(__obj: c_void_ptr,
      data: c_void_ptr, idx: c_void_ptr) {
    var obj = __obj:PrefetchHook;
    return obj.getByteIndex(data, idx);
  }

  /*export*/ proc __serialized_obj_size_wrapper(__obj: c_void_ptr,
      slice_desc, slice_desc_size: size_t): size_t {
    var obj = __obj:PrefetchHook;
    if slice_desc_size > 0 then {
      /*writeln(here, " gonna report size for ",*/
          /*(slice_desc:c_ptr(int))[0]);*/
      const ret = obj.dsiGetSerializedObjectSize(slice_desc);
      debug_writeln(here, " reports size ", ret);
      return ret;
    }
    else {
      const ret = obj.dsiGetSerializedObjectSize();
      debug_writeln(here, " reports size ", ret);
      return ret;
    }

  }

  /*export*/ proc __serialize_wrapper(__obj: c_void_ptr, __buf: c_void_ptr,
      bufsize: size_t, slice_desc, slice_desc_size: size_t) {

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
