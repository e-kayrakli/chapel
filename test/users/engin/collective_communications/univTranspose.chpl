use BlockDist;
use PrefetchPatterns;

config const N = 8;
config const prefetch = false;
config const shouldPrint = false;
const space = {0..#N, 0..#N};
var dom = space dmapped Block(space);
var arr: [dom] int;

forall a in arr do a = a.locale.id + 10;

if prefetch then arr._value.transposePrefetch(consistent=false);

for l in Locales do on l {
  if shouldPrint then print();
  writeln(sum());

  writeln("\nLOCALE FINISHED ***********\n");
}

proc print() {
  writeln(here);
  startCommDiagnosticsHere();
  for i in space.dim(1) {
    for j in space.dim(2) {
      write(arr[i,j], " ");
    }
    writeln();
  }
  stopCommDiagnosticsHere();
  writeln(getCommDiagnosticsHere());
}

proc sum() {
  writeln(here);
  var sum = 0;
  const dim1 = dom.localSubdomain().dim(2);
  const dim2 = dom.localSubdomain().dim(1);
  startCommDiagnosticsHere();
  for i in dim1 {
    for j in dim2 {
      sum += arr[i,j];
    }
  }
  stopCommDiagnosticsHere();
  writeln(getCommDiagnosticsHere());
  return sum;
}
