module ChapelBulkTransferCache {

  pragma "no doc"
  config param debugCachedBulkTransfer = false;

  use ChapelBase;
  use CTypes;
  use Map;

  record chpl__btdCacheKey {
    //type eltType;

    var locId: int(32);
    var addr: int;

    //proc init(type eltType) {
      //this.eltType = eltType;
    //}

    proc init(locId: int(32), addr: c_ptr) {
      //this.eltType = eltType;
      this.locId = locId;
      this.addr = __primitive("cast", int, addr);
    }
  }

  record chpl__btdCacheValue {
    type eltType;

    var key: chpl__btdCacheKey;
    var srcData: _ddata(eltType);
    var dstData: _ddata(eltType);
    var srcLocId: int;
    var dstLocId: int;
    var len: uint;
    var isParallel: bool;

  }

  record chpl__btdCache {
    type eltType;

    var cache: map(chpl__btdCacheKey, chpl__btdCacheValue(eltType));

    proc get(otherArr) {
      return cache[generateKeyFromArray(otherArr._value)];
    }

    proc insert(dstArr, Adata, Bdata, Alocid, Blocid, len, doParallelAssign) {

      const key = generateKeyFromArray(dstArr);

      if debugCachedBulkTransfer then
        chpl_debug_writeln("inserting new data into cache key: ", key:string);

      this.cache.add(key, new chpl__btdCacheValue(eltType,
                                           key=key,
                                           srcData=Adata,
                                           dstData=Bdata,
                                           srcLocId=Alocid,
                                           dstLocId=Blocid,
                                           len=len,
                                           isParallel=doParallelAssign));
    }

    proc contains(k) {
      const key = generateKeyFromArray(k._value);

      if debugCachedBulkTransfer then
        chpl_debug_writeln("checking for cache key: ", key:string);

      return cache.contains(key);
    }

  }

  private proc generateKeyFromArray(b) {
    const bLocId = b.locale.id;
    const bAddr = __primitive("_wide_get_addr", b): c_ptr(b.eltType);

    return new chpl__btdCacheKey(bLocId, bAddr);
  }
}
