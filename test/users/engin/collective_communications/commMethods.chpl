use BlockDist;
use BlockCycDist;

inline proc BlockArr.updatePrefetch() {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      locArr[localeIdx].getPrefetchHook().updatePrefetch();
    }
  }
}

inline proc BlockArr.__prefetchFrom(localeIdx, sourceIdx, consistent) {
  var privCopy = chpl_getPrivatizedCopy(this.type, this.pid);
  locArr[localeIdx].prefetchHook.requestPrefetch(
      sourceIdx,
      privCopy.locArr[sourceIdx],
      consistent);
}

inline proc SparseBlockArr.__prefetchFrom(localeIdx, sourceIdx,
    consistent) {
  var privCopy = chpl_getPrivatizedCopy(this.type, this.pid);
  locArr[localeIdx].prefetchHook.requestPrefetch(
      dom.dist.targetLocales[sourceIdx].id, //TODO this can be avoided
      privCopy.locArr[sourceIdx],
      consistent);
}

inline proc BlockArr.__prefetchFrom(localeIdx, sourceIdx, sliceDesc,
    consistent) {
  var privCopy = chpl_getPrivatizedCopy(this.type, this.pid);
  const sliceDescArr = domToArray(sliceDesc);
  locArr[localeIdx].prefetchHook.requestPrefetch(
      sourceIdx,
      privCopy.locArr[sourceIdx], sliceDescArr,
      consistent);
}

proc BlockCyclicArr.__prefetchFrom(localeIdx, sourceIdx,
    consistent) {

  var privCopy = chpl_getPrivatizedCopy(this.type, this.pid);
  locArr[localeIdx].prefetchHook.requestPrefetch(
      dom.dist.targetLocales[sourceIdx].id, //TODO this can be avoided
      privCopy.locArr[sourceIdx],
      consistent);
}

proc BlockCyclicArr.transposePrefetch(consistent=true) {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      const sourceIdx = (localeIdx[2], localeIdx[1]);
      __prefetchFrom(localeIdx, sourceIdx, consistent);
    }
  }
  /*writeln("Finalizing prefetch");*/
  finalizePrefetch();
}

proc BlockArr.allGather(consistent=true) {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      for sourceIdx in dom.dist.targetLocDom {
        __prefetchFrom(localeIdx, sourceIdx, consistent);
      }
    }
  }
  finalizePrefetch();
}

proc SparseBlockArr.allGather(consistent=true) {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      for sourceIdx in dom.dist.targetLocDom {
        __prefetchFrom(localeIdx, sourceIdx, consistent);
      }
    }
  }
  finalizePrefetch();
}

