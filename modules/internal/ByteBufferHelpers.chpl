
module ByteBufferHelpers {
  use Bytes;
  pragma "no doc"
  type byteType = uint(8);
  pragma "no doc"
  type bufferType = _ddata(uint(8));
  type loc_bufferType = c_ptr(uint(8));

  // Growth factor to use when extending the buffer for appends
  config param chpl_stringGrowthFactor = 1.5;

  // Following is copy-paste from string
  //
  // Externs and constants used to implement strings
  //
  private        param chpl_string_min_alloc_size: int = 16;

  // TODO (EJR: 02/25/16): see if we can remove this explicit type declaration.
  // chpl_mem_descInt_t is really a well known compiler type since the compiler
  // emits calls for the chpl_mem_descs table. Maybe the compiler should just
  // create the type and export it to the runtime?
  pragma "no doc"
  extern type chpl_mem_descInt_t = int(16);

  pragma "fn synchronization free"
  private extern proc chpl_memhook_md_num(): chpl_mem_descInt_t;

  // Calls to chpl_here_alloc increment the memory descriptor by
  // `chpl_memhook_md_num`. For internal runtime descriptors like the ones
  // below, this would result in selecting the incorrect descriptor string.
  //
  // Instead, decrement the CHPL_RT_MD* descriptor and use the result when
  // calling chpl_here_alloc.
  private proc offset_STR_COPY_DATA {
    extern const CHPL_RT_MD_STR_COPY_DATA: chpl_mem_descInt_t;
    return CHPL_RT_MD_STR_COPY_DATA - chpl_memhook_md_num();
  }
  private proc offset_STR_COPY_REMOTE {
    extern const CHPL_RT_MD_STR_COPY_REMOTE: chpl_mem_descInt_t;
    return CHPL_RT_MD_STR_COPY_REMOTE - chpl_memhook_md_num();
  }

  private inline proc _cast(type t: loc_bufferType, v: bufferType) {
    return __primitive("_wide_get_addr", v):loc_bufferType;
  }

  inline proc chpl_string_comm_get(dest: loc_bufferType, src_loc_id: int(64),
                                   src_addr: loc_bufferType, len: integral) {
    __primitive("chpl_comm_get", dest, src_loc_id, src_addr, len.safeCast(size_t));
  }

  proc allocBuffer(requestedSize) {
    const allocSize = max(chpl_here_good_alloc_size(requestedSize),
                          chpl_string_min_alloc_size);
    var buf = chpl_here_alloc(allocSize,
                              offset_STR_COPY_DATA): bufferType;
    return (buf, allocSize);
  }

  proc allocBufferExact(requestedSize) {
    var buf = chpl_here_alloc(requestedSize,
                              offset_STR_COPY_DATA): bufferType;
    return buf;
  }

  proc reallocBuffer(buf, requestedSize) {
    const allocSize = max(chpl_here_good_alloc_size(requestedSize+1),
                          chpl_string_min_alloc_size);
    var newBuff = chpl_here_realloc(buf:loc_bufferType, allocSize,
                                offset_STR_COPY_DATA): bufferType;
    return (newBuff, allocSize);
  }

  proc copyRemoteBuffer(src_loc_id: int(64), src_addr: bufferType,
                                len: int): bufferType {
      const dest = chpl_here_alloc(len+1, offset_STR_COPY_REMOTE): bufferType;
      chpl_string_comm_get(dest:loc_bufferType, src_loc_id,
                           src_addr:loc_bufferType, len);
      dest[len] = 0;
      return dest;
  }

  proc copyLocalBuffer(src_addr: bufferType, len: int) {
      const (dst, allocSize) = allocBuffer(len+1);
      bufferMemcpyLocal(dst=dst, src=src_addr, len=len);
      return (dst, allocSize);
  }

  private inline proc _strcmp_local(buf1, len1, buf2, len2) : int {
    // Assumes a and b are on same locale and not empty.
    const size = min(len1, len2);
    const result =  c_memcmp(buf1:loc_bufferType, buf2:loc_bufferType, size);

    if (result == 0) {
      // Handle cases where one string is the beginning of the other
      if (size < len1) then return 1;
      if (size < len2) then return -1;
    }
    return result;
  }

  inline proc _strcmp(buf1, len1, loc1, buf2, len2, loc2) {
    if loc1 == chpl_nodeID && loc2 == chpl_nodeID {
      // it's local
      return _strcmp_local(buf1, len1, buf2, len2);
    } 
    else if loc1 != chpl_nodeID && loc2 == chpl_nodeID {
      var locBuf1 = copyRemoteBuffer(loc1, buf1, len1);
      return _strcmp_local(locBuf1, len1, buf2, len2);
    }
    else if loc1 == chpl_nodeID && loc2 != chpl_nodeID {
      var locBuf2 = copyRemoteBuffer(loc2, buf2, len2);
      return _strcmp_local(buf1, len1, locBuf2, len2);
    }
    else {
      var locBuf1 = copyRemoteBuffer(loc1, buf1, len1);
      var locBuf2 = copyRemoteBuffer(loc2, buf2, len2);
      return _strcmp_local(locBuf1, len1, locBuf2, len2);
    }
  }

  proc addr(buf) {
    return c_ptrTo(buf[0]);
  }

  private proc ddataToOffset(buf, off) {
    return _ddata_shift(byteType, buf, off:int); // cast is needed for byteIndex
  }

  proc copyChunk(buf, off, len, loc) {
    if !_local && loc != chpl_nodeID {
      var newBuf = copyRemoteBuffer(loc, ddataToOffset(buf, off), len);
      return (newBuf, len);
    }
    else {
      var (newBuf,size) = allocBuffer(len+1);
      c_memcpy(newBuf:loc_bufferType, buf:loc_bufferType+off, len);
      return (newBuf, size);
    }
  }

  //dst must be local
  proc bufferMemcpy(dst, src_loc, src, len, dst_off=0, src_off=0) {
    if !_local && src_loc != chpl_nodeID {
      chpl_string_comm_get(dst:loc_bufferType+dst_off, src_loc,
                           src:loc_bufferType+src_off, len);
    }
    else {
      c_memcpy(dst:loc_bufferType+dst_off, src:loc_bufferType+src_off, len);
    }

  }

  proc bufferMemcpyLocal(dst, src, len, dst_off=0, src_off=0) {
    c_memcpy(dst:loc_bufferType+dst_off, src:loc_bufferType+src_off, len);
  }

  proc bufferMemmove(dst, src, len, dst_off=0, src_off=0) {
    c_memmove(dst:loc_bufferType+dst_off, src:loc_bufferType+src_off, len);
  }

  proc freeBuffer(buf) {
    chpl_here_free(buf:loc_bufferType);
  }

  proc getByteFromBuf(buf, off, loc) {
    if !_local && loc != chpl_nodeID {
      const newBuf = copyRemoteBuffer(loc, ddataToOffset(buf,off), 1);
      return newBuf[0];
    }
    else {
      return buf[off];
    }
  }

  proc bufferEqualsLocal(buf1, off1, buf2, off2, len) {
    return _strcmp_local(buf1=addr(buf1)+off1,len1=len,
                         buf2=addr(buf2)+off2,len2=len) == 0;
  }

  proc bufferEquals(buf1, off1, loc1, buf2, off2, loc2, len) {
    return _strcmp(buf1=ddataToOffset(buf1,off1),len1=len,loc1=loc1,
                   buf2=ddataToOffset(buf2,off2),len2=len,loc2=loc1) == 0;
  }
}
