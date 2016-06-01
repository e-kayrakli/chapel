use LayoutCSR;

config param N = 100;

var PD = {0..#N, 0..#N};
var SD: sparse subdomain(PD) dmapped new dmap(new CSR());


for i in 2..98 {
  SD += (i, i);
  SD += (i, i+1);
}

for row in {0..#N}  {
  forall i in SD.dimIter(2,row) do write(i, " ");
  writeln();
}
