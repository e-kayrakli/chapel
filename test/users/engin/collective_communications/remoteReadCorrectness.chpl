use BlockDist;
use PrefetchPatterns;

config const N = 4;
const space = {1..N, 1..N};
const dom = space dmapped Block(space);
var arr: [dom] int;

forall a in arr do a = a.locale.id;

arr._value.stencilPrefetch();

for l in Locales do on l {
  writeln(l);
  for i in space.dim(1) {
    for j in space.dim(2) do
      write(arr[i,j], " ");
    writeln();
  }
  writeln();
}