proc BlockArr.luleshStencilPrefetch3d(consistent=true) {

  if rank != 3 then
    halt("This Prefetch pattern is only supprted for 3D arrays");

  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      const myDom = dom.locDoms[localeIdx].myBlock;
      const tlDom = dom.dist.targetLocDom;

      const hasFront = localeIdx[1] > 0;
      /*const hasBack = localeIdx[1] < tlDom.dim(1).size-1;*/

      const hasTop = localeIdx[2] > 0;
      /*const hasBottom = localeIdx[2] < tlDom.dim(2).size-1;*/

      const hasLeft = localeIdx[3] > 0;
      /*const hasRight = localeIdx[3] < tlDom.dim(3).size-1;*/

      if hasFront {
        const sourceIdx = localeIdx + (-1,0,0);
        const sliceDesc = {myDom.dim(1).low-1..myDom.dim(1).low-1,
          myDom.dim(2), myDom.dim(3)};

        /*[>writeln(here, " will get " , sliceDesc, " from ",<]*/
            /*[>dom.dist.targetLocales(sourceIdx));<]*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }
      /*if hasBack {*/
        /*const sourceIdx = localeIdx + (1,0,0);*/
        /*const sliceDesc = {myDom.dim(1).high+1..myDom.dim(1).high+1,*/
          /*myDom.dim(2), myDom.dim(3)};*/

        /*[>writeln(here, " will get " , sliceDesc, " from ",<]*/
            /*[>dom.dist.targetLocales(sourceIdx));<]*/
        /*__prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);*/
      /*}*/

      if hasTop {
        const sourceIdx = localeIdx + (0,-1,0);
        const sliceDesc = {myDom.dim(1),
          myDom.dim(2).low-1..myDom.dim(2).low-1, myDom.dim(3)};

        /*[>writeln(here, " will get " , sliceDesc, " from ",<]*/
            /*[>dom.dist.targetLocales(sourceIdx));<]*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }
      /*if hasBottom {*/
        /*const sourceIdx = localeIdx + (0,1,0);*/
        /*const sliceDesc = {myDom.dim(1),*/
          /*myDom.dim(2).high+1..myDom.dim(2).high+1, myDom.dim(3)};*/

        /*[>writeln(here, " will get " , sliceDesc, " from ",<]*/
            /*[>dom.dist.targetLocales(sourceIdx));<]*/
        /*__prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);*/
      /*}*/

      if hasLeft {
        const sourceIdx = localeIdx + (0,0,-1);
        const sliceDesc = {myDom.dim(1),
          myDom.dim(2), myDom.dim(3).low-1..myDom.dim(3).low-1};

        /*[>writeln(here, " will get " , sliceDesc, " from ",<]*/
            /*[>dom.dist.targetLocales(sourceIdx));<]*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }
      /*if hasRight {*/
        /*const sourceIdx = localeIdx + (0,0,1);*/
        /*const sliceDesc = {myDom.dim(1),*/
          /*myDom.dim(2), myDom.dim(3).high+1..myDom.dim(3).high+1};*/

        /*[>writeln(here, " will get " , sliceDesc, " from ",<]*/
            /*[>dom.dist.targetLocales(sourceIdx));<]*/
        /*__prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);*/
      /*}*/

      if hasFront && hasLeft {
        const sourceIdx = localeIdx + (-1,0,-1);
        const sliceDesc = {myDom.dim(1).low-1..myDom.dim(1).low-1,
          myDom.dim(2), myDom.dim(3).low-1..myDom.dim(3).low-1};

        /*writeln(here, " will get " , sliceDesc, " from ",*/
            /*dom.dist.targetLocales(sourceIdx));*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }
      /*if hasBack && hasRight {*/
        /*const sourceIdx = localeIdx + (1,0,1);*/
        /*const sliceDesc = {myDom.dim(1).high+1..myDom.dim(1).high+1,*/
          /*myDom.dim(2), myDom.dim(3).high+1..myDom.dim(3).high+1};*/

        /*[>writeln(here, " will get " , sliceDesc, " from ",<]*/
            /*[>dom.dist.targetLocales(sourceIdx));<]*/
        /*__prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);*/
      /*}*/
      if hasFront && hasTop {
        const sourceIdx = localeIdx + (-1,-1,0);
        const sliceDesc = {myDom.dim(1).low-1..myDom.dim(1).low-1,
          myDom.dim(2).low-1..myDom.dim(2).low-1, myDom.dim(3)};

        /*writeln(here, " will get " , sliceDesc, " from ",*/
            /*dom.dist.targetLocales(sourceIdx));*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }
      /*if hasBack && hasBottom {*/
        /*const sourceIdx = localeIdx + (1,1,0);*/
        /*const sliceDesc = {myDom.dim(1).high+1..myDom.dim(1).high+1,*/
          /*myDom.dim(2).high+1..myDom.dim(2).high+1, myDom.dim(3)};*/

        /*[>writeln(here, " will get " , sliceDesc, " from ",<]*/
            /*[>dom.dist.targetLocales(sourceIdx));<]*/
        /*__prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);*/
      /*}*/
      if hasFront && hasTop && hasLeft {
        const sourceIdx = localeIdx + (-1,-1,-1);
        const sliceDesc = {myDom.dim(1).low-1..myDom.dim(1).low-1,
          myDom.dim(2).low-1..myDom.dim(2).low-1,
          myDom.dim(3).low-1..myDom.dim(3).low-1};

        /*writeln(here, " will get " , sliceDesc, " from ",*/
            /*dom.dist.targetLocales(sourceIdx));*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }
      /*if hasBack && hasBottom && hasRight{*/
        /*const sourceIdx = localeIdx + (1,1,1);*/
        /*const sliceDesc = {myDom.dim(1).high+1..myDom.dim(1).high+1,*/
          /*myDom.dim(2).high+1..myDom.dim(2).high+1,*/
          /*myDom.dim(3).high+1..myDom.dim(3).high+1};*/

        /*[>writeln(here, " will get " , sliceDesc, " from ",<]*/
            /*[>dom.dist.targetLocales(sourceIdx));<]*/
        /*__prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);*/
      /*}*/
      if hasLeft && hasTop {
        const sourceIdx = localeIdx + (0,-1,-1);
        const sliceDesc = {myDom.dim(1),
          myDom.dim(2).low-1..myDom.dim(2).low-1,
          myDom.dim(3).low-1..myDom.dim(3).low-1};

        /*writeln(here, " will get " , sliceDesc, " from ",*/
            /*dom.dist.targetLocales(sourceIdx));*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }
      /*if hasRight && hasBottom {*/
        /*const sourceIdx = localeIdx + (0,1,1);*/
        /*const sliceDesc = {myDom.dim(1),*/
          /*myDom.dim(2).high+1..myDom.dim(2).high+1,*/
          /*myDom.dim(3).high+1..myDom.dim(3).high+1};*/

        /*[>writeln(here, " will get " , sliceDesc, " from ",<]*/
            /*[>dom.dist.targetLocales(sourceIdx));<]*/
        /*__prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);*/
      /*}*/
    }
  }
  finalizePrefetch();
}
proc BlockArr.stencilPrefetch3d(consistent=true) {

  if rank != 3 then
    halt("This Prefetch pattern is only supprted for 3D arrays");

  //TODO FIXME TODO FIXME coforall --fixed
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      const myDom = dom.locDoms[localeIdx].myBlock;
      const tlDom = dom.dist.targetLocDom;

      const hasFront = localeIdx[1] > 0;
      const hasBack = localeIdx[1] < tlDom.dim(1).size-1;

      const hasTop = localeIdx[2] > 0;
      const hasBottom = localeIdx[2] < tlDom.dim(2).size-1;

      const hasLeft = localeIdx[3] > 0;
      const hasRight = localeIdx[3] < tlDom.dim(3).size-1;

      if hasFront {
        const sourceIdx = localeIdx + (-1,0,0);
        const sliceDesc = {myDom.dim(1).low-1..myDom.dim(1).low-1,
          myDom.dim(2), myDom.dim(3)};

        /*writeln(here, " will get " , sliceDesc, " from ",*/
            /*dom.dist.targetLocales(sourceIdx));*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }
      if hasBack {
        const sourceIdx = localeIdx + (1,0,0);
        const sliceDesc = {myDom.dim(1).high+1..myDom.dim(1).high+1,
          myDom.dim(2), myDom.dim(3)};

        /*writeln(here, " will get " , sliceDesc, " from ",*/
            /*dom.dist.targetLocales(sourceIdx));*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }

      if hasTop {
        const sourceIdx = localeIdx + (0,-1,0);
        const sliceDesc = {myDom.dim(1),
          myDom.dim(2).low-1..myDom.dim(2).low-1, myDom.dim(3)};

        /*writeln(here, " will get " , sliceDesc, " from ",*/
            /*dom.dist.targetLocales(sourceIdx));*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }
      if hasBottom {
        const sourceIdx = localeIdx + (0,1,0);
        const sliceDesc = {myDom.dim(1),
          myDom.dim(2).high+1..myDom.dim(2).high+1, myDom.dim(3)};

        /*writeln(here, " will get " , sliceDesc, " from ",*/
            /*dom.dist.targetLocales(sourceIdx));*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }

      if hasLeft {
        const sourceIdx = localeIdx + (0,0,-1);
        const sliceDesc = {myDom.dim(1),
          myDom.dim(2), myDom.dim(3).low-1..myDom.dim(3).low-1};

        /*writeln(here, " will get " , sliceDesc, " from ",*/
            /*dom.dist.targetLocales(sourceIdx));*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }
      if hasRight {
        const sourceIdx = localeIdx + (0,0,1);
        const sliceDesc = {myDom.dim(1),
          myDom.dim(2), myDom.dim(3).high+1..myDom.dim(3).high+1};

        /*writeln(here, " will get " , sliceDesc, " from ",*/
            /*dom.dist.targetLocales(sourceIdx));*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }
    }
  }
  finalizePrefetch();
}
proc BlockArr.stencilPrefetch(consistent=true, corners=false) {
  if rank != 2 then
    halt("This Prefetch pattern is only supprted for 2D arrays");

  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      const myDom = dom.locDoms[localeIdx].myBlock;
      const hasWest = localeIdx[2] > 0;
      const hasEast =  localeIdx[2] <
        dom.dist.targetLocDom.dim(2).size -1;

      const hasNorth = localeIdx[1] > 0;
      const hasSouth =  localeIdx[1] <
        dom.dist.targetLocDom.dim(1).size-1 ;

      //west
      if hasWest {
        const sourceIdx = localeIdx - (0,1);
        /*writeln(here, " my west is ", sourceIdx);*/
        const sliceDesc = {myDom.dim(1),
            myDom.dim(2).low-1..myDom.dim(2).low-1};
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }
      //east
      if hasEast {
        const sourceIdx = localeIdx + (0,1);
        /*writeln(here, " my east is ", sourceIdx);*/
        const sliceDesc = {myDom.dim(1),
            myDom.dim(2).high+1..myDom.dim(2).high+1};
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }
      //north
      if hasNorth {
        const sourceIdx = localeIdx - (1,0);
        /*writeln(here, " my north is ", sourceIdx);*/
        const sliceDesc = {myDom.dim(1).low-1..myDom.dim(1).low-1,
            myDom.dim(2)};
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }
      //south
      if hasSouth {
        const sourceIdx = localeIdx + (1,0);
        /*writeln(here, " my south is ", sourceIdx);*/
        const sliceDesc = {myDom.dim(1).high+1..myDom.dim(1).high+1,
            myDom.dim(2)};
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
      }

      if(corners) {
        if hasNorth && hasWest {
          const sourceIdx = localeIdx + (-1,-1);
          /*[>writeln(here, " my nw is ", sourceIdx);<]*/
            const sliceDesc = {myDom.dim(1).low-1..myDom.dim(1).low-1,
              myDom.dim(2).low-1..myDom.dim(2).low-1};
          __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);

        }
        if hasNorth && hasEast {
          const sourceIdx = localeIdx + (-1,1);
          /*[>writeln(here, " my ne is ", sourceIdx);<]*/
            const sliceDesc = {myDom.dim(1).low-1..myDom.dim(1).low-1,
              myDom.dim(2).high+1..myDom.dim(2).high+1};
          __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);

        }
        if hasSouth && hasWest {
          const sourceIdx = localeIdx + (1,-1);
          /*[>writeln(here, " my sw is ", sourceIdx);<]*/
            const sliceDesc = {myDom.dim(1).high+1..myDom.dim(1).high+1,
              myDom.dim(2).low-1..myDom.dim(2).low-1};
          __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);

        }
        if hasSouth && hasEast {
          const sourceIdx = localeIdx + (1,1);
          /*[>writeln(here, " my se is ", sourceIdx);<]*/
            const sliceDesc = {myDom.dim(1).high+1..myDom.dim(1).high+1,
              myDom.dim(2).high+1..myDom.dim(2).high+1};
          __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);

        }
      }
    }
  }
  finalizePrefetch();
}

