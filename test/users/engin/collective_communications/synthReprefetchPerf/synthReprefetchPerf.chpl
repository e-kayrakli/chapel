use Random;
use BlockDist;
use commMethods;
use Barrier;

if numLocales <= 1 then
  halt("This test needs at least 2 locales");

config const staticDomain = false;
config const size = 2048;
config const N = 5;

const space = {0..#size, 0..#size};
const dom = space dmapped Block(space);

var arr: [dom] real;

var prefetchTime = 0.0;
var accessTime = 0.0;


forall (i,j) in dom do arr[i,j] = i+j;

const b = new Barrier(numLocales);

arr._value.allGather(consistent=true, staticDomain=staticDomain);

var times: [Locales.domain] real;

coforall l in Locales do on l {
  var rrIdxDom = {0..#N};
  var rrIdxArr: [rrIdxDom] 2*int;

  for (rr,idx) in zip(rrIdxArr, randomRemoteIndex()) {
    rr = idx;
  }
  var t = new Timer();
  var sum = 0.0;
  for idx in rrIdxArr {
    t.start();
    sum += arr[idx];
    t.stop();
    b.barrier();
  }
  times[here.id] = t.elapsed();
}

for i in Locales.domain do writeln(Locales[i], ": ", times[i]);

writeln("Min:  ", (min reduce times));
writeln("Max:  ", (max reduce times));
writeln("Mean: ", (+ reduce times)/times.size);

iter randomRemoteIndex() {
  const rs = makeRandomStream(eltType=uint, seed=7);
  const locSubDom = dom.localSubdomain();

  var idx: 2*int;
  while true {
    do {
      idx = (rs.getNext()%size:uint, rs.getNext()%size:uint):idx.type;
    } while(locSubDom.member(idx));

    yield idx;
  }
}
