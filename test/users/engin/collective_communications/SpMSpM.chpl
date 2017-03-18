use Random;
use LayoutCSR;
use commMethods;
use Time;

config const prefetch = false;
config const consistent = true;
config const staticDomain = false;

config const N = 10;
config const nnzPerRow = 3;
config type sparseLayoutType = CSR;

config const outputData = false;

const space = {0..#N, 0..#N};
var distDom = space dmapped Block(boundingBox=space,
    sparseLayoutType=sparseLayoutType);

var indicesDom = {0..#N*nnzPerRow};
var indices: [indicesDom] 2*int;

var sparseDomA: sparse subdomain(distDom);
var sparseDomB: sparse subdomain(distDom);

// TODO initialize sparse arrays after populating the domains
var A: [sparseDomA] real;
var B: [sparseDomB] real;

var C: [distDom] real; // result matrix is dense

// create indices for domains
var rs = makeRandomStream(seed=3, eltType=int); // deterministic arrays

indexArrayHelper();
sparseDomA.bulkAdd(indices, preserveInds=false);
indexArrayHelper();
sparseDomB.bulkAdd(indices, preserveInds=false);

A = 3;
B = 5;

if outputData {
  matWriter(A);
  writeln();
  matWriter(B);
  writeln();
}

const t = new Timer();


t.start();
if prefetch {
  A._value.rowWiseAllGather(consistent, staticDomain);
  B._value.colWiseAllGather(consistent, staticDomain);
}
const prefetchTime = t.elapsed();

forall i in distDom.dim(1) {
  for j in distDom.dim(2) {
    for k in A.domain.dimIter(2, i) { // this is still a remote call
      C[i,j] += A[i,k] * B[k,j];
    }
  }
}
t.stop();

if outputData {
  matWriter(C);
  writeln();
}

writeln("Prefetch time = ", prefetchTime);
writeln("Time = ", t.elapsed());

proc matWriter(mat) {
  for i in mat.domain.dim(1) {
    for j in mat.domain.dim(2) {
      write(mat[i, j], " ");
    }
    writeln();
  }
}

// sets the global indices array
proc indexArrayHelper() {
  var n = 0;
  for i in space.dim(1) {
    for j in 1..nnzPerRow {
      indices[n] = (i, abs(rs.getNext())%N);
      n += 1;
    }
  }
}

iter SparseBlockDom.dimIter(param dim, idx) {
  var targetLocRow = dist.targetLocsIdx((idx, whole.dim(2).low));
  /*writeln("dimIter idx: ", idx, " targetLocRow ", targetLocRow);*/

  for l in dist.targetLocales.domain.dim(2) {
    for idx in locDoms[(targetLocRow[1], l)].mySparseBlock.dimIter(2, idx) {
      yield idx;
    }
  }
}

