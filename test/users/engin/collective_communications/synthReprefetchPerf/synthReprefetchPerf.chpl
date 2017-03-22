use Random;
use BlockDist;
use commMethods;
use Barrier;

if numLocales <= 1 then
  halt("This test needs at least 2 locales");

config const staticDomain = false;
config const size = 10;
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
  const t = new Timer();
  var sum = 0.0;
  for (_,idx) in zip(1..#N, randomRemoteIndex()) {
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
