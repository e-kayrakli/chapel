use BlockDist;
use BlockCycDist;

// for checking whether paths are correct
use FileSystem;

/*config const predictorScriptPath =*/
          /*"/home/ngnk/code/nn_for_lapps/predict.py";*/
/*config const predictorModelPath = "";*/
/*config const tinyDNNPath = "/home/ngnk/code/test-tiny-dnn/";*/
/*config const tinyDNNModelPath = "";*/

config const tinyDNN = false;
config const autoPrefetchPredictorPath = "";
config const autoPrefetchUnpackerPath = "";
config const autoPrefetchModelPath = "";

inline proc BlockArr.updatePrefetch() {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      locArr[localeIdx].getPrefetchHook().updatePrefetch();
    }
  }
}

inline proc BlockArr.updatePrefetchHere() {
    myLocArr.getPrefetchHook().updatePrefetch();
}

inline proc BlockArr.spmdUpdatePrefetch(tid) {
  myLocArr.getPrefetchHook().spmdUpdatePrefetch(tid);
}

proc BlockArr.reportPrefetch() {
  for localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      locArr[localeIdx].prefetchHook.reportPrefetchTimes();
    }
  }
}

inline proc BlockArr.__prefetchFrom(localeIdx, sourceIdx, consistent,
    staticDomain=false) {
  var privCopy = chpl_getPrivatizedCopy(this.type, this.pid);
  locArr[localeIdx].prefetchHook.requestPrefetch(
      sourceIdx,
      privCopy.locArr[sourceIdx],
      consistent=consistent, staticDomain=staticDomain);
}

inline proc SparseBlockArr.__prefetchFrom(localeIdx, sourceIdx,
    consistent, staticDomain=false) {
  /*var privCopy = chpl_getPrivatizedCopy(this.type, this.pid);*/
  locArr[localeIdx].prefetchHook.requestPrefetch(
      sourceIdx, //TODO this can be avoided
      locArr[sourceIdx],
      consistent, staticDomain);
}

inline proc BlockArr.__prefetchFrom(localeIdx, sourceIdx, sliceDesc,
    consistent, staticDomain=false) {
  var privCopy = chpl_getPrivatizedCopy(this.type, this.pid);
  /*writeln(here, " prefetch from LOCALE", sourceIdx, " the slice ", sliceDesc);*/
  locArr[localeIdx].prefetchHook.requestPrefetch( sourceIdx,
      privCopy.locArr[sourceIdx], sliceDesc,
      locArr[sourceIdx].locDom.myBlock, consistent, staticDomain);
}

proc BlockCyclicArr.__prefetchFrom(localeIdx, sourceIdx,
    consistent, staticDomain) {

  var privCopy = chpl_getPrivatizedCopy(this.type, this.pid);
  locArr[localeIdx].prefetchHook.requestPrefetch(
      dom.dist.targetLocales[sourceIdx].id, //TODO this can be avoided
      privCopy.locArr[sourceIdx],
      consistent, staticDomain);
}

proc BlockArr.customPrefetch(consistent=true, descTable,
    staticDomain=false) {
  if descTable.rank != 2 then
    halt("Description talbe must be two-dimensional");

  coforall l in descTable.domain.dim(1) do on Locales[l] {
    var localeIdx = locIdxFromId(l);
    for l2 in descTable.domain.dim(2) {
      var sliceDesc = descTable[l,l2];
      if sliceDesc.numIndices != 0 {
        var sourceIdx = locIdxFromId(l2);
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc,
            consistent, staticDomain=staticDomain);
      }
    }
  }

  proc locIdxFromId(id) {
    for (i,l) in zip(dom.dist.targetLocDom, dom.dist.targetLocales) do
      if l.id == id then
        return chpl__tuplify(i);

    var dummy: rank*int;
    return dummy;
  }
}

