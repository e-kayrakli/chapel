proc LocBlockArr.getIdxFromData(data: c_void_ptr, offset) {

  //-8 for the backlink offset
  const offsetInData = (offset-8) - (getMetadataSize():int);

  var metadata = getElementArrayAtOffset(data, 0, idxType);

  writeln("Offset in data : ", offsetInData);
  writeln("metadata[1] : ", metadata[0]);
  const eltSize = getSize(1, eltType):int;
  const eltCount = offsetInData/eltSize;
  if rank == 1 then
    return eltCount+metadata[0];
  if rank == 2 then
    return ((eltCount/metadata[3])+metadata[0],
            (eltCount%metadata[3])+metadata[1]);
  if rank == 3 {
    return (0,0,0);
    halt("No WT yet for 3D arrays");
  }
}

inline proc LocBlockArr.accessByLocalIdx(localIdx) ref {
  return myElems[localIdx];
}

// a prototype for now
inline proc LocBlockArr.getMetadataSize() : uint(64) {
  return rank*2*getSize(1, idxType);
}

inline proc LocBlockArr.getUnpackContainer(data:c_void_ptr) {
  var metadata = getElementArrayAtOffset(data, 0, idxType);
  var ranges: rank*range;

  for param i in 1..rank {
    ranges[i] = metadata[i-1]..#metadata[i+rank-1];
  }

  var container: [(...ranges)] eltType;
  return container._value;

}

inline proc LocBlockArr.getUnpackContainerDirect(data: c_void_ptr) {
  var metadata = getElementArrayAtOffset(data, 0, idxType);
  var ranges: rank*range;

  for param i in 1..rank do
    ranges[i] = metadata[i-1]..#metadata[i+rank-1];

  const dom = {(...ranges)};
  var ret: [dom] eltType;
  return ret;
}

inline proc LocBlockArr.getDataStartByteIndex() {
  return getSize(rank*2, idxType);
}

proc LocBlockArr.dsiGetBaseDataStartAddr() {
  return c_ptrTo(myElems[myElems.domain.low]):c_void_ptr;
}

proc LocBlockArr.dsiGetBaseDataStartAddr(startIdx: rank*idxType) {
  return c_ptrTo(myElems[startIdx]):c_void_ptr;
}

inline proc LocBlockArr.getByteIndex(data: c_void_ptr, idx:rank*idxType) {

  if rank > 3 then
    halt("I don't know how to do this yet");

  //construct metadata
  /*var low: rank*idxType;*/
  /*var size: rank*idxType;*/

  var metadata = getElementArrayAtOffset(data, 0, idxType);

  /*for param i in 1..rank {*/
    /*low[i] = metadata[i-1];*/
  /*}*/

  /*for param i in rank+1..2*rank {*/
    /*size[i-rank] = metadata[i-1];*/
  /*}*/

  /*writeln(here, " ",*/
      /*metadata[0], " ",*/
      /*metadata[1], " ",*/
      /*metadata[2], " ",*/
      /*metadata[3]);*/
  /*var low = getElementArrayAtOffset(data, 0, idxType);*/
  /*var high = getElementArrayAtOffset(data, getSize(rank,idxType), */
      /*idxType);*/

  //idx is a tuple, metadata is a c array
  const elemCount =
    if rank == 1 then
      if idx[1] >= metadata[0]+metadata[1] then
        -1
      else if idx[1] < metadata[0] then
        -1
      else
        idx[1]-metadata[0]
    else if rank == 2 then
      if idx[1] >= metadata[0]+metadata[2] ||
         idx[2] >= metadata[1]+metadata[3] then
        -1
      else if idx[1] < metadata[0] ||
              idx[2] < metadata[1] then
        -1
      else
        (idx[1]-metadata[0])*(metadata[3])+
        (idx[2]-metadata[1])
    else if rank == 3 then
      if idx[1] >= metadata[0]+metadata[2] ||
         idx[2] >= metadata[1]+metadata[3] ||
         idx[3] >= metadata[2]+metadata[4] then
        -1
      else if idx[1] < metadata[0] ||
              idx[2] < metadata[1] ||
              idx[3] < metadata[2] then
        -1
      else
        (idx[1]-metadata[0])*(metadata[4]*metadata[5])+
        (idx[2]-metadata[1])*(metadata[5])+
        (idx[3]-metadata[2])
    else
      compilerError("Not ready to prefetch where rank>3");


  // TODO TODO TODO
  /*if elemCount < 0 then return -1:size_t;*/


  // TODO this loop should work but it has one extra multiplication so I
  // am typing the code explicitly

  /*var coeff = 1;*/
  /*var sum = 0;*/
  /*for param i in 1..rank by -1{*/
    /*sum += coeff*(idx[i] - metadata[i-1]);*/
    /*coeff *= metadata[i+rank-1];*/
  /*}*/

  /*writeln(here, " > Byte index for ", idx, " ",*/
      /*getMetadataSize() + getSize(elemCount, eltType), " elemCount: ",*/
      /*elemCount);*/

  if elemCount < 0 then
    return elemCount * (getSize(1, eltType)):int;
  else
    return (getMetadataSize() + getSize(elemCount, eltType)):int;
}

