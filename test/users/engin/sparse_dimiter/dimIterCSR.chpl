use LayoutCSR;

config const N = 10;

const ParentDom = {0..#N, 0..#N};
var SparseDom: sparse subdomain(ParentDom) dmapped CSR();
var SparseMat: [SparseDom] int;

// create cool set of sparse indices
for i in 0..#N {
  for j in 0..#N by 2 align i%2 {
    SparseDom += (i, j);
  }
} 

for (i,n) in zip(SparseDom, 1..) {
  SparseMat[i] = n;
}

for i in ParentDom.dim(1) {
  for j in ParentDom.dim(2) {
    writef("%2i ", SparseMat[i, j]);
  }
  writeln();
}

writeln("Even rows:");
for r in 0..#N by 2 {
  forall i in SparseDom.dimIter(2, r) {
    writef("%2i ", SparseMat[r, i]);
  }
  writeln();
}

writeln("Odd rows:");
for r in 0..#N by 2 align 1{
  forall i in SparseDom.dimIter(2, r) {
    writef("%2i ", SparseMat[r, i]);
  }
  writeln();
}

writeln("Even cols:");
for r in 0..#N by 2 {
  forall i in SparseDom.dimIter(1, r) {
    writef("%2i ", SparseMat[i, r]);
  }
  writeln();
}

writeln("Odd cols:");
for r in 0..#N by 2 align 1{
  forall i in SparseDom.dimIter(1, r) {
    writef("%2i ", SparseMat[i, r]);
  }
  writeln();
}
