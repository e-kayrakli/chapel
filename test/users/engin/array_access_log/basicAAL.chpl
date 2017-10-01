use BlockDist;

config const N = 10;
const space = {0..#N, 0..#N};
const dom = space dmapped Block(space);
var arr: [dom] int;

/*forall (i,j) in dom do arr[i,j] = i+j;*/

arr.enableAccessLogging("arr");
for l in Locales do on l {
  var sum = 0.0;
  var i = (l.id*3)%N;
  for j in 0..#N {
    writeln("From app ", here, " ", (i,j));
    sum += arr[i,j];
  }
  writeln(here, " sum= ", sum);
}
