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

Result matrix should be:
    0 3 4 0 4
    7 1 3 3 0
C = 0 0 5 2 0
    0 2 0 0 1 
    1 0 0 0 7
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

//these for loops could be in previous two loops, but this seemed closer to what
//you might see in real-world applications
for idx in Aindices do SD_C += idx;
for idx in Bindices do SD_C += idx;

C = A + B; //it would be great if we can do this directly
