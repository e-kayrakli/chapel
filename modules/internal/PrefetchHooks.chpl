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

  extern proc prefetch_strided_entry(entry);

  extern proc initialize_opt_fields(handle, strided_remote_data,
    consec_remote_data, stridelevel, dstStrides, srcStrides, counts);
  extern proc
    entry_has_data(handle): bool;
  extern proc
    get_entry_data(handle): c_void_ptr;
  extern proc
    get_entry_data_start(handle): c_void_ptr;
  extern proc
    get_entry_remote_data_start(handle): c_void_ptr;
  extern proc
    set_entry_remote_data_start(handle, start);
  extern proc
    get_entry_size(handle): size_t;
  extern proc
    get_entry_data_actual_size(handle): size_t;
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
      consistent, fixed_size, data_start_offset, elemsize): c_void_ptr;

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

    proc getSerializedMetadataSize() {
      halt("This shouldn't have been called", x);
      return 0:uint;
    }

    iter dsiSerialize(metadataOnly) {
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

    iter dsiSerialize(slice_desc, metadataOnly) {
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

    proc requestPrefetch(localeIdx, otherObj, consistent=true,
        staticDomain) {
      halt("This shouldn't have been called");
    }

    proc requestPrefetch(localeIdx, otherObj, sliceDesc, wholeDesc,
        consistent=true, staticDomain) {
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
    
    proc getBaseDataStartAddr() {
      halt("This shouldn't have been called");
      var dummy: c_void_ptr;
      return dummy;
    }

    proc getBaseDataStartAddr(startIdx) {
      halt("This shouldn't have been called");
      var dummy: c_void_ptr;
      return dummy;
    }

    inline proc hasPrefetchedFrom(localeId) {
      halt("This shouldn't have been called");
      return false;;
    }

    proc reprefetch(destLocaleId, srcLocaleId, srcObj, slice_desc,
        slice_desc_size: size_t, consistent, staticDomain) {
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

  inline proc getNewPrefetchHook(obj, type unpackType, param
      unpackAccess, localeContainer) {
    return new GenericPrefetchHook(obj, unpackType, unpackAccess,
        localeContainer);
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

    var subreprefetchTimer = new Timer();

    var reprefetchCount = 0;

    /*var handles: c_ptr(prefetch_entry_t);*/
    /*var handles: [localeDom] prefetch_entry_t;*/
    var handles: c_ptr(prefetch_entry_t);
    var localeDomDimSize: localeDom.rank*int;
    var localeDomSize: int;

    /*var unpackedData: [localeDom] unpackType;*/
    var unpackedData: c_ptr(unpackType);
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
      unpackedData = c_calloc(unpackType, localeDomSize);
      localeDom = D;
      forall (i,l) in zip(localeIDs, localeContainer) do i = l.id;
      hasLocaleContainer = true;

      for (idx,dim) in zip(1..localeDomDimSize.size, D.dims()) {
        localeDomDimSize[idx] = dim.size;
      }

      for i in 0..#localeDomSize do create_prefetch_handle(handles[i]);
    }

    proc getSerializedMetadataSize() {
      return obj.getMetadataSize();
    }

    inline proc is_ud_nil(locIdx) {
      const flatIdx = flattenLocaleIdx(locIdx);
      return is_c_nil(__primitive("+", unpackedData, flatIdx));
    }

    pragma "no local return"
    inline proc unifiedAccessPrefetchedData(locIdx, i,
        out prefetched: bool) ref {
      local {
        if prefetchTiming then accessTimer.start();
        if unpackAccess {
          /*writeln(here, " unpacked access");*/
          if hasPrefetchedFrom(locIdx) {
            /*writeln(here, " has prefetched from ", locIdx);*/
            const flatIdx = flattenLocaleIdx(locIdx);
            ref unpackedDataTmp = unpackedData[flatIdx];
            if unpackedDataTmp.domain.member(i) {
              /*writeln(here, " has prefetched ", i, " from ", locIdx);*/
              ref retTmp = unpackedDataTmp[i];
              prefetched = true;
              const lockOffset = get_lock_offset(
                  handles[flatIdx],
                  __primitive("_wide_get_addr", retTmp));
              if prefetchTiming then accessTimer.stop();
              return __primitive("gen prefetch ptr", retTmp, lockOffset);
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

    iter dsiSerialize(slice_desc, metadataOnly) {
      for val in obj.dsiSerializeMetadata(slice_desc:c_ptr(obj.idxType)) do
        yield val;
      if !metadataOnly then
        for val in obj.dsiSerializeData(slice_desc:c_ptr(obj.idxType)) do
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

    iter dsiSerialize(metadataOnly) {
      for val in obj.dsiSerializeMetadata() do yield val;
      if !metadataOnly then
        for val in obj.dsiSerializeData() do yield val;
    }
    proc dsiGetSerializedObjectSize(): size_t {
      debug_writeln("getting size on ", here);
      var size = 0: size_t;
      for v in obj.dsiGetSerializedObjectSize() {
        size += v;
      }
      return size;
    }

    proc getBaseDataStartAddr() {
      return obj.dsiGetBaseDataStartAddr();
    }

    proc getBaseDataStartAddr(startIdx) {
      return obj.dsiGetBaseDataStartAddr(startIdx);
    }

    //prefetch-reprefetch helpers
    pragma "no remote memory fence"
    inline proc __getSerializedSize(destLocaleId, srcLocaleId, srcObj,
        slice_desc, slice_desc_size) {
      var size = 0: size_t;

        /*if prefetchTiming then subreprefetchTimer.start();*/
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
        /*if prefetchTiming then subreprefetchTimer.stop();*/

      return size;
    }

    pragma "no remote memory fence"
    proc __getSerializedData(destLocaleId, srcLocaleId, srcObj,
        slice_desc, slice_desc_size: size_t, data, size,
        metadataOnly=false) {

        if prefetchTiming then subreprefetchTimer.start();
      on Locales[srcLocaleId] {
        // write data to destLocales handle's data
        const size_local = size;
        var slice_desc_local: c_ptr(uint(8));

        if slice_desc_size > 0 {
          slice_desc_local = c_malloc(uint(8), slice_desc_size);
          __primitive("chpl_comm_array_get", slice_desc_local[0],
              destLocaleId, (slice_desc:c_ptr(uint(8)))[0],
              slice_desc_size);
        }

        //NOTE for now we are serializing the data ad hoc. previously,
        //when we relied on AM's data serialization used to start right
        //after responding to size query. This is a TODO for now
        var local_buffer = c_malloc(uint(8), size_local):c_ptr(uint(8));

        __serialize_wrapper(srcObj, local_buffer, size_local,
            slice_desc_local, slice_desc_size, metadataOnly);
        /*writeln("Putting ", size_local, " to ", srcLocaleId);*/
        __primitive("chpl_comm_array_put", local_buffer[0], destLocaleId,
            data[0], size_local);
      }
      if prefetchTiming then subreprefetchTimer.stop();
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

    inline proc flattenLocaleIdx(idx) {
      var _idx = -1;
      if isTuple(idx) {
        if idx.size == 1 {
          return idx[1];
        }
        if idx.size == 2 {
          /*var thisIntTmp = __primitive("cast", uint,*/
              /*__primitive("_wide_get_addr", this));*/
          /*writeln(here, " accesing handle of hook obj ", thisIntTmp);*/
          return idx[1]*localeDomDimSize[2]+idx[2];
        }
        if idx.size == 3 {
          return idx[1]*localeDomDimSize[2]*
            localeDomDimSize[3]+idx[2]*localeDomDimSize[3]+idx[3];
        }
      }
      else {
        return idx;
      }
      halt("not ready for this - handleFromLocaleIdx");
      return 0;
    }

    inline proc handleFromLocaleIdx(idx) {
      var _idx = -1;
      if isTuple(idx) {
        if idx.size == 1 {
          return handles[idx[1]];
        }
        if idx.size == 2 {
          /*var thisIntTmp = __primitive("cast", uint,*/
              /*__primitive("_wide_get_addr", this));*/
          /*writeln(here, " accesing handle of hook obj ", thisIntTmp);*/
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
          return handles[idx[1]];
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

    // this is now the last resort for reprefetching
    pragma "no remote memory fence"
    proc reprefetch(destLocaleId, srcLocaleId, srcObj, slice_desc,
        slice_desc_size: size_t, consistent, staticDomain) {

      if prefetchTiming then reprefetchTimer.start();
      if prefetchTiming then reprefetchCount += 1;

      if destLocaleId != here.id {
        halt("reprefetch can only be called from the prefetching \
            locale");
      }

      var handle = handleFromLocaleID(srcLocaleId);

      var data: _ddata(uint(8));
      var size = __getSerializedSize(destLocaleId, srcLocaleId, srcObj,
          slice_desc, slice_desc_size);

      /*if fixedSize then*/
      /*var size = get_entry_size(handle);*/

      data = __primitive("cast", _ddata(uint(8)),
          update_prefetch_handle(this, srcLocaleId, srcObj,
            c_ptrTo(handle), size, slice_desc:c_void_ptr,
            slice_desc_size, consistent));


      /*if prefetchTiming then subreprefetchTimer.start();*/
      __getSerializedData(destLocaleId, srcLocaleId, srcObj,
          slice_desc, slice_desc_size, data, size);
      /*if prefetchTiming then subreprefetchTimer.stop();*/
      /*writeln("Copied");*/
      /*for i in 0..3 do {*/
      /*write((get_entry_data(handle):c_ptr(int(64)))[i], " ");*/
      /*}*/
      /*writeln();*/

      if prefetchTiming then reprefetchTimer.stop();
    }

    proc __getRemoteDataStartAddr(srcLocaleId, srcObj) {

      var dataStartPtr: c_void_ptr;
      on Locales[srcLocaleId] {
        dataStartPtr = __get_data_start_ptr_wrapper(srcObj);
      }
      if is_c_nil(dataStartPtr) then halt("Received null pointer");
      return dataStartPtr;
    }

    proc __getRemoteDataStartAddr(srcLocaleId, srcObj, startIdx) {

      var dataStartPtr: c_void_ptr;
      on Locales[srcLocaleId] {
        dataStartPtr = __get_data_start_ptr_wrapper(srcObj, startIdx);
      }
      if is_c_nil(dataStartPtr) then halt("Received null pointer");
      return dataStartPtr;
    }

    proc __get_data_start_ptr_wrapper(__obj: c_void_ptr) {
      var obj = __obj:PrefetchHook;

      return obj.getBaseDataStartAddr();
    }

    proc __get_data_start_ptr_wrapper(__obj: c_void_ptr, startIdx) {
      var obj = __obj:PrefetchHook;

      return obj.getBaseDataStartAddr(startIdx);
    }

    //srcObj is the remote PrefetchHook
    proc doPrefetch(destLocaleId, srcLocaleId, srcObj, sliceDesc,
        wholeDesc, consistent, staticDomain, param prefetchSlice) {

      if destLocaleId != here.id {
        halt("doPrefetch can only be called from the prefetching \
            locale");
      }

      var new_handle_ptr: prefetch_entry_t;
      var data: _ddata(uint(8));

      var sliceDescArr = domToArray(sliceDesc);
      var (slice_desc, slice_desc_size, dummyBool) =
        if prefetchSlice then
          convertToSerialChunk(sliceDescArr)
        else
          (c_nil, 0:size_t, false);

      var size = __getSerializedSize(destLocaleId, srcLocaleId, srcObj,
          slice_desc, slice_desc_size);

      data = __primitive("cast", _ddata(uint(8)),
          initialize_prefetch_handle(this, srcLocaleId, srcObj,
            c_ptrTo(new_handle_ptr), size, slice_desc:c_void_ptr,
            slice_desc_size, consistent, staticDomain,
            obj.getDataStartByteIndex(), getSize(1, obj.eltType)));

      const (consData, stridedData) =
        generateStridedGetData(new_handle_ptr, sliceDesc, wholeDesc,
            obj.eltType, srcLocaleId); //srcLocaleId is for dbg


      // if data is being prefetched consistently, don't bring in the
      // data right away
      if !consistent {
        if staticDomain && (consData || stridedData) {
        /*if staticDomain && (consData || false) {*/
          // even though we are not prefetching the full data, we still
          // need to bring in the metadata b/c:
          // when we  don't bring in the metadata, first access to the
          // data is done through junk metadata(all zeroes). Remember that
          // we are checking for stale data while doing the actual read
          // from the buffer and not when calculating the byte index,
          // which happens without any lockign(we assume that metadata
          // never changes and it is always there
          const metadataSize = __getSerializedMetadataSize(destLocaleId,
              srcLocaleId, srcObj, slice_desc, slice_desc_size): size_t;

          __getSerializedData(destLocaleId, srcLocaleId, srcObj,
              slice_desc, slice_desc_size, data, metadataSize,
              metadataOnly=true);

          var remoteDataStartPtr =
            if prefetchSlice then
              __getRemoteDataStartAddr(srcLocaleId, srcObj,
                  sliceDesc.first)
            else
              __getRemoteDataStartAddr(srcLocaleId, srcObj);

          set_entry_remote_data_start(new_handle_ptr,
              remoteDataStartPtr);

          if consData {
            /*writeln(here, " doing consec prefetch");*/
            __primitive("chpl_comm_array_get",
              __primitive("array_get",
                  get_entry_data_start(new_handle_ptr):c_ptr(uint(8)),
                  0),
              srcLocaleId,
              get_entry_remote_data_start(new_handle_ptr):c_ptr(uint(8)),
              get_entry_data_actual_size(new_handle_ptr));
          }
          else { //strided data
            /*writeln(here, " doing strided prefetch");*/
            prefetch_strided_entry(new_handle_ptr);
          }
        }
        else {
          /*writeln(here, " doing full prefetch");*/
          __getSerializedData(destLocaleId, srcLocaleId, srcObj,
              slice_desc, slice_desc_size, data, size);
        }
      }
      else {
        // even though we are not prefetching the full data, we still
        // need to bring in the metadata b/c:
        // when we  don't bring in the metadata, first access to the
        // data is done through junk metadata(all zeroes). Remember that
        // we are checking for stale data while doing the actual read
        // from the buffer and not when calculating the byte index,
        // which happens without any lockign(we assume that metadata
        // never changes and it is always there
        const metadataSize = __getSerializedMetadataSize(destLocaleId,
            srcLocaleId, srcObj, slice_desc, slice_desc_size): size_t;

        __getSerializedData(destLocaleId, srcLocaleId, srcObj,
            slice_desc, slice_desc_size, data, metadataSize,
            metadataOnly=true);

        // data is being prefetched consistently,
        // if staticDomain, and is not slice we need to get the start
        // address of the data in the owner node
        if staticDomain && (consData || stridedData) {

          var remoteDataStartPtr =
            if prefetchSlice then
              __getRemoteDataStartAddr(srcLocaleId, srcObj,
                  sliceDesc.first)
            else
              __getRemoteDataStartAddr(srcLocaleId, srcObj);

          set_entry_remote_data_start(new_handle_ptr,
              remoteDataStartPtr);
        }
        else {
          /*writeln(here, " prefetch from ", srcLocaleId, " cant be opt");*/
          // we cannot do any optimization for reprefetching
          // runtime will call `reprefetch`
        }
      }

      return new_handle_ptr;
    }

    inline proc __getSerializedMetadataSize(destLocaleId, srcLocaleId,
        srcObj, slice_desc, slice_desc_size) {

      var size = 0:uint;
      on Locales[srcLocaleId] {
        var hookObj = srcObj:PrefetchHook;

        size = hookObj.getSerializedMetadataSize();
      }

      return size;
    }

    // here obj needs to be a wide class refernece to another hook
    proc requestPrefetch(localeIdx, otherObj, consistent=true,
        staticDomain=false) {

      if prefetchTiming then prefetchTimer.start();

      var robjaddr = __primitive("_wide_get_addr",
          otherObj.prefetchHook);
      const nodeId = localeIDs[localeIdx];

      if nodeId!=here.id {
        const emptySliceDom = {1..0};
        handleFromLocaleIdx(localeIdx) = doPrefetch(here.id, nodeId,
            robjaddr, emptySliceDom, emptySliceDom, consistent,
            staticDomain, prefetchSlice=false);

        if unpackAccess {
          var dataReceived = getData(handleFromLocaleIdx(localeIdx));
          assignUnpackContainer(localeIdx,
              obj.getUnpackContainerDirect(dataReceived));

          unpackedData[flattenLocaleIdx(localeIdx)].setData(
                getElementArrayAtOffset(dataReceived,
                  obj.getDataStartByteIndex(),
                  obj.eltType));
        }
        hasData[localeIdx] = true;
      }
      if prefetchTiming then prefetchTimer.stop();
    }

    proc requestPrefetch(localeIdx, otherObj, sliceDesc, wholeDesc,
        consistent=true, staticDomain=false) {

      if prefetchTiming then prefetchTimer.start();

      var robjaddr = __primitive("_wide_get_addr",
          otherObj.prefetchHook);
      
      const nodeId = localeIDs[localeIdx];

      if nodeId!=here.id {
        debug_writeln(here, " prefetching ", sliceDesc);
        handleFromLocaleIdx(localeIdx) = doPrefetch(here.id, nodeId,
            robjaddr, sliceDesc, wholeDesc, consistent,
            staticDomain, prefetchSlice=true);

        if unpackAccess {
          var dataReceived = getData(handleFromLocaleIdx(localeIdx));
          assignUnpackContainer(localeIdx,
              obj.getUnpackContainerDirect(dataReceived));

          unpackedData[flattenLocaleIdx(localeIdx)].setData(
                getElementArrayAtOffset(dataReceived,
                  obj.getDataStartByteIndex(),
                  obj.eltType));

        }
        hasData[localeIdx] = true;
      }
      if prefetchTiming then prefetchTimer.stop();
    }

    inline proc assignUnpackContainer(localeIdx, container) {
      pragma "no auto destroy"
      var localCopy: container.type;

      __primitive("=", unpackedData[flattenLocaleIdx(localeIdx)], localCopy);
    }

    proc reportPrefetchTimes() {
      if prefetchTiming {
        writeln("------------------");
        writeln(here);
        writeln("Prefetch Time : ", prefetchTimer.elapsed());
        writeln("RePrefetch Time : ", reprefetchTimer.elapsed(), " (",
            reprefetchCount, ")");
        writeln("SubrePrefetch Time : ", subreprefetchTimer.elapsed());
        writeln("Access Time : ", accessTimer.elapsed());
        writeln("------------------");
      }
    }

    proc updatePrefetch() {
      local forall i in localeDom {
        if hasData[i] {
          reprefetch_single_entry(handleFromLocaleIdx(i));
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
        return unpackedData[flattenLocaleIdx(locIdx)].domain.member(i);
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
      return unpackedData[flattenLocaleIdx(localeIdx)];
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
      if !unpackAccess {
        var idx = __idx:c_ptr(obj.rank*obj.idxType);

        return obj.getByteIndex(data, idx.deref());
      }
      else {
        halt("getByteIndex is called on an object that doesn't " +
            "support it");

        return 0:uint;
      }
    }

    proc test() {
      writeln("Subclass", x);
    }
  }

  export proc __reprefetch_wrapper(__obj: c_void_ptr, destLocaleId:
      int(64), srcLocaleId: int(64), src_obj: c_void_ptr, slice_desc:
      c_void_ptr, slice_desc_size: size_t, consistent: bool, staticDomain:
      bool) {

    var obj = __obj:PrefetchHook;

    obj.reprefetch(destLocaleId, srcLocaleId, src_obj, slice_desc,
        slice_desc_size, consistent, staticDomain);
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

  proc __serialize_wrapper(__obj: c_void_ptr, __buf: c_void_ptr,
      bufsize: size_t, slice_desc, slice_desc_size: size_t,
      metadataOnly: bool) {

    local {
      type bufferEltType = uint(8);
      var obj = __obj:PrefetchHook;
      var buf = __buf:c_ptr(bufferEltType);

      var curBufferSize = 0:uint;

      // chunk will be a heterogeneous tuple of
      //
      // (ref to first index:void, numBytes)
      //
      // currently I am providing a helper convertToSerialChunk that
      // takes a rectangular array and returns the tuple we need. if the
      // format is changed, only implementation of that function should
      // change
      if slice_desc_size > 0 {
        for chunk in obj.dsiSerialize(slice_desc, metadataOnly) {
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
        for chunk in obj.dsiSerialize(metadataOnly) {
          const chunkSize = chunk[2];
          //memcpy to buffer
          c_memcpy(c_ptrTo(buf[curBufferSize]), //there was a cast here
              chunk[1]:c_ptr(bufferEltType), chunkSize);

          curBufferSize += chunkSize;
        }
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

  inline proc convertToSerialChunk(a: c_ptr, count, type t) {
    return (a:c_void_ptr,
        getSize(count, t),
        false); //buffer needs to be freed?

  }

  inline proc convertToSerialChunk(a: integral) {
    var dyn_mem = c_malloc(a.type, 1);
    dyn_mem[0] = a;
    return (dyn_mem:c_void_ptr,
        getSize(1, a.type),
        true); //buffer needs to be freed?

  }

  inline proc convertToSerialChunk(a, scratchPad)
      where scratchPad.type == c_ptr(a.type) {
    scratchPad[0] = a;
    return (scratchPad:c_void_ptr,
        getSize(1, a.type),
        false); //buffer needs to be freed?

  }
  
  inline proc convertToSerialChunk(a) where isTuple(a) {
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

  proc generateStridedGetData(handle, slice, whole, type eltType,
      srcLocaleId) {

    /*writeln("Generate called with slice: ", slice, " whole ", whole);*/

    if whole.rank != slice.rank then
      compilerError("Slice with different rank than whole is not " +
          "allowed");

    param rank = slice.rank;
    const wholePrefetch = (slice==whole);

    // TODO we can probably stop here if wholePrefetch

    var differentDims = 0;
    var lastDiffDim = -1;

    var incompatSlice = false;
    var nonstrConsData = wholePrefetch;

    if !wholePrefetch {
      for param r in 1..rank {
        if slice.dim(r) != whole.dim(r) {
          lastDiffDim = r;
          differentDims += 1;
        }
      }

      // TODO probably disable optimization silently
      if differentDims > 1 {
        incompatSlice = true;
        /*writeln("Different dimensions = 2");*/
      }

    }

    if lastDiffDim == 1 then {
      // this is not a whole nor strided prefetch, but remote data is
      // consecutive
      nonstrConsData = true;
      /*writeln("Do something for consecutive access");*/
    }

    // we can still support this case even if incompatSlice
    if slice.numIndices == 1 {
      nonstrConsData = true;
    }

    var strideLevels: int;
    var counts: c_ptr(size_t);
    var srcStrides: c_ptr(size_t);
    var dstStrides: c_ptr(size_t);

    // TODO work out the bug preventing this if -- not urgent
    /*if !nonstrConsData {*/
      // strideLevels to be copied to entry
      strideLevels = differentDims;

      // to be copied to the entry
      counts = c_calloc(size_t, differentDims+1);

      // count[0] is a special case
      counts[0] = 1;
      for r in lastDiffDim..rank {
        counts[0] *= slice.dim(r).length.safeCast(size_t);
      }

      dstStrides = c_calloc(size_t, differentDims);
      // we are assuming strideLevels == 1
      dstStrides[0] = counts[0];

      // we are assuming stridelevels == 1
      counts[1] = 1;
      for r in 1..lastDiffDim-1 {
        counts[1] *= slice.dim(r).length.safeCast(size_t);
      }

      srcStrides = c_calloc(size_t, differentDims);
      srcStrides[0] = 1;
      for r in lastDiffDim..rank {
        srcStrides[0] *= whole.dim(r).length.safeCast(size_t);
      }
    /*}*/

    // TODO thise writelns can be debug writelns
    /*writeln(here, " from ", srcLocaleId, " Counts :", counts[0], " ",*/
        /*counts[1], " flags: ", incompatSlice, ", ", nonstrConsData);*/
    /*writeln(here, " from ", srcLocaleId, " SrcStrides:", srcStrides[0],*/
        /*" flags: ", incompatSlice, ", ", nonstrConsData);*/
    /*writeln(here, " from ", srcLocaleId, " DestStrides:",*/
        /*dstStrides[0], " flags: ", incompatSlice, ", ",*/
        /*nonstrConsData);*/

    initialize_opt_fields(handle,
        !incompatSlice, nonstrConsData, // flags
        strideLevels, dstStrides, srcStrides, counts);

    return (nonstrConsData, !incompatSlice);
  }
  inline proc domToArray(dom: domain) where dom.rank == 1 {
    return [dom.dim(1).low, dom.dim(1).high];
  }
  inline proc domToArray(dom: domain) where dom.rank == 2 {
    return [dom.dim(1).low, dom.dim(2).low,
           dom.dim(1).high, dom.dim(2).high];
  }
  inline proc domToArray(dom: domain) where dom.rank == 3 {
    return [dom.dim(1).low, dom.dim(2).low, dom.dim(3).low,
           dom.dim(1).high, dom.dim(2).high, dom.dim(3).high];
  }
}
