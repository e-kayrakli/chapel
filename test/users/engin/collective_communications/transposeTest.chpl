use BlockDist;
use commMethods;

config const N = 10;
const space = {0..#N, 0..#N};
const dom = space dmapped Block(space);

var arr: [dom] int;

arr._value.rowWiseAllGatherTranspose();
