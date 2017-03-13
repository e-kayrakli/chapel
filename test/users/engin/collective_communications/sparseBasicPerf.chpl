use Time;
use commMethods;

config const N = 10;
config const prefetch = false;
config const consistent = true;

var space = {0..#N, 0..#N};

var dom = space dmapped Block(space, sparseLayoutType=DefaultDist);
var sparseDom: sparse subdomain(dom);

var sparseArr: [sparseDom] int;


var indices: [0..#N**2] 2*int;
var ind = 0;
for i in space {
  indices[ind] = i;
  ind += 1;
}
sparseDom.bulkAdd(indices, dataSorted=true, isUnique=true);

forall i in sparseDom do sparseArr[i] = here.id + 1;
const t1 = new Timer();
const t2 = new Timer();

t1.start();
if prefetch then
  sparseArr._value.allGather(consistent);
t1.stop();



var sums: [Locales.domain] int;


t2.start();
for l in Locales do on l {
  var sum = 0;
  for i in sparseDom do sum += sparseArr[i];
  sums[here.id] = sum;
}
t2.stop();

writeln(sums);
writeln("Prefetch setup : ", t1.elapsed());
writeln("Computation : ", t2.elapsed());
