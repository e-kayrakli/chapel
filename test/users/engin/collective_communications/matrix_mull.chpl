use Time;
use BlockDist;
use CommDiagnostics;

config param detailedTiming=false;
config const N = 4;
config const optComm = true;
const space = {0..#N, 0..#N};
const dom = space dmapped Block(space);

var a: [dom] real;
var b: [dom] real;

forall (i,j) in dom {
  a[i,j] = sin(i*N+j);
  b[i,j] = cos(i+j);
}

/*writeln(a);*/
/*writeln(b);*/


var c: [dom] real;

startCommDiagnostics();
const t = new Timer();
const detailT = new Timer();
var commTime = 0.0;
var compTime = 0.0;

t.start();
if optComm {
  if detailedTiming then detailT.start();
  a._value.rowWiseAllGather();
  b._value.colWiseAllGather();
  if detailedTiming {
    detailT.stop();
    commTime += detailT.elapsed();
    detailT.clear();
  }
}

if detailedTiming then detailT.start();
forall (i,j) in dom {
  for k in dom.dim(1) {
    c[i,j] += a[i,k] * b[k,j];
  }
}
if detailedTiming {
  detailT.stop();
  compTime += detailT.elapsed();
  detailT.clear();
}
t.stop();
stopCommDiagnostics();

/*writeln(c);*/

writeln("Checksum : ", + reduce c);
writeln("N : ", N);
writeln("Time : ", t.elapsed());
if detailedTiming {
  writeln("\t CommTime : ", commTime);
  writeln("\t CompTime : ", compTime);
}

writeln(getCommDiagnostics());

// local copies are broadcast across columns
proc BlockArr.rowWiseAllGather() {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      for i in dom.dist.targetLocDom.dim(2) {
        const sourceIdx = chpl__tuplify(i).withIdx(1, localeIdx[1]);
        const locDom = dom.getLocDom(sourceIdx);
        /*writeln("Copying ", locDom.myBlock, " from ", */
            /*dom.dist.targetLocales(sourceIdx), " to ",*/
            /*dom.dist.targetLocales(localeIdx), " on ", here);*/
        const privCopy = chpl_getPrivatizedCopy(this.type, this.pid);
        privCopy.locArrsScratchPad[sourceIdx] =
          new LocBlockArr(eltType, rank, idxType, stridable, locDom);
        chpl__bulkTransferArray(
            privCopy.locArrsScratchPad[sourceIdx].myElems,
            locArr[sourceIdx].myElems);
        privCopy.locArrsScratchPadReady[sourceIdx] = true;
      }
    }
  }
  /*writeln("Gather finished");*/
  /*writeln(locArrsScratchPadFlags);*/
}

/*proc BlockArr.rowWiseAllPrefetch(onlyCol) {*/
  /*coforall localeIdx in dom.dist.targetLocDom {*/
    /*on dom.dist.targetLocales(localeIdx) {*/
      /*[>for i in dom.dist.targetLocDom.dim(2) {<]*/
        /*const targetIdx = */
          /*chpl__tuplify(onlyCol).withIdx(1, localeIdx[1]);*/
        /*const locDom = dom.getLocDom(targetIdx);*/
        /*[>writeln("Copying ", locDom.myBlock, " from ", <]*/
            /*[>dom.dist.targetLocales(sourceIdx), " to ",<]*/
            /*[>dom.dist.targetLocales(localeIdx), " on ", here);<]*/
        /*const privCopy = chpl_getPrivatizedCopy(this.type, this.pid);*/
        /*privCopy.locArrsScratchPad[sourceIdx] =*/
          /*new LocBlockArr(eltType, rank, idxType, stridable, locDom);*/
        /*chpl__bulkTransferArray(*/
            /*privCopy.locArrsScratchPad[sourceIdx].myElems,*/
            /*locArr[sourceIdx].myElems);*/
      /*[>}<]*/
    /*}*/
  /*}*/
  /*[>writeln("Gather finished");<]*/
  /*[>writeln(locArrsScratchPadFlags);<]*/
/*}*/

// local copies are broadcast across columns
proc BlockArr.colWiseAllGather() {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      for i in dom.dist.targetLocDom.dim(1) {
        const sourceIdx = chpl__tuplify(i).withIdx(2, localeIdx[2]);
        const locDom = dom.getLocDom(sourceIdx);
        /*writeln("Copying ", locDom.myBlock, " from ", */
            /*dom.dist.targetLocales(sourceIdx), " to ",*/
            /*dom.dist.targetLocales(localeIdx), " on ", here);*/
        const privCopy = chpl_getPrivatizedCopy(this.type, this.pid);
        privCopy.locArrsScratchPad[sourceIdx] =
          new LocBlockArr(eltType, rank, idxType, stridable, locDom);
        chpl__bulkTransferArray(
            privCopy.locArrsScratchPad[sourceIdx].myElems,
            locArr[sourceIdx].myElems);
        privCopy.locArrsScratchPadReady[sourceIdx] = true;
      }
    }
  }
  /*writeln("Gather finished");*/
  /*writeln(locArrsScratchPadFlags);*/
}

