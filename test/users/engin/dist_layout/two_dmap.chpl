use BlockDist;
use LayoutCSR;

config const N = 100;

const D = {0..#N, 0..#N} dmapped Block({0..#N, 0..#N});

var SD: sparse subdomain(D) dmapped CSR();