inline proc BlockArr.finalizePrefetch() {
  coforall l in dom.dist.targetLocDom {
    on dom.dist.targetLocales[l] {
      locArr[l].prefetchHook.finalizePrefetch();
    }
  }
}

inline proc BlockCyclicArr.finalizePrefetch() {
  coforall l in dom.dist.targetLocDom {
    on dom.dist.targetLocales[l] {
      locArr[l].prefetchHook.finalizePrefetch();
    }
  }
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

proc BlockArr.rowWiseAllGather(consistent=true) {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      for i in dom.dist.targetLocDom.dim(2) {
        const sourceIdx = chpl__tuplify(i).withIdx(1, localeIdx[1]);
        __prefetchFrom(localeIdx, sourceIdx, consistent);
      }
    }
  }
  finalizePrefetch();
}

proc BlockArr.rowWiseAllGatherTranspose(consistent=true) {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      const myDom = dom.locDoms[localeIdx].myBlock;
      //what is the row range I am going to prefetch?
      const myColRange = dom.locDoms[localeIdx].myBlock.dim(2);
      const prefetchStartRowIdx = myColRange.low;
      const prefetchStopRowIdx = myColRange.high;
      const prefetchStartLocaleRowIdx =
        dom.dist.targetLocsIdx((prefetchStartRowIdx, 0))[1];
      const prefetchStopLocaleRowIdx =
        dom.dist.targetLocsIdx((prefetchStopRowIdx, 0))[1];

      /*writeln("**** ", here, " reports : ",*/
          /*prefetchStartRowIdx, " ", prefetchStopRowIdx, " ",*/
          /*prefetchStartLocaleRowIdx, " ",  prefetchStopLocaleRowIdx);*/
      const sliceDesc = {prefetchStartRowIdx..prefetchStopRowIdx,
        dom.whole.dim(2)};

      //prefetch from starting locales
      for i in dom.dist.targetLocDom.dim(2) {
        const sourceIdx = chpl__tuplify(i).withIdx(1,
            prefetchStartLocaleRowIdx);
        if(sourceIdx != localeIdx) {
          /*const sliceDesc = {prefetchStartRowIdx..myDom.dim(1).low-1,*/
            /*myDom.dim(2)};*/
          /*writeln(here, " will get ", sliceDesc, " from ",*/
              /*dom.dist.targetLocales[sourceIdx], " (start)");*/
          __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
        }
      }
      //prefetch from locales in between
      for row in
            prefetchStartLocaleRowIdx+1..prefetchStopLocaleRowIdx-1{
        for i in dom.dist.targetLocDom.dim(2) {
          const sourceIdx = chpl__tuplify(i).withIdx(1,
              row);
          if(sourceIdx != localeIdx) {
            /*writeln(here, " will get everything from ",*/
                /*dom.dist.targetLocales[sourceIdx], " (mid)");*/
            __prefetchFrom(localeIdx, sourceIdx, consistent);
          }
        }
      }
      //prefetch from ending locales
      if(prefetchStartLocaleRowIdx != prefetchStopLocaleRowIdx) {
        for i in dom.dist.targetLocDom.dim(2) {
          const sourceIdx = chpl__tuplify(i).withIdx(1,
              prefetchStopLocaleRowIdx);
          if(sourceIdx != localeIdx) {
            /*const sliceDesc = {myDom.dim(1).high+1..prefetchStopRowIdx,*/
              /*myDom.dim(2)};*/

            /*writeln(here, " will get ", sliceDesc, " from ",*/
                /*dom.dist.targetLocales[sourceIdx], " (end)");*/
            __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent);
          }
        }
      }
    }
  }
  /*halt("END");*/
  finalizePrefetch();
}

