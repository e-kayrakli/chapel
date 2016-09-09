use BlockDist;
use CommDiagnostics;

config const N = 4;
const space = {0..#N};
const dom = space dmapped Block(space);

var a: [dom] int;
var b: [dom] int;

forall i in dom {
  a[i] = i;
  b[i] = i+N;
}

/*writeln(a);*/
/*writeln(b);*/

var c: [dom] int;

startCommDiagnostics();
b._value.allBroadcast();
/*b._value.scratchPadMemDebug();*/
/*b._value.scratchPadMemDebug();*/
/*writeln(*/
    /*b._value.locArrsScratchPad[0][0]!=nil, " ", */
    /*b._value.locArrsScratchPad[0][1]!=nil, " ", */
    /*b._value.locArrsScratchPad[1][0]!=nil, " ", */
    /*b._value.locArrsScratchPad[1][1]!=nil);*/
forall i in dom {
  /*writeln("Assigning ", i, " from ", N-1-i, " on ", here);*/
  /*c._value.dsiAccess(i) = b._value.dsiAccess(N-1-i);*/
  c[i] = b[N-1-i];
}
stopCommDiagnostics();
writeln(c);

/*writeln();*/
writeln(getCommDiagnostics());

//all-to-all
proc BlockArr.allBroadcast() {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {

      for sourceIdx in dom.dist.targetLocDom {
        const locDom = dom.getLocDom(sourceIdx);
        writeln("Copying ", locDom.myBlock, " from ", sourceIdx, " to ",
            localeIdx, " on ", here);
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
  /*writeln("Broadcast finished");*/
  /*writeln(locArrsScratchPadFlags);*/
}

/*proc BlockArr.scratchPadMemDebug() {*/
  /*coforall l in dom.dist.targetLocDom {*/
    /*on dom.dist.targetLocales(l) {*/
      /*writeln(here);*/
      /*for x in dom.dist.targetLocDom do */
        /*writeln(locArrsScratchPad[here.id][x]!=nil);*/
    /*}*/
  /*}*/

/*}*/