iter BlockArr.dsiGetSerializedObjectSize() {
  //FIXME fix this ....thing
  for ij in dom.dist.targetLocDom {
    if dom.dist.targetLocales[ij].id == here.id {
      for val in locArr[ij].dsiGetSerializedObjectSize() {
        yield val;
      }
    }
    return;
  }
}
iter BlockArr.dsiGetSerializedObjectSize(slice_desc) {
  //FIXME fix this ....thing
  for ij in dom.dist.targetLocDom {
    if dom.dist.targetLocales[ij].id == here.id {
      for val in locArr[ij].dsiGetSerializedObjectSize(slice_desc) {
        yield val;
      }
    }
    return;
  }
}

// BlockArr slice descriptors are range tuples
iter LocBlockArr.dsiGetSerializedObjectSize() {
  yield getSize(rank*2, idxType);
  /*writeln(here, " ", myElems.domain, " ", getSize(myElems.size,*/
        /*eltType));*/
  /*yield getSize(myElems.size, eltType);*/
  const dataSize = getSize(myElems.size, eltType);
  /*if dataSize == 360 {*/
    /*writeln(here, " ", myElems.domain, " ", " ", myElems.size,  " ",*/
        /*360);*/
  /*}*/
  yield dataSize;
}
// BlockArr slice descriptors are range tuples
iter LocBlockArr.dsiGetSerializedObjectSize(slice_desc) {
  yield getSize(rank*2, idxType);

  var rangeTuple: rank*range(idxType);
  var size = 1;
  for param i in 1..rank {
    /*rangeTuple[i] = slice_desc[2*(i-1)]..slice_desc[2*(i-1)+1];*/
    rangeTuple[i] = slice_desc[(i-1)]..slice_desc[(i-1)+rank];
  }
  for param i in 1..rank {
    size *= rangeTuple[i].length;
  }
  /*writeln(here, " calculates size for slice :", rangeTuple);*/
  /*const sliceDom = {(...rangeTuple)};*/
  yield getSize(size, eltType);
}
iter LocBlockArr.dsiSerializeMetadata() {
  // two points is enough to describe a slice
  // therefore we need rank*2 idxType variables for metadata
  /*const space = 0..#(rank*2);*/
  /*var metaDataArr: [space] idxType;*/

  var low = chpl__tuplify(locDom.myBlock.low);
  var hi = chpl__tuplify(locDom.myBlock.high);
  var size = hi-low + 1;

  /*writeln(here, " serializing, ", low, " ", hi, " ", size);*/

  for param i in 1..rank {
    /*metaDataArr[i-1] = low[i];*/
    yield convertToSerialChunk(low[i]);
  }
  for param i in rank+1..2*rank {
    /*metaDataArr[i-1] = hi[i-rank] - low[i-rank] + 1;*/
    /*yield convertToSerialChunk(hi[i-rank] - low[i-rank] + 1);*/
    yield convertToSerialChunk(size[i-rank]);
  }
}

iter LocBlockArr.dsiSerializeData() {
  yield convertToSerialChunk(myElems);
}