proc BlockArr.colWiseAllGather() {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      for i in dom.dist.targetLocDom.dim(1) {
        const sourceIdx = chpl__tuplify(i).withIdx(2, localeIdx[2]);
        __prefetchFrom(localeIdx, sourceIdx);
      }
    }
  }
}
// FIXME 8's must be changed with sizeof(eltType)

proc BlockArr.dsiSerializeIdx(i: idxType):int{
  return dsiSerializeIdx(chpl__tuplify(i));
}
proc BlockArr.dsiSerializeIdx(i: rank*idxType):int{
  if rank==1 then return 8*i[1];
  if rank==2 then return 8*(i[1]*dom.whole.dim(2).size+i[2]);
}
proc BlockArr.dsiDeserializeIdx(i) {
  if rank==1 then return i/8;
  if rank==2 then return ((i/8)/dom.whole.dim(2), (i/8)%dom.whole.dim(2));
}

inline proc __rowWiseSliceDom(dom, numElems, i, num) {
  /*const numRows = dom.dim(1).size;*/
  /*var (start, end) = _computeChunkStartEnd(numRows, num, i);*/
  /*start -= 1-dom.dim(1).low;*/
  /*end -= 1-dom.dim(1).low;*/
  //0-base specialization
  const (start, end) = _computeBlock(numElems, num, i, numElems-1);
  
  return {start..end, dom.dim(2)};
}



