use LayoutCSR;
config const N = 10;

const parentDom = {0..#N, 0..#N};
var sparseDom: sparse subdomain(parentDom) dmapped CSR();

config const nnzPerRow = 3;

for r in parentDom.dim(1) {
  for nnz in 0..#nnzPerRow {
    sparseDom += (r, (r+nnz)%parentDom.dim(2).size);
  }
}

sparseDom._instance.setFixedNNZPerRow();
var sparseArr: [sparseDom] int = 1;

for i in parentDom.dim(1) {
  for j in parentDom.dim(2) {
    write(sparseArr[i,j], " ");
  }
  writeln();
}

writeln("*********************");


forall (i,j) in sparseDom do
  writeln(i,j);
