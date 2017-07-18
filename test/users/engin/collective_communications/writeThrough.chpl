use BlockDist;
use PrefetchPatterns;

config const prefetch = false;
config const commDiag = false;
config const consistent = false;

const space = {1..10, 1..10};
var dom = space dmapped Block(space);
var arr: [dom] int;

if prefetch then arr._value.stencilPrefetch(consistent=consistent);

on Locales[0] {
  if commDiag then startCommDiagnosticsHere();
  for i in 6..10 do
    for j in 1..1 do
      arr[i,j] = 8;
  if commDiag then stopCommDiagnosticsHere();
  print();
}

if commDiag then writeln(getCommDiagnosticsHere());

on Locales[1] {
  print();
}

proc print() {
  for i in space.dim(1) {
    for j in space.dim(2) {
      write(arr[i,j], " ");
    }
    writeln();
  }
}