proc getPred(arr_name, locdom, whole) {
  use Spawn;
  proc domToTup(dom) {
    var retval: 2*dom.rank*int;
    var counter = 0;
    for r in dom.dims() {
      retval[2*counter+1] = r.low;
      retval[2*counter+2] = r.high;
      counter += 1;
    }
    return retval;
  }

  proc domToTinyDNNString(dom) {
    var retval = "";
    for r in dom.dims() {
      retval += r.low;
      retval += " ";
      retval += r.high;
      retval += " ";
    }

    return retval.strip();
  }

  /*writeln(here, " locdom ", locdom);*/
  /*writeln(here, " whole ", whole);*/

  var locdomRepr : string;
  var wholeRepr : string;

  var trainCmdList = new list(string);

  if autoPrefetchPredictorPath == "" then
    halt("autoPrefetchPredictorPath cannot be empty");
  if autoPrefetchModelPath == "" then
    halt("autoPrefetchPredictorPath cannot be empty");
  if !exists(autoPrefetchPredictorPath) then
    halt("autoPrefetchPredictorPath invalid ", autoPrefetchPredictorPath);
  /*if !exists(autoPrefetchModelPath) then*/
    /*halt("autoPrefetchModelPath invalid", autoPrefetchModelPath);*/


  if tinyDNN {
    if autoPrefetchUnpackerPath == "" then
      halt("autoPrefetchUnpackerPath cannot be empty");
    if !exists(autoPrefetchUnpackerPath) then
      halt("autoPrefetchUnpackerPath invalid");

    locdomRepr = domToTinyDNNString(locdom):string;
    wholeRepr = domToTinyDNNString(whole):string;
    trainCmdList.append(autoPrefetchPredictorPath + " " +
                        "$(" + autoPrefetchUnpackerPath +  " " +
                            autoPrefetchModelPath + " loc" + here.id + 
                            ")/arr"+arr_name+"_modelbest " +
                        "\"" + locdomRepr + "\" "+
                        "\"" + wholeRepr + "\"");
  }
  else {
    locdomRepr = domToTup(locdom):string;
    wholeRepr = domToTup(whole):string;
    trainCmdList.append("/mnt/lustre_server/users/engin/miniconda3/envs/nn/bin/python", autoPrefetchPredictorPath,
                        arr_name,
                        locdomRepr,
                        wholeRepr,
                        "--write-to-file",
                        "--pred-only");
  }

  var trainCmd: [{0..#trainCmdList.size}] trainCmdList.eltType;

  for (c,l) in zip(trainCmd, trainCmdList) {
    c = l;
  }

  var sub = if tinyDNN then
              spawnshell(trainCmd[0], stdout=FORWARD, stderr=FORWARD)
            else
              spawn(trainCmd, stdout=FORWARD, stderr=FORWARD);

  sub.wait();
  if sub.exit_status != 0 then
    halt("There was an error running ", trainCmd);

  var ranges: locdom.rank*range;

  var predFile = open("prediction", iomode.r);
  var predFileChannel = predFile.reader();
  var dim = 1;
  while true {

    /*var line:string;*/
    var x: int;
    if !predFileChannel.read(x) then
      break;
    /*writeln("From predictor: ", line);*/
    var lo = x;
    predFileChannel.read(x);
    /*writeln("From predictor: ", line);*/
    var hi = x;
    ranges[dim] = lo..hi;
    dim += 1;
  }



  const rawDom = {(...ranges)}.expand((whole.dim(1).size*0.01):int);
  return rawDom[whole];
}

proc BlockArr.autoPrefetch(arr_name, consistent=true, staticDomain=false) {
  var accDoms: [Locales.domain] domain(this.rank);
  for l in Locales do on l {
    accDoms[l.id] = getPred(arr_name, dom.dsiLocalSubdomain(), this.dom.whole);
    writeln(here, " access domain: ", accDoms[l.id]);
  }

  // 1. this is very centralized and likely unscalable. In the future,
  //    when tinydnn or a similar library is used, this needs to be done
  //    in a decentralized way
  // 2. Internally, the predict script predicts only for a single data
  //    point. If we are moving forward in this direction, then the data
  //    can be passed to predict in one go significantly reducing the
  //    initialization time of keras.
  coforall l in Locales do on l {
    var privCopy = chpl_getPrivatizedCopy(this.type, this.pid);
    const localeIdx = locIdxFromId(l.id);
    /*const accDom = getPred(arr_name, dom.dsiLocalSubdomain(), this.dom.whole);*/
    const accDom = accDoms[l.id];
    for sourceId in 0..#numLocales {
      const sourceIdx = locIdxFromId(sourceId);
      const toPrefetch = accDom[privCopy.locArr[sourceIdx].locDom.myBlock];

      /*writeln(here, " will prefetch ", toPrefetch, " from ", sourceId);*/

      __prefetchFrom(localeIdx, sourceIdx, toPrefetch, consistent,
          staticDomain);
    }
  }

  proc locIdxFromId(id) {
    for (i,l) in zip(dom.dist.targetLocDom, dom.dist.targetLocales) do
      if l.id == id then
        return chpl__tuplify(i);

    var dummy: rank*int;
    return dummy;
  }
}

// number of locales must be square
proc BlockArr.transposePrefetch(consistent=true, staticDomain=false) {

  const tld = dom.dist.targetLocDom;
  if tld.rank != 2 then
    halt("Only 2D array s can be transpose-prefetched");

  inline proc checkFastPrefetch() {
    if dom.whole.dim(1).length ==  dom.whole.dim(2).length {
      if tld.dim(1).length == tld.dim(2).length {
        if dom.whole.dim(1).length % tld.dim(1).length == 0 {
          return true;
        }
      }
    }
    return false;
  }

  // perfect divisibility and full-square distribution avoids some of
  // the computation during the initialization
  if checkFastPrefetch() {
    coforall localeIdx in dom.dist.targetLocDom {
      on dom.dist.targetLocales(localeIdx) {
        const sourceIdx = (localeIdx[2], localeIdx[1]);
        __prefetchFrom(localeIdx, sourceIdx, consistent,
            staticDomain=staticDomain);
      }
    }
  }
  // there are some divisibility "issue", be pessimistic and assume
  // everyone can have something to prefetch from everyone
  else {     
    coforall localeIdx in dom.dist.targetLocDom {
      on dom.dist.targetLocales(localeIdx) {

        const locSubDom = dom.dsiLocalSubdomain();
        const locSubDomT = {locSubDom.dim(2), locSubDom.dim(1)};
        /*writeln(this.locale, " ", here, "locSubDom=", locSubDom);*/
        /*writeln(this.locale, " ", here, "locSubDomT=", locSubDomT);*/
        for sourceIdx in dom.dist.targetLocDom {
          const intersectDom =  dom.locDoms[sourceIdx].myBlock[locSubDomT];
          if intersectDom.size != 0 {
            __prefetchFrom(localeIdx, sourceIdx, intersectDom,
                consistent, staticDomain=staticDomain);
          }
        }
      }
    }
  }
  /*writeln("Finalizing prefetch");*/
  finalizePrefetch();
}

proc BlockCyclicArr.transposePrefetch(consistent=true) {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      const sourceIdx = (localeIdx[2], localeIdx[1]);
      __prefetchFrom(localeIdx, sourceIdx, consistent,
          staticDomain=false);
    }
  }
  /*writeln("Finalizing prefetch");*/
  finalizePrefetch();
}

