use Time;
use Memory;
use CommDiagnostics;

use BlockDist;
use CyclicDist;
use BlockCycDist;
use StencilDist;

import Math;


type elemType = real;

config param nDims = 1;
config param slice = false;

param alpha = 2.0;

enum diagMode { performance, correctness, commCount, verboseComm, verboseMem };
enum operationMode { promotion, directIndex, arrZip };
enum arraySize { tiny, small, large };
enum distType { defaultRect, block, cyclic, blockCyc };

config const size = arraySize.tiny;
config const dist = distType.defaultRect;
config const dMode = diagMode.performance;

config const nIter = 4;

// assume homogeneity
const totMem = here.physicalMemory(unit = MemUnits.Bytes);
config const memFraction = 4;

config const nElemsTiny = numLocales*10;
config const nElemsSmall = if dMode==diagMode.correctness then 100 else 1000000;
config const nElemsLarge = numLocales*((totMem/numBytes(elemType))/memFraction)/3;
config const nElemsLargeOneLoc = ((totMem/numBytes(elemType))/memFraction)/3;


var t = new Timer();

inline proc startDiag(name) {
  select(dMode) {
    when diagMode.performance {
      t.start();
    }
    when diagMode.correctness { }
    when diagMode.commCount {
      startCommDiagnostics();
    }
    when diagMode.verboseComm {
      startVerboseComm();
    }
    when diagMode.verboseMem {
      startVerboseMem();
    }
    otherwise {
      halt("Unrecognized diagMode");
    }
  }
}

inline proc endDiag(name) {
  select(dMode) {
    when diagMode.performance {
      t.stop();
      writeln(name, ": ", t.elapsed());
      t.clear();
    }
    when diagMode.correctness { }
    when diagMode.commCount {
      stopCommDiagnostics();
      const d = getCommDiagnostics();
      writeln(name, "-GETS: ", + reduce (d.get + d.get_nb));
      writeln(name, "-PUTS: ", + reduce (d.put + d.put_nb));
      writeln(name, "-ONS: ", + reduce (d.execute_on + d.execute_on_fast +
                                        d.execute_on_nb));
      resetCommDiagnostics();
    }
    when diagMode.verboseComm {
      stopVerboseComm();
    }
    when diagMode.verboseMem {
      stopVerboseMem();
    }
    otherwise {
      halt("Unrecognized diagMode");
    }
  }
}

proc getMultiLocIndexSpace() {
  const nElems = if size == arraySize.tiny then nElemsTiny else
                 if size == arraySize.small then nElemsSmall else
                 if size == arraySize.large then nElemsLarge else -1;

  var ranges: nDims*range;
  for r in ranges {
    if nDims == 1 then
      r = 0..#nElems;
    else
      r = 0..#(Math.sqrt(nElems)):int;
  }
  return {(...ranges)};
}

proc getSingleLocIndexSpace() {
  const nElems = if size == arraySize.tiny then nElemsTiny else
                 if size == arraySize.small then nElemsSmall else
                 if size == arraySize.large then nElemsLargeOneLoc else -1;

  var ranges: nDims*range;
  for r in ranges {
    if nDims == 1 then
      r = 0..#nElems;
    else
      r = 0..#(Math.sqrt(nElems)):int;
  }
  return {(...ranges)};
}


proc createDefaultRect() {
  var D = getSingleLocIndexSpace();

  var A: [D] elemType;
  var B: [D] elemType;
  var C: [D] elemType;

  return slicifyIfNeeded(D, A, B, C);
}

proc createBlock() {
  var D = newBlockDom(getMultiLocIndexSpace());

  var A: [D] elemType;
  var B: [D] elemType;
  var C: [D] elemType;

  return slicifyIfNeeded(D, A, B, C);
}

proc createCyclic() {
  var D = newCyclicDom(getMultiLocIndexSpace());

  var A: [D] elemType;
  var B: [D] elemType;
  var C: [D] elemType;

  return slicifyIfNeeded(D, A, B, C);
}

inline proc slicifyIfNeeded(D, A, B, C) {
  if !slice {
    return (D, A, B, C);
  }
  else {
    if nDims == 1 {
      const DInner = D.expand(-1);
      return (DInner, A[DInner], B[DInner], C[DInner]);
    }
    else if nDims == 2 {
      const DInner = D.expand((-1,-1));
      return (DInner, A[DInner], B[DInner], C[DInner]);
    }
    else {
      compilerError("Wrong `nDims`: ", nDims);
    }
  }
}

proc runTest(D, A, B, C, oMode, keyPrefix: string) {

  var diagName = keyPrefix+"-"+oMode:string;

  if oMode == operationMode.promotion {
    A = B + alpha * C;
    startDiag(diagName);
    for i in 0..nIter {
      A = B + alpha * C;
    }
    endDiag(diagName);
  }
  else if oMode == operationMode.directIndex {
    forall i in D {
      A[i] = B[i] + alpha * C[i];
    }
    startDiag(diagName);
    for i in 0..nIter {
      forall i in D {
        A[i] = B[i] + alpha * C[i];
      }
    }
    endDiag(diagName);
  }
  else if oMode == operationMode.arrZip {
    forall (a,b,c) in zip(A,B,C) {
      a = b + alpha * c;
    }
    startDiag(diagName);
    for i in 0..nIter {
      forall (a,b,c) in zip(A,B,C) {
        a = b + alpha * c;
      }
    }
    endDiag(diagName);
  }
  else {
    halt("Unrecognized operation mode");
  }
}

proc runTests(D, A, B, C, keyPrefix: string) {
  runTest(D, A, B, C, operationMode.promotion, keyPrefix);
  runTest(D, A, B, C, operationMode.directIndex, keyPrefix);
  runTest(D, A, B, C, operationMode.arrZip, keyPrefix);
}

{
  runTests((...createDefaultRect()), "defaultRect");
}
{
  runTests((...createBlock()), "block");
}
{
  runTests((...createCyclic()), "cyclic");
}
