/*
   Overall TODO notes after cleanup

- Consider externing the entry type as a record/class to have more
  direct control over its fields. Things that can be removed with the
  help of this:

  getData()
  bunch of other functions used in support of some optimizations

- Rename initialize_opt_fields -> it seems to be initializing metadata
  for strided get API

- Unpacked data can be stored within the handle

- Think about how to create PrefetchHook objects. Currently DSI objects
  directly create the full-blown object.

- Remove unnecessary methods

- There are bunch of special casing for rank <= 3. Generalize

- Having -or not having- a prefetch slice should be handled more
  elegantly
*/

module PrefetchHooks {
  use BlockDist;
  use Time;
  // this is currently a totatlly random value
  config param initSerializeBufSize = 1024;
  config param serializeBufferGrowthFactor = 1.5;
  config param measureTime = false;
  config param debugPrefetch = false;
  config param prefetchTiming = false;

  extern type prefetch_entry_t;


      extern proc  chpl_comm_put(ref addr, node, ref raddr,
          size, typeIndex: int(32),
          commID, ln, fn:int(32));
  extern proc prefetch_strided_entry(entry);

  extern proc get_entry_data(handle): c_void_ptr; // for debugging

  // for several optimizations
  extern proc get_entry_data_start(handle): c_void_ptr;
  extern proc get_entry_remote_data_start(handle): c_void_ptr;
  extern proc set_entry_remote_data_start(handle, start);
  extern proc get_entry_data_actual_size(handle): size_t;

  extern proc get_entry_size(handle): size_t; // for fixed size opt

  // Prefetch Hook generators
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

  // Helpers
  inline proc getData(handle) {
    extern proc get_data_from_prefetch_entry(handle): c_void_ptr;
    return get_data_from_prefetch_entry(handle);
  }

  private inline proc debug_writeln(args...) {
    if debugPrefetch then
      writeln((...args));
  }

  class PrefetchHook {
    var x = 10;

    proc writeThrough(node, serialData: c_void_ptr, 
        offset, data: c_void_ptr) {
      halt("writeThrough called on PrefetchHook");
    }

    /*proc writeThrough(data, offset) {*/
      /*halt("writeThrough called on PrefetchHook");*/
    /*}*/

    proc reportPrefetchTimes() {
      halt("This shouldn't have been called 1 ", x);
    }

    proc getSerializedMetadataSize() {
      halt("This shouldn't have been called 2 ", x);
      return 0:uint;
    }

    iter dsiSerialize(metadataOnly:bool) {
      halt("This shouldn't have been called 3 ", here);
      var dummyPtr: c_void_ptr;
      var dummySize: size_t;
      yield (dummyPtr, dummySize, false);
    }

    proc dsiGetSerializedObjectSize(): size_t {
      halt("This shouldn't have been called 4 ", x);
      var val: size_t;
      return val;
    }

    iter dsiSerialize(slice_desc, metadataOnly:bool) {
      halt("This shouldn't have been called 5 ", x);
      var dummyPtr: c_void_ptr;
      var dummySize: size_t;
      yield (dummyPtr, dummySize, false);
    }

    proc dsiGetSerializedObjectSize(slice_desc): size_t {
      halt("This shouldn't have been called 6 ", x);
      var val: size_t;
      return val;
    }

    proc requestPrefetch(localeIdx, otherObj, consistent=true,
        staticDomain) {
      halt("This shouldn't have been called 7 ");
    }

    proc requestPrefetch(localeIdx, otherObj, sliceDesc, wholeDesc,
        consistent=true, staticDomain) {
      halt("This shouldn't have been called 8 ");
    }

    proc updatePrefetch() {
      halt("This shouldn't have been called 9 ");
    }

