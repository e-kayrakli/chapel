/* for block this test tests the following slice assignments. All figures shown
   for 16 locales where the local array is in locale 0. 'X' denotes a
   transferred index

   localSubDom
   -----------
      |XX|  |  |  |
      |XX|  |  |  |
      ------------
      |  |  |  |  |
      |  |  |  |  |
      ------------
      |  |  |  |  |
      |  |  |  |  |
      ------------
      |  |  |  |  |
      |  |  |  |  |

   remoteSubDom
   -----------
      |  |  |  |  |
      |  |  |  |  |
      ------------
      |  |XX|  |  |
      |  |XX|  |  |
      ------------
      |  |  |  |  |
      |  |  |  |  |
      ------------
      |  |  |  |  |
      |  |  |  |  |

  quadrants
  ---------
      |  |  |  |  |
      | X|X |  |  |
      ------------
      | X|X |  |  |
      |  |  |  |  |
      ------------
      |  |  |  |  |
      |  |  |  |  |
      ------------
      |  |  |  |  |
      |  |  |  |  |

  full
  ----
      |XX|XX|XX|XX|
      |XX|XX|XX|XX|
      ------------
      |XX|XX|XX|XX|
      |XX|XX|XX|XX|
      ------------
      |XX|XX|XX|XX|
      |XX|XX|XX|XX|
      ------------
      |XX|XX|XX|XX|
      |XX|XX|XX|XX|

  unbalanced (shown bigger only to properly demonstrate)
  ----------
      |    |    |    |    |
      |    |    |    |    |
      |    |    |    |    |
      |   X|XXXX|XXX |    |
      ---------- ---------
      |   X|XXXX|XXX |    |
      |   X|XXXX|XXX |    |
      |   X|XXXX|XXX |    |
      |   X|XXXX|XXX |    |
      ---------- ---------
      |   X|XXXX|XXX |    |
      |   X|XXXX|XXX |    |
      |   X|XXXX|XXX |    |
      |    |    |    |    |
      ---------- ---------
      |    |    |    |    |
      |    |    |    |    |
      |    |    |    |    |
      |    |    |    |    |

*/
use Time;
use Memory;
use CommDiagnostics;

use BlockDist;
use CyclicDist;
use BlockCycDist;
use StencilDist;

var t = new Timer();

type elemType = int;
param elemSize = numBytes(int);

enum diagMode { performance, correctness, commCount, verboseComm, verboseMem };
enum arraySize { tiny, small, large };
enum distType { block, cyclic, blockCyc, stencil };
enum sliceType { localSubDom, remoteSubDom, quadrants, full, unbalanced };

config const memFraction = 4;

config const size = arraySize.tiny;
config const dist = distType.block;
config const mode = diagMode.performance;
config const slice = sliceType.localSubDom;

// num elems in the DefaultRectangular
config const nBytesTiny = 4*elemSize;
config const nBytesSmall = 8192;
config const nBytesLarge = here.physicalMemory(unit=MemUnits.Bytes)/memFraction;

const nElems = if size == arraySize.tiny then nBytesTiny/elemSize else
               if size == arraySize.small then nBytesSmall/elemSize else
               if size == arraySize.large then nBytesLarge/elemSize else -1;

// create the local array
const localDimSize = getRootOfNearestSquare(nElems);
const localDom = {0..#localDimSize, 0..#localDimSize};
var localArr: [localDom] elemType;

// create the distributed array
const sqrtNumLocales = sqrt(numLocales):int;
assert(sqrtNumLocales == sqrt(numLocales));
var distDimSize: int;
var distDimStart: int;

// the below logic makes sense only with block (and stencil?)
select slice {
  when sliceType.localSubDom {
    distDimSize = localDimSize * sqrtNumLocales;
    distDimStart = 0;
  }
  when sliceType.remoteSubDom {
    // the local one == local subdomain
    distDimSize = localDimSize * sqrtNumLocales;
    distDimStart = 0-localDimSize;
  }
  when sliceType.quadrants {
    // local one overlaps with 4 locales symmetrically
    distDimSize = localDimSize * sqrtNumLocales;
    distDimStart = 0-localDimSize/2;
  }
  when sliceType.full {
    distDimSize = localDimSize;
    distDimStart = 0;
  }
  when sliceType.unbalanced {
    // a smaller inner domain that is sized to cover inner locales'
    // subdomains but shifted a quarter of the way
    assert(numLocales>=9); // doesn't make sense otherwise
    distDimSize = (localDimSize * (1.0*sqrtNumLocales/(sqrtNumLocales-2))):int;
    distDimStart = 0-(distDimSize/sqrtNumLocales*0.75):int;
  }
}

const distSpace = {distDimStart..#distDimSize, distDimStart..#distDimSize};
const distDom = distSpace dmapped Block(distSpace);
var distArr: [distDom] elemType;

// initialize the array
forall a in distArr do a = a.locale.id;

// report what is going to happen
writeln("Slice assigment benchmark from distributed to local array");
writeln("Number of locales: ", numLocales);
writeln("Distributed array size: ", distDimSize, "x", distDimSize,
                                 " --- ", distSpace);
writeln("Local array size: ", localDimSize, "x", localDimSize,
                           " --- ", localDom);
writeln("Slice type: ", slice);

writef("Total data to be transferred: %10i bytes\n", localDom.size*elemSize);
for l in Locales do on l { 
  writef("\t%s -> %s: %10i bytes\n", here:string, localArr.locale:string,
          distDom.localSubdomain()[localDom].size*elemSize);
}


startDiag();
localArr = distArr[localDom];
endDiag();

inline proc startDiag() {
  select(mode) {
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

inline proc endDiag() {

  select(mode) {
    when diagMode.performance {
      t.stop();
      const timeSpent = t.elapsed();
      writeln("Time : ", timeSpent, " seconds");
      writeln("Throughput : ", localDom.size*elemSize/timeSpent/1_000_000,
                               "MB/s");
      t.clear();
    }
    when diagMode.correctness { }
    when diagMode.commCount {
      stopCommDiagnostics();
      const d = getCommDiagnostics();
      writeln("GETS: ", + reduce (d.get + d.get_nb));
      writeln("PUTS: ", + reduce (d.put + d.put_nb));
      writeln("ONS: ", + reduce (d.execute_on + d.execute_on_fast +
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

proc getRootOfNearestSquare(n) {
  return floor(sqrt(n)):int;
}

