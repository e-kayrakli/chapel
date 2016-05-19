use BlockDist;

config const N = 10;

//create sparse and dense domains
var D = {0..#N, 0..#N} dmapped Block({0..#N, 0..#N});

//A and B matrices are of same size, but they should have separate sparse
//domains
var SD_A: sparse subdomain(D);
var SD_B: sparse subdomain(D);
var SD_C: sparse subdomain(D);
//define sparse arrays

//ideally, they can be on different sparse/dense domains? or do we care?
var A: [SD_A] int;
var B: [SD_B] int;

/*populate matrices as follows:
    0 1 4 0 0 
    6 0 0 3 0
A = 0 0 5 0 0 
    0 1 0 0 0
    0 0 0 0 7

    0 2 0 0 4
    1 1 3 0 0
B = 0 0 0 2 0
    0 1 0 0 1
    1 0 0 0 0 

Result matrix should be (done by hand, don't trust):
    1 1  0 8 0 
    0 12 0 0 17   
C = 0 0 0 10 0
    1 1 3 0 0 
    7 0 0 0 0
*/

//add indices to domains
var Aindices = [(0,1), (0,2), (1,0), (1,3), (2,2), (3,1), (4,4)];
var Avals = [1, 4, 6, 3, 5, 1, 7];

var Bindices = [(0,1), (0,4), (1,0), (1,1), (1,2), (2,3), (3,1), (3,4), (4,0)];
var Bvals = [2, 4, 1, 2, 3, 2, 1, 1, 1];

for (idx,val) in zip(Aindices, Avals) {
  SD_A += idx;
  A[idx] = val;
}

for (idx,val) in zip(Bindices, Bvals) {
  SD_B += idx;
  B[idx] = val;
}

for r in A.rows() {
  for c in A.dimIter(2, r) { // we already have a similar dimIter function
    SD_C += (r,c);
    C[r,c] = + reduce A[r, ..] * B[.., c];
  }
}

