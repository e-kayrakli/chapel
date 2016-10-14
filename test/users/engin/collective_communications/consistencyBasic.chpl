use commMethods;
use BlockDist;
use Barrier;

var b = new Barrier(1);

config const N = 4;
const space = {0..#N};
var dom = space dmapped Block(space);
var arr: [dom] int;

forall i in dom do arr[i] = i;
arr._value.allGather();
directWrite();
forall i in dom do arr[i] += arr[i].locale.id+1;
b.barrier();
directWrite();

proc directWrite() {
  for l in Locales do on l {
    writeln(l);
    for i in arr.domain {
      write(arr[i], " ");
    }
    writeln();
  }
}
