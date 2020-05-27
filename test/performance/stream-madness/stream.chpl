use Time;
use Memory;
use CommDiagnostics;

use BlockDist;
use CyclicDist;
use BlockCycDist;
use StencilDist;


type elemType = real;

config param nDims = 1;

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

config const nElemsTiny = numLocales;
config const nElemsSmall = if dMode==diagMode.correctness then 100 else 1000000;
config const nElemsLarge = numLocales*((totMem/numBytes(elemType))/memFraction)/3;

const nElems = if size == arraySize.tiny then nElemsTiny else
               if size == arraySize.small then nElemsSmall else
               if size == arraySize.large then nElemsLarge else -1;


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

var ranges: nDims*range;
for r in ranges {
  r = 0..#nElems;
}
const indexSpace = {(...ranges)};

proc createDefaultRect() {
  var D = indexSpace;

  var A: [D] elemType;
  var B: [D] elemType;
  var C: [D] elemType;

  return (D, A, B, C);
}

proc createBlock() {
  var D = newBlockDom(indexSpace);

  var A: [D] elemType;
  var B: [D] elemType;
  var C: [D] elemType;

  return (D, A, B, C);
}

proc createCyclic() {
  var D = newCyclicDom(indexSpace);

  var A: [D] elemType;
  var B: [D] elemType;
  var C: [D] elemType;

  return (D, A, B, C);
}

//proc createBlockCyc() {
  //var D = newBlockCycDom(indexSpace);

  //var A: [D] elemType;
  //var B: [D] elemType;
  //var C: [D] elemType;

  //return (D, A, B, C);
//}

proc runTest(D, A, B, C, oMode) {

  var diagName = dist:string+"-"+oMode:string;

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

proc runTests(D, A, B, C) {

  runTest(D, A, B, C, operationMode.promotion);
  runTest(D, A, B, C, operationMode.directIndex);
  runTest(D, A, B, C, operationMode.arrZip);
}

runTests((...createDefaultRect()));
runTests((...createBlock()));
runTests((...createCyclic()));
//runTests((...createBlockCyc));