proc BlockArr.allGather(consistent=true, staticDomain=false) {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      for sourceIdx in dom.dist.targetLocDom {
        __prefetchFrom(localeIdx, sourceIdx, consistent=consistent,
            staticDomain=staticDomain);
      }
    }
  }
  finalizePrefetch();
}

proc SparseBlockArr.allGather(consistent=true, staticDomain=false) {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      for sourceIdx in dom.dist.targetLocDom {
        __prefetchFrom(localeIdx, sourceIdx, consistent,
            staticDomain=staticDomain);
      }
    }
  }
  finalizePrefetch();
}

proc BlockArr.luleshStencilPrefetch3d(consistent=true,
    staticDomain=false) {

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
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain=staticDomain);
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
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain=staticDomain);
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
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain=staticDomain);
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
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain=staticDomain);
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
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain=staticDomain);
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
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain=staticDomain);
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
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain=staticDomain);
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

proc BlockArr.MGPrefetch(consistent=true, staticDomain=false) {
  const tldShape = dom.dist.targetLocDom.shape;

  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {

      const myDom = dom.locDoms[localeIdx].myBlock;
      const whole = dom.whole;

      inline proc getSrcAndRanges(param dim, param neg) {
        // calculate the source idx
        var offTuple = (0,0,0);
        offTuple[dim] = if neg then -1 else 1;
        const sourceIdx = ((localeIdx+offTuple)+tldShape)%tldShape;

        // calculate the wrapped index
        var wrappedIdx: int;
        if neg {
          const bound = whole.dim(dim).low;
          wrappedIdx = myDom.dim(dim).low-1;
          if wrappedIdx < bound then
            wrappedIdx += whole.dim(dim).size;
        }
        else {
          const bound = whole.dim(dim).high;
          wrappedIdx = myDom.dim(dim).high+1;
          if wrappedIdx > bound then
            wrappedIdx -= whole.dim(dim).size;
        }

        var ranges = (myDom.dim(1), myDom.dim(2), myDom.dim(3));
        ranges[dim] = wrappedIdx..wrappedIdx;

        return (sourceIdx, ranges);
      }

      for param d in 1..3 {
        for param _n in 0..1 {
          param n = _n==0;
          const (sourceIdx, _r) = getSrcAndRanges(dim=d, neg=n);
          var sliceDesc: domain(3);
          sliceDesc = {(..._r)};
          writeln(here, " will get " , sliceDesc, " from ",
              dom.dist.targetLocales(sourceIdx));
          __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
              staticDomain);
        }
      }
    }
  }
}

