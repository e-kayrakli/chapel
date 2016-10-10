use commMethods;
use BlockDist;

config const N = 10;
const space = {0..#N, 0..#N};
const dom = space dmapped Block(space);
config const east = false;
config const west = false;
config const north = false;
config const south = false;
var arr: [dom] int;


forall (i,j) in dom do arr[i,j] = i*N+j;

arr._value.stencilPrefetch();

/*writeln(arr);*/
writeln();
writeln("Accessing prefetched data");
var sum = 0;
if east {
  writeln("East");
  on Locales[1] {
    for i in 0..#(N/2) {
      sum += arr[i, N/2-1]; //test east
    }
  }
}
if west {
  writeln(sum);
  writeln("West");
  on Locales[0] {
    for i in 0..#(N/2) {
      sum += arr[i, N/2]; //test west
    }
  }
}
if north {
  writeln(sum);
  writeln("North");
  on Locales[2] {
    for i in 0..#(N/2) {
      sum += arr[N/2-1, i]; //test north
    }
  }
}
if south {
  writeln(sum);
  writeln("South");
  on Locales[0] {
    for i in 0..#(N/2) {
      sum += arr[N/2, i]; //test south
    }
  }
  writeln(sum);
}