    inline proc accessPrefetchedData(localeId, idx) {
      halt("This shouldn't have been called 10 ");
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
      var dummy: int(64);
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

    var handles: c_ptr(prefetch_entry_t);
    var localeDomDimSize: localeDom.rank*int;
    var localeDomSize: int;

    var unpackedData: c_ptr(unpackType);

    //FIXME this is a dangerous field now, since we can evict data with
    //no callback to change this array
    // Update: set this to false when evictPrefetch is implemented
    var hasData: [localeDom] bool = false; // only to be use for reprefetch

    /*proc GenericPrefetchHook(obj, type unpackType, param unpackAccess) {*/
      /*handles = c_calloc(prefetch_entry_t, numLocales);*/
      /*unpackedData = c_calloc(unpackType, numLocales);*/
      /*localeD = {1..0};*/
      /*x = 20;*/
    /*}*/

    proc GenericPrefetchHook(obj, type unpackType, param unpackAccess,
        localeContainer: [?D] locale) {

      extern proc create_prefetch_handle(ref handle);

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

    proc writeThrough(node, serialData: c_void_ptr, 
        offset, data: c_void_ptr) {
      const multiDIdx = obj.getIdxFromData(serialData, offset);
      const globalDesc = obj.globalDesc;
      const localeIdx =
        globalDesc.dom.dist.targetLocaleIDs[node:int];
      /*writeln("Write through to calculated index : ", multiDIdx);*/
      globalDesc.locArr[localeIdx].accessByLocalIdx(multiDIdx) = (data:c_ptr(obj.eltType)).deref();
    }

    /*proc writeThrough(data, offset) {*/
      /*halt("data in writeThrough must be a c_void_ptr");*/
    /*}*/

    proc getSerializedMetadataSize() {
      return obj.getMetadataSize();
    }

    pragma "no local return"
    inline proc unifiedAccessPrefetchedData(locIdx, i,
        out prefetched: bool) ref {

      extern proc get_lock_offset(handle, addr): int(32);

      local {
        if prefetchTiming then accessTimer.start();

        if unpackAccess {

          debug_writeln(here, " unpacked access");

          if hasPrefetchedFrom(locIdx) {
            const flatIdx = flattenLocaleIdx(locIdx);
            ref unpackedDataTmp = unpackedData[flatIdx];

            if isSparseArr(unpackedDataTmp) then
              prefetched = unpackedDataTmp.domain._value.parentDom.member(i);
            else
              prefetched = unpackedDataTmp.domain.member(i);

            if prefetched {

              debug_writeln(here, " has prefetched ", i, " from ",
                  locIdx);

              // TODO check this logic in this if
              if isSparseArr(unpackedDataTmp) &&
                !unpackedDataTmp.domain.member(i) {
                  return unpackedDataTmp.IRV;
              }
              ref retTmp = unpackedDataTmp[i];
              const lockOffset = get_lock_offset(
                  handles[flatIdx], __primitive("_wide_get_addr", retTmp));

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

        // TODO return a pre-generated dummy for performance?
        return __primitive("gen prefetch ptr", dummyPtr, -1);
      }
    }

    iter dsiSerialize(slice_desc, metadataOnly:bool) {
      for val in obj.dsiSerializeMetadata(slice_desc:c_ptr(obj.idxType)) do
        yield val;
      if !metadataOnly then
        for val in obj.dsiSerializeData(slice_desc:c_ptr(obj.idxType)) do
          yield val;
    }

    proc dsiGetSerializedObjectSize(slice_desc): size_t {
      var size = 0: size_t;
      for v in obj.dsiGetSerializedObjectSize(slice_desc:c_ptr(obj.idxType)) {
        size += v;
      }
      return size;
    }

    iter dsiSerialize(metadataOnly:bool) {
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
      return obj.dsiGetBaseDataStartAddr(chpl__tuplify(startIdx));
    }

    //prefetch-reprefetch helpers
    pragma "no remote memory fence"
    inline proc __getSerializedSize(destLocaleId, srcLocaleId, srcObj,
        slice_desc, slice_desc_size) {
      var size = 0: size_t;
      var dataStartByteOffset = 0:uint;

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

        (size, dataStartByteOffset) =
          __serialized_obj_size_wrapper(srcObj, slice_desc_local,
              slice_desc_size);
      }
        /*if prefetchTiming then subreprefetchTimer.stop();*/

      return (size, dataStartByteOffset);
    }

    // TODO actually data start is part of metadata, this method name
    // was probably used to avoid overload confusions
    // At the very least, this and next method can be refactored into a
    // single one.
    pragma "no remote memory fence"
    proc __getSerializedMetadataAndStart(destLocaleId, srcLocaleId, srcObj,
        slice_desc, slice_desc_size: size_t, data,
        startIdx, param prefetchSlice=false) {

      var dataStartPtr: c_void_ptr;
        if prefetchTiming then subreprefetchTimer.start();
      on Locales[srcLocaleId] {
        // write data to destLocales handle's data
        var hookObj = srcObj:PrefetchHook;

        const size_local = hookObj.getSerializedMetadataSize();
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

        __serialize_wrapper(this.type, srcObj, local_buffer, size_local,
            slice_desc_local, slice_desc_size, metadataOnly=true);

        debug_writeln("Putting ", size_local, " to ", srcLocaleId);

        /*__primitive("chpl_comm_array_put", local_buffer[0], destLocaleId,*/
            /*data[0], size_local);*/

        chpl_comm_put(local_buffer[0], destLocaleId, data[0],
            size_local, -1, 0, 0, 0);
        dataStartPtr = if prefetchSlice
          then
            __get_data_start_ptr_wrapper(srcObj, startIdx)
          else
            __get_data_start_ptr_wrapper(srcObj);
      }

      if prefetchTiming then subreprefetchTimer.stop();

      if is_c_nil(dataStartPtr) then halt("Received null pointer");
      return dataStartPtr;
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

        __serialize_wrapper(this.type, srcObj, local_buffer, size_local,
            slice_desc_local, slice_desc_size, metadataOnly);

        debug_writeln("Putting ", size_local, " to ", srcLocaleId);

        /*__primitive("chpl_comm_array_put", local_buffer[0], destLocaleId,*/
            /*data[0], size_local);*/

        chpl_comm_put(local_buffer[0], destLocaleId, data[0],
            size_local, -1, 0, 0, 0);
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

    // TODO this is used only for accessing unpackedData array. If we
    // are using an extern struct for handles with explicit unpackedData
    // fields, this probably will no longer be relevant
    // Alternatively, use this in handleFromLocaleIdx methods
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
      halt("not ready for this - flattenLocaleIdx");
      return 0;
    }

    // Why not a single ref version
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

    // this is now the last resort for reprefetching (for static domains
    // this is not called?)
    pragma "no remote memory fence"
    proc reprefetch(destLocaleId, srcLocaleId, srcObj, slice_desc,
        slice_desc_size: size_t, consistent, staticDomain) {

      extern proc update_prefetch_handle(owner_obj, origin_node,
          robjaddr, new_entry, prefetch_size, slice_desc,
          slice_desc_size, consistent): c_void_ptr;

      if prefetchTiming then reprefetchTimer.start();
      if prefetchTiming then reprefetchCount += 1;

      if destLocaleId != here.id then
        halt("reprefetch can only be called from the prefetching \
            locale");

      var handle = handleFromLocaleID(srcLocaleId);

      var data: _ddata(uint(8));
      var (size, dummyOffset) = __getSerializedSize(destLocaleId,
          srcLocaleId, srcObj, slice_desc, slice_desc_size);

      data = __primitive("cast", _ddata(uint(8)),
          update_prefetch_handle(this, srcLocaleId, srcObj,
            c_ptrTo(handle), size, slice_desc:c_void_ptr,
            slice_desc_size, consistent));


      __getSerializedData(destLocaleId, srcLocaleId, srcObj,
          slice_desc, slice_desc_size, data, size);

      if prefetchTiming then reprefetchTimer.stop();
    }

    // TODO refactor this and following 3
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
        wholeDesc, out dataStartIndex, consistent, staticDomain, param
        prefetchSlice) {

      extern proc chpl_comm_get(addr, node, raddr, size,
          typeIndex: int(32), commID, ln, fn:int(32));
      extern proc initialize_prefetch_handle(owner_obj, origin_node,
          robjaddr, new_entry, prefetch_size, slice_desc, slice_desc_size,
          consistent, fixed_size, data_start_offset, elemsize): c_void_ptr;

      if destLocaleId != here.id then
        halt("doPrefetch can only be called from the prefetching \
            locale");

      var new_handle_ptr: prefetch_entry_t;
      var data: _ddata(uint(8));

      var (slice_desc, slice_desc_size, dummyBool) = (c_nil, 0:size_t,
          false);

      if prefetchSlice then
        (slice_desc, slice_desc_size, dummyBool) =
          convertToSerialChunk(domToArray(sliceDesc));

      var (size, dataStartOffset) = __getSerializedSize(destLocaleId,
          srcLocaleId, srcObj, slice_desc, slice_desc_size);
      dataStartIndex = dataStartOffset:int; // yikes

      /*writeln(here, " received serial size=",size, " from ",*/
          /*srcLocaleId);*/

      // getdatastartbyteindex is called locally
      data = __primitive("cast", _ddata(uint(8)),
          initialize_prefetch_handle(this, srcLocaleId, srcObj,
            c_ptrTo(new_handle_ptr), size, slice_desc:c_void_ptr,
            slice_desc_size, consistent, staticDomain,
            dataStartOffset:int, getSize(1, obj.eltType)));

      const (consData, stridedData) =
        generateStridedGetData(new_handle_ptr, sliceDesc, wholeDesc,
            obj.eltType, srcLocaleId); //srcLocaleId is for dbg


      // TODO branches of this decision tree should be refactored
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
          /*const metadataSize = __getSerializedMetadataSize(destLocaleId,*/
              /*srcLocaleId, srcObj, slice_desc, slice_desc_size): size_t;*/

          /*writeln(here, " received metadata size=", metadataSize);*/

          var remoteDataStartPtr =
            __getSerializedMetadataAndStart(destLocaleId, srcLocaleId,
                srcObj, slice_desc, slice_desc_size, data,
                sliceDesc.first, prefetchSlice=prefetchSlice);

          /*var remoteDataStartPtr =*/
            /*if prefetchSlice then*/
              /*__getRemoteDataStartAddr(srcLocaleId, srcObj,*/
                  /*sliceDesc.first)*/
            /*else*/
              /*__getRemoteDataStartAddr(srcLocaleId, srcObj);*/

          set_entry_remote_data_start(new_handle_ptr,
              remoteDataStartPtr);

          if consData {
            /*writeln(here, " doing consec prefetch");*/
            /*__primitive("chpl_comm_array_get",*/
              /*__primitive("array_get",*/
                  /*get_entry_data_start(new_handle_ptr):c_ptr(uint(8)),*/
                  /*0),*/
              /*srcLocaleId,*/
              /*get_entry_remote_data_start(new_handle_ptr):c_ptr(uint(8)),*/
              /*get_entry_data_actual_size(new_handle_ptr));*/

            // TODO don't we have consec prefetch function in runtime?
            chpl_comm_get(
                get_entry_data_start( new_handle_ptr),
                srcLocaleId,
                get_entry_remote_data_start(new_handle_ptr),
                get_entry_data_actual_size(new_handle_ptr),
                -1,0, 0,0);
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

    // TODO these two user-facing methods seem to defer checking if the
    // slice empty or not to `doPrefetch`. Probably refactor this pair
    // into a single method with default arguments for slice
    // here obj needs to be a wide class refernece to another hook
    proc requestPrefetch(localeIdx, otherObj, consistent=true,
        staticDomain=false) {

      if prefetchTiming then prefetchTimer.start();

      var robjaddr = __primitive("_wide_get_addr",
          otherObj.prefetchHook);
      const nodeId = localeIDs[localeIdx];

      var thisInt = __primitive("cast", uint,
          __primitive("_wide_get_addr", this));
      var other = __primitive("cast", uint, robjaddr);

      /*writeln(here,"(",thisInt,") prefetching from ", nodeId,*/
          /*"(",other,")");*/

      if nodeId!=here.id {
        const emptySliceDom = {1..0};
        var dataStartIndex = -1;
        handleFromLocaleIdx(localeIdx) = doPrefetch(here.id, nodeId,
            robjaddr, emptySliceDom, emptySliceDom, dataStartIndex,
            consistent, staticDomain, prefetchSlice=false);

        if unpackAccess {
          var dataReceived = getData(handleFromLocaleIdx(localeIdx));
          assignUnpackContainer(localeIdx,
              obj.getUnpackContainerDirect(dataReceived));

          unpackedData[flattenLocaleIdx(localeIdx)].setData(
                getElementArrayAtOffset(dataReceived,
                  dataStartIndex,
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
        var dataStartIndex = -1;
        handleFromLocaleIdx(localeIdx) = doPrefetch(here.id, nodeId,
            robjaddr, sliceDesc, wholeDesc, dataStartIndex, consistent,
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
      extern proc reprefetch_single_entry(handle);
      local forall i in localeDom {
        if hasData[i] {
          reprefetch_single_entry(handleFromLocaleIdx(i));
        }
      }
    }

    inline proc hasPrefetchedFrom(localeIdx) {
      extern proc entry_has_data(handle): bool;
      return entry_has_data(handleFromLocaleIdx[localeIdx]);
    }

    inline proc accessPrefetchedDataRef(handle, idx) {
      extern proc get_prefetched_data_addr(accessor: c_void_ptr,
          handle, size, ref idx, ref isPrefetched): c_void_ptr;
      local{
        var localIdx = idx;
        var backLinkOffset: int;
        var thisaddr = __primitive("_wide_get_addr", this);
        var data = get_prefetched_data_addr(thisaddr, handle,
            getSize(1, obj.eltType), localIdx, backLinkOffset);
        return (data:c_ptr(obj.eltType), backLinkOffset);
      }
    }

    proc printTimeStats() {
      writeln("Hook access prep time : ", accessPrepTime);
      writeln("Hook access real time : ", accessRealTime);
      writeln("Hook access out time : ", accessOutTime);
    }

    proc finalizePrefetch() {
      // TODO keeping this in the interface to avoid compilation issues
    }

    inline proc getByteIndex(data: c_void_ptr, __idx: c_void_ptr) {
      if !unpackAccess {
        var idx = __idx:c_ptr(obj.rank*obj.idxType);

        return obj.getByteIndex(data, idx.deref());
      }
      else {
        halt("getByteIndex is called on an object that doesn't " +
            "support it");

        return 0;
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

  export proc __writethrough_wrapper(__node: int(32), 
      serialData: c_void_ptr, __obj: c_void_ptr, data: c_void_ptr,
      offset: int) {

    var obj = __obj:PrefetchHook;
    /*var obj = __primitive("gen prefetch ptr", */
        /*__obj, __node) :PrefetchHook;*/

    writeln("In wrapper");
    obj.writeThrough(__node, serialData, offset, data); // pass args
  }

  /*export*/ proc __serialized_obj_size_wrapper(__obj: c_void_ptr,
      slice_desc, slice_desc_size: size_t) {
    var obj = __obj:PrefetchHook;

    var size = 0:uint;
    if slice_desc_size > 0 then {
      size = obj.dsiGetSerializedObjectSize(slice_desc);
      debug_writeln(here, " reports size ", size);
    }
    else {
      size = obj.dsiGetSerializedObjectSize();
      debug_writeln(here, " reports size ", size);
    }
    const dataStartIdx = obj.getSerializedMetadataSize();
    return (size, dataStartIdx);
  }

  proc __serialize_wrapper(type objType, __obj: c_void_ptr, __buf: c_void_ptr,
      bufsize: size_t, slice_desc, slice_desc_size: size_t,
      metadataOnly: bool) {

    local {
      type bufferEltType = uint(8);
      var obj = __obj:objType;
      /*writeln(here, " reads obj ", __primitive("cast", uint, obj));*/
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
          /*writeln(here, " chunk size ", chunkSize);*/
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
    if a.domain.numIndices > 0 {
      const startIdx = a.domain.low; // or first?
      return (c_ptrTo(a[startIdx]):c_void_ptr,
          getSize(a.size, a._value.eltType),
          false); //buffer needs to be freed?
    }
    else {
      var dummy: c_void_ptr;
      return (dummy,
          0:size_t,
          false); //buffer needs to be freed?
    }

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

    extern proc initialize_opt_fields(handle, strided_remote_data,
        consec_remote_data, stridelevel, dstStrides, srcStrides, counts);

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

    /*if !wholePrefetch {*/
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

    /*}*/

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
    if lastDiffDim != -1 {
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
    }

    debug_writeln(here, " from ", srcLocaleId, " Counts :", counts[0],
        " ", counts[1], " flags: ", incompatSlice, ", ",
        nonstrConsData);
    debug_writeln(here, " from ", srcLocaleId, " SrcStrides:",
        srcStrides[0], " flags: ", incompatSlice, ", ", nonstrConsData);
    debug_writeln(here, " from ", srcLocaleId, " DestStrides:",
        dstStrides[0], " flags: ", incompatSlice, ", ", nonstrConsData);

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
