use BlockDist;

config const N = 10;
const space = {0..#N, 0..#N};
var parentDom = space dmapped Block(space);

var sparseDom: sparse subdomain(parentDom);

var sparseArr: [sparseDom] int;

for i in space {
  sparseDom += i;
}

for i in sparseDom {
  sparseArr[i] = i[1]*10;
}


for l in parentDom._value.dist.targetLocDom {
  on parentDom._value.dist.targetLocales[l] {
    writeln(here);
    for v in sparseArr._value.locArr[l].dsiSerialize() {
      const size = v[2]/8;
      var start = v[1]:c_ptr(int);
      for i in 0..#size {
        write(start[i], " ");
      }
      writeln();
    }
  }
}
