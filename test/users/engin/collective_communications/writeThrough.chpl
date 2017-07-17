use BlockDist;
use PrefetchPatterns;

config const prefetch = false;

const space = {1..10, 1..10};
var dom = space dmapped Block(space);
var arr: [dom] int;

if prefetch then arr._value.stencilPrefetch();

on Locales[0] {
  startCommDiagnostics();
  for i in 6..10 do
    arr[i,10] = 8;
  stopCommDiagnostics();
}

writeln(getCommDiagnostics());

on Locales[1] {
  writeln(arr);
}