/*proc BlockArr.rowWiseAllPartialGather() {*/
  /*coforall localeIdx in dom.dist.targetLocDom {*/
    /*on dom.dist.targetLocales(localeIdx) {*/
      /*const numLocalesInCol = dom.dist.targetLocDom.dim(1).size;*/
      /*const numLocalesInRow = dom.dist.targetLocDom.dim(2).size;*/
      /*const rowSize = dom.whole.dim(2).size;*/
      /*for i in dom.dist.targetLocDom.dim(2) {*/
        /*const sourceIdx = chpl__tuplify(i).withIdx(1, localeIdx[1]);*/
        /*const locDom = dom.getLocDom(sourceIdx);*/
        /*[>writeln(localeIdx, " recieving ", <]*/
            /*[>__rowWiseSliceDom(locDom.myBlock, rowSize,<]*/
              /*[>localeIdx[1]*numLocalesInRow+localeIdx[2],<]*/
              /*[>dom.dist.targetLocales.size), " from ", sourceIdx);<]*/
        /*__prefetchFrom(sourceIdx, __rowWiseSliceDom(locDom.myBlock,*/
              /*rowSize, localeIdx[1]*numLocalesInRow+localeIdx[2],*/
              /*dom.dist.targetLocales.size));*/
      /*}*/
    /*}*/
  /*}*/
  /*[>halt("END");<]*/
/*}*/

proc BlockArr.rowWiseAllPrefetch(onlyCol) {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      const sourceIdx = chpl__tuplify(onlyCol).withIdx(1, localeIdx[1]);
      __prefetchFrom(localeIdx, sourceIdx);
    }
  }
}

proc BlockArr.colWiseAllPrefetch(onlyRow) {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      const sourceIdx = chpl__tuplify(onlyRow).withIdx(2, localeIdx[2]);
      __prefetchFrom(localeIdx, sourceIdx);
    }
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
