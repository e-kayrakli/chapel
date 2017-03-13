config const N = 10;
config const consistent = true;

use commMethods;

var space = {0..#N, 0..#N};

var dom = space dmapped Block(space, sparseLayoutType=DefaultDist);
var sparseDom: sparse subdomain(dom);

var sparseArr: [sparseDom] int;

for i in space {
  sparseDom += i;
}

forall i in sparseDom do sparseArr[i] = here.id + 1;

sparseArr._value.allGather(consistent);

for l in Locales do on l {
  writeln(here);
  for i in 0..#N {
    for j in 0..#N {
      write(sparseArr[i,j], " ");
    }
    writeln();
  }
  writeln();
}
/*on Locales[0] {*/
  /*writeln(here);*/
  /*for i in 0..#N do write(sparseArr[i], " ");*/
  /*writeln();*/
/*}*/
