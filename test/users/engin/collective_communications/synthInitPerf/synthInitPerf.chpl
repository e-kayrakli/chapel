use BlockDist;
use commMethods;
use Barrier;

config const prefetch = false;
config const N = 10;

const space = {0..#N, 0..#N};
const dom = space dmapped Block(space);

var arr: [dom] real;

var prefetchTime = 0.0;
var accessTime = 0.0;

const t = new Timer();

forall (i,j) in dom do arr[i,j] = i+j;

if prefetch {
  t.start();
  arr._value.allGather(consistent=false);
  t.stop();
  prefetchTime = t.elapsed();
  t.clear();

  t.start();
  coforall l in Locales do on l {
    var sum = 0.0;
    for i in arr.domain do sum += arr[i];
    writeln(here, " - ", sum);
  }
  t.stop();
  accessTime = t.elapsed();
}
else {
  var b = new Barrier(numLocales);
  t.start();
  coforall l in Locales with (ref prefetchTime) do on l {
    var localArr = arr;

    b.barrier();
    if l.id == 0 {
      t.stop();
      prefetchTime = t.elapsed();
      t.clear();

      t.start();
    }
    b.barrier();

    var sum = 0.0;
    for i in localArr.domain do sum += localArr[i];
    writeln(here, " - ", sum);
  }
  t.stop();
  accessTime = t.elapsed();
}

writeln("Prefetch Time = ", prefetchTime);
writeln("Access Time = ", accessTime);