iter LocBlockArr.dsiSerialize() {
  // two points is enough to describe a slice
  // therefore we need rank*2 idxType variables for metadata
  /*const space = 0..#(rank*2);*/
  /*var metaDataArr: [space] idxType;*/

  compilerWarning("dsiSerialize is depracated");
  var low = chpl__tuplify(locDom.myBlock.low);
  var hi = chpl__tuplify(locDom.myBlock.high);
  var size = hi-low + 1;

  /*writeln(here, " serializing, ", low, " ", hi, " ", size);*/

  for param i in 1..rank {
    /*metaDataArr[i-1] = low[i];*/
    yield convertToSerialChunk(low[i]);
  }
  for param i in rank+1..2*rank {
    /*metaDataArr[i-1] = hi[i-rank] - low[i-rank] + 1;*/
    /*yield convertToSerialChunk(hi[i-rank] - low[i-rank] + 1);*/
    yield convertToSerialChunk(size[i-rank]);
  }
  /*yield convertToSerialChunk(metaDataArr);*/
  yield convertToSerialChunk(myElems);
}

iter LocBlockArr.dsiSerializeMetadata(slice_desc) {
  const space = 0..#(rank*2);
  var metaDataArr: [space] idxType;
  const myDom = locDom.myBlock;

  /*for i in space do*/
  /*metaDataArr[i] = slice_desc[i];*/

  for param i in 1..rank {
    metaDataArr[i-1] = max(myDom.dim(i).low, slice_desc[i-1]);
    metaDataArr[i-1+rank] = min(myDom.dim(i).high,
        slice_desc[i-1+rank])-max(myDom.dim(i).low, slice_desc[i-1])+1;
  }

  /*writeln(here, " serializing metedata slice_desc ", slice_desc[0], " ",*/
                                            /*slice_desc[1], " ",*/
                                            /*slice_desc[2], " ",*/
                                            /*slice_desc[3]);*/

  /*writeln(here, " serializing metadata ", metaDataArr);*/

  for d in metaDataArr do yield convertToSerialChunk(d);
  /*yield convertToSerialChunk(metaDataArr);*/
}

iter LocBlockArr.dsiSerializeData(slice_desc) {
  var rangeTuple: rank*range(idxType);

  for param i in 1..rank {
    /*rangeTuple[i] = slice_desc[2*(i-1)]..slice_desc[2*(i-1)+1];*/
    rangeTuple[i] = slice_desc[(i-1)]..slice_desc[(i-1)+rank];
  }
  const sliceDom = {(...rangeTuple)};
  /*writeln(here, " will serialize slice : ", sliceDom);*/
  /*halt("END");*/
  /*var sliceToSend = myElems[sliceDom];*/
  /*yield convertToSerialChunk(sliceToSend);*/

  var sp = c_malloc(eltType, 1);
  for i in sliceDom do
    yield convertToSerialChunk(myElems[i], sp);
  /*yield convertToSerialChunk(c_ptrTo(myElems[sliceDom.low]),*/
      /*sliceDom.size, eltType);*/
  c_free(sp);
}

iter LocBlockArr.dsiSerialize(slice_desc) {
  compilerWarning("dsiSerialize is depracated");
  // two points is enough to describe a slice
  // therefore we need rank*2 idxType variables for metadata
  const space = 0..#(rank*2);
  var metaDataArr: [space] idxType;
  const myDom = locDom.myBlock;

  /*for i in space do*/
  /*metaDataArr[i] = slice_desc[i];*/

  for param i in 1..rank {
    metaDataArr[i-1] = max(myDom.dim(i).low, slice_desc[i-1]);
    metaDataArr[i-1+rank] = min(myDom.dim(i).high,
        slice_desc[i-1+rank])-max(myDom.dim(i).low, slice_desc[i-1])+1;
  }

  yield convertToSerialChunk(metaDataArr);
  var rangeTuple: rank*range(idxType);

  for param i in 1..rank {
    /*rangeTuple[i] = slice_desc[2*(i-1)]..slice_desc[2*(i-1)+1];*/
    rangeTuple[i] = slice_desc[(i-1)]..slice_desc[(i-1)+rank];
  }
  const sliceDom = {(...rangeTuple)};
  /*writeln(here, " will serialize slice : ", sliceDom);*/
  /*halt("END");*/
  var sliceToSend = myElems[sliceDom];
  yield convertToSerialChunk(sliceToSend);
}
