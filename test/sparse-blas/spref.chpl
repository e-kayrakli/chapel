use BlockDist;

config const N = 10;

//create sparse and dense domains
var D = {0..#N, 0..#N} dmapped Block({0..#N, 0..#N});
var SD: sparse subdomain(D);

//define sparse arrays

//ideally, they can be on different sparse/dense domains? or do we care?
var A: [SD] int;
var B: [SD] int;

//add indices to sparse domain

//can we avoid explicitly adding indices to sparse domains?
SD += (2,1);
SD += (4,3);
SD += (6,5);

//add values to the array A
A[2,1] = 10;
A[4,3] = 20;
A[6,5] = 30;

//SpRef:
var refRow = 2;
var refCol = 5;

B = A[refRow, ..];
//B should have 10 only
B = A[.., refCol];
//B should have 30 only

//one more step that can be taken is to have refRow and refCol vector of indices
var refRowV = [2, 6];
var refColV = [1, 5];

B = A[refRowV, ..];
B = A[.., refColV];
//after both refs B should hav 10,30
