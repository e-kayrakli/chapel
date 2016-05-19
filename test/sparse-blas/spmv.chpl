use BlockDist;

config const N = 5;

//create sparse and dense domains
var D = {0..#N, 0..#N} dmapped Block({0..#N, 0..#N});
var SD: sparse subdomain(D);
var SVecD_B: sparse subdomain({0..#N});
var SVecD_C: sparse subdomain({0..#N});

//define sparse arrays

var A: [SD] int;
var b: [SVecD_B] int;
var c: [SVecD_C] int;

/*populate arrays as follows:
    0 1 4 0 0 
    6 0 0 3 0
A = 0 0 5 0 0 
    0 1 0 0 0
    0 0 0 0 7

    0
    6
b = 0
    0
    1

Result vector should be:
    6
    0
c = 0
    6
    7
*/

//add indices to domains
var Aindices = [(0,1), (0,2), (1,0), (1,3), (2,2), (3,1), (4,4)];
var Avals = [1, 4, 6, 3, 5, 1, 7];

var bindices = [1, 4];
var bvals = [6, 1];

for (idx,val) in zip(Aindices, Avals) {
  SD_A += idx;
  A[idx] = val;
}

for (idx,val) in zip(Bindices, Bvals) {
  SD_B += idx;
  B[idx] = val;
}

//spmv
for r in A.rows() { //assuming rows is a sparse-aware iterator that yields row
                    //indices
  SVecD_C += r; //or (r, ) ?
  c[r] = + reduce A[r, ..]*b;
}

