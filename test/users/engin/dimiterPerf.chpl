use LayoutCSR;
use Time;

config const N = 4096;
const PD = {0..#N, 0..#N};
var SD: sparse subdomain(PD) dmapped new dmap(new CSR());

config const nnzPerRowRate = 0.125;
const nnzPerRow = (N*nnzPerRowRate): int;

var SA: [SD] int;

var inds: [{0..#N*nnzPerRow}] 2*int;

const t = new Timer();

writeln("Start adding indices");
t.start();

for row in 0..#N {
  for i in 0..#nnzPerRow {
    SD += (row, ((i+row+4123)*179/3)%N);
  }
}
t.stop();
writeln("Index addition complete");
writeln("Index Addition Time: ", t.elapsed());
t.clear();

const testDom = {0..#nnzPerRow};

writeln("Start dim iteration");
t.start();
for row in 0..#N {
  /*for (f, i) in zip(testDom, SD.dimIter(2, row)) {*/
  forall (i, f) in zip(SD.dimIter(2, row), testDom) {
    SA[row, i] = f;
  }
  /*forall i in SD._value.dimIter(2, row) do SA[row, i] = i;*/
}
t.stop();
writeln("Dim iteration complete");
writeln("Dim itration time: ", t.elapsed());
t.clear();

/*for i in SD do writeln(i, " ", SA[i]);*/