/*proc BlockArr.colWiseAllPrefetch(onlyRow) {*/
  /*coforall localeIdx in dom.dist.targetLocDom {*/
    /*on dom.dist.targetLocales(localeIdx) {*/
      /*[>for i in dom.dist.targetLocDom.dim(1) {<]*/
        /*const sourceIdx =*/
          /*chpl__tuplify(onlyRow).withIdx(2, localeIdx[2]);*/
        /*const locDom = dom.getLocDom(sourceIdx);*/
        /*[>writeln("Copying ", locDom.myBlock, " from ", <]*/
            /*[>dom.dist.targetLocales(sourceIdx), " to ",<]*/
            /*[>dom.dist.targetLocales(localeIdx), " on ", here);<]*/
        /*const privCopy = chpl_getPrivatizedCopy(this.type, this.pid);*/
        /*privCopy.locArrsScratchPad[sourceIdx] =*/
          /*new LocBlockArr(eltType, rank, idxType, stridable, locDom);*/
        /*chpl__bulkTransferArray(*/
            /*privCopy.locArrsScratchPad[sourceIdx].myElems,*/
            /*locArr[sourceIdx].myElems);*/
      /*[>}<]*/
    /*}*/
  /*}*/
  /*[>writeln("Gather finished");<]*/
  /*[>writeln(locArrsScratchPadFlags);<]*/
/*}*/
proc BlockArr.allGather() {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {

      for sourceIdx in dom.dist.targetLocDom {
        const locDom = dom.getLocDom(sourceIdx);
        /*writeln("Copying ", locDom.myBlock, " from ", sourceIdx, " to ",*/
            /*localeIdx, " on ", here);*/
        const privCopy = chpl_getPrivatizedCopy(this.type, this.pid);
        privCopy.locArrsScratchPad[sourceIdx] =
          new LocBlockArr(eltType, rank, idxType, stridable, locDom);
        /*this.locArrsScratchPadFlags[localeIdx*numLocales+sourceIdx] = true;*/
        chpl__bulkTransferArray(
            privCopy.locArrsScratchPad[sourceIdx].myElems,
            locArr[sourceIdx].myElems);
      }
    }
  }
  /*writeln("Gather finished");*/
  /*writeln(locArrsScratchPadFlags);*/
}
proc lineSliceMask(dom, param dim, idx) {

  if !isTuple(idx) || !isHomogeneousTuple(idx) then
    compilerError("Index to get line slice must be a homogeneous tuple");

  if idx[1].type != dom.idxType then 
    compilerError("Index to get line slice is not of the domain's index type");

  param numIdxPre = dim - 1;
  param numIdxPost = dom.rank - dim;

  compilerAssert(numIdxPre + numIdxPost == dom.rank-1);

  var idxPre = createTuple(if numIdxPre>0 then numIdxPre else 1, 
      dom.idxType, 0:dom.idxType);
  for param i in 1..numIdxPre do
    idxPre[i] = idx[i];

  var idxPost = createTuple(if numIdxPost > 0 then numIdxPost else 1, 
      dom.idxType, 0:dom.idxType);
  for param i in 1..numIdxPost do
    idxPost[i] = idx[numIdxPre+1+i];

  if numIdxPre > 0 && numIdxPost > 0 {
    return ((...idxPre),..,(...idxPost));
  }
  if numIdxPre > 0 && numIdxPost <= 0 {
    return ((...idxPre),..);
  }
  if numIdxPre <= 0 && numIdxPost > 0 {
    return (..,(...idxPost));
  }
  if numIdxPre <= 0 && numIdxPost <= 0 {
    return (.., );
  }

}

proc _tuple.withIdx(idx, mergeVal) where isHomogeneousTuple(this) {

  // FIXME this if doesn't work as expected
  if mergeVal.type != this[1].type then
    compilerError("Value to be merged is not of the type of tuple components");

  const defVal: mergeVal.type;
  var ret = createTuple(this.size+1, mergeVal.type, defVal);

  var partialIndexOffset = 0;
  for i in 1..ret.size {
    if i == idx {
      ret[i] = mergeVal;
      partialIndexOffset = 1;
    }
    else {
      ret[i] = this[i-partialIndexOffset];
    }
  }

  return ret;
}

proc _tuple.withoutIdx(idx) where isHomogeneousTuple(this) {

  const defVal: this[1].type;
  var ret = createTuple(this.size-1, this[1].type, defVal);

  for i in 1..idx-1 do
    ret[i] = this[i];

  for i in idx+1..this.size do
    ret[i-1] = this[i];

  return ret;
}