proc BlockArr.stencilPrefetch3d(consistent=true, staticDomain=false) {

  if rank != 3 then
    halt("This Prefetch pattern is only supprted for 3D arrays");

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
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain);
      }
      if hasBack {
        const sourceIdx = localeIdx + (1,0,0);
        const sliceDesc = {myDom.dim(1).high+1..myDom.dim(1).high+1,
          myDom.dim(2), myDom.dim(3)};

        /*writeln(here, " will get " , sliceDesc, " from ",*/
            /*dom.dist.targetLocales(sourceIdx));*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain);
      }

      if hasTop {
        const sourceIdx = localeIdx + (0,-1,0);
        const sliceDesc = {myDom.dim(1),
          myDom.dim(2).low-1..myDom.dim(2).low-1, myDom.dim(3)};

        /*writeln(here, " will get " , sliceDesc, " from ",*/
            /*dom.dist.targetLocales(sourceIdx));*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain);
      }
      if hasBottom {
        const sourceIdx = localeIdx + (0,1,0);
        const sliceDesc = {myDom.dim(1),
          myDom.dim(2).high+1..myDom.dim(2).high+1, myDom.dim(3)};

        /*writeln(here, " will get " , sliceDesc, " from ",*/
            /*dom.dist.targetLocales(sourceIdx));*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain);
      }

      if hasLeft {
        const sourceIdx = localeIdx + (0,0,-1);
        const sliceDesc = {myDom.dim(1),
          myDom.dim(2), myDom.dim(3).low-1..myDom.dim(3).low-1};

        /*writeln(here, " will get " , sliceDesc, " from ",*/
            /*dom.dist.targetLocales(sourceIdx));*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain);
      }
      if hasRight {
        const sourceIdx = localeIdx + (0,0,1);
        const sliceDesc = {myDom.dim(1),
          myDom.dim(2), myDom.dim(3).high+1..myDom.dim(3).high+1};

        /*writeln(here, " will get " , sliceDesc, " from ",*/
            /*dom.dist.targetLocales(sourceIdx));*/
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain);
      }
    }
  }
  finalizePrefetch();
}
proc BlockArr.stencilPrefetch(consistent=true, corners=false, depth=1,
    staticDomain=false) {
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
            myDom.dim(2).low-depth..myDom.dim(2).low-1};
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain);
      }
      //east
      if hasEast {
        const sourceIdx = localeIdx + (0,1);
        /*writeln(here, " my east is ", sourceIdx);*/
        const sliceDesc = {myDom.dim(1),
            myDom.dim(2).high+1..myDom.dim(2).high+depth};
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain);
      }
      //north
      if hasNorth {
        const sourceIdx = localeIdx - (1,0);
        /*writeln(here, " my north is ", sourceIdx);*/
        const sliceDesc = {myDom.dim(1).low-depth..myDom.dim(1).low-1,
            myDom.dim(2)};
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain);
      }
      //south
      if hasSouth {
        const sourceIdx = localeIdx + (1,0);
        /*writeln(here, " my south is ", sourceIdx);*/
        const sliceDesc = {myDom.dim(1).high+1..myDom.dim(1).high+depth,
            myDom.dim(2)};
        __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
            staticDomain);
      }

      if(corners) {
        if hasNorth && hasWest {
          const sourceIdx = localeIdx + (-1,-1);
          /*[>writeln(here, " my nw is ", sourceIdx);<]*/
            const sliceDesc =
            {myDom.dim(1).low-depth..myDom.dim(1).low-1,
              myDom.dim(2).low-depth..myDom.dim(2).low-1};
          __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
              staticDomain);

        }
        if hasNorth && hasEast {
          const sourceIdx = localeIdx + (-1,1);
          /*[>writeln(here, " my ne is ", sourceIdx);<]*/
            const sliceDesc =
            {myDom.dim(1).low-depth..myDom.dim(1).low-1,
              myDom.dim(2).high+1..myDom.dim(2).high+depth};
          __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
              staticDomain);

        }
        if hasSouth && hasWest {
          const sourceIdx = localeIdx + (1,-1);
          /*[>writeln(here, " my sw is ", sourceIdx);<]*/
            const sliceDesc =
            {myDom.dim(1).high+1..myDom.dim(1).high+depth,
              myDom.dim(2).low-depth..myDom.dim(2).low-1};
            __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
                staticDomain);

        }
        if hasSouth && hasEast {
          const sourceIdx = localeIdx + (1,1);
          /*[>writeln(here, " my se is ", sourceIdx);<]*/
            const sliceDesc =
            {myDom.dim(1).high+1..myDom.dim(1).high+depth,
              myDom.dim(2).high+1..myDom.dim(2).high+depth};
            __prefetchFrom(localeIdx, sourceIdx, sliceDesc, consistent,
                staticDomain);

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

inline proc SparseBlockArr.finalizePrefetch() {
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
/*
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
 */

proc BlockArr.rowWiseAllGather(consistent=true, staticDomain=false) {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      for i in dom.dist.targetLocDom.dim(2) {
        const sourceIdx = chpl__tuplify(i).withIdx(1, localeIdx[1]);
        __prefetchFrom(localeIdx, sourceIdx, consistent,
            staticDomain=staticDomain);
      }
    }
  }
  finalizePrefetch();
}

proc SparseBlockArr.rowWiseAllGather(consistent=true, staticDomain=false) {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      for i in dom.dist.targetLocDom.dim(2) {
        const sourceIdx = chpl__tuplify(i).withIdx(1, localeIdx[1]);
        __prefetchFrom(localeIdx, sourceIdx, consistent,
            staticDomain=staticDomain);
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

proc BlockArr.colWiseAllGather(consistent=true, staticDomain=false) {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      for i in dom.dist.targetLocDom.dim(1) {
        const sourceIdx = chpl__tuplify(i).withIdx(2, localeIdx[2]);
        __prefetchFrom(localeIdx, sourceIdx, consistent,
            staticDomain=staticDomain);
      }
    }
  }
}

proc SparseBlockArr.colWiseAllGather(consistent=true, staticDomain=false) {
  coforall localeIdx in dom.dist.targetLocDom {
    on dom.dist.targetLocales(localeIdx) {
      for i in dom.dist.targetLocDom.dim(1) {
        const sourceIdx = chpl__tuplify(i).withIdx(2, localeIdx[2]);
        __prefetchFrom(localeIdx, sourceIdx, consistent,
            staticDomain=staticDomain);
      }
    }
  }
}

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
