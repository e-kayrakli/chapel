use Time;
use BlockDist;
use commMethods;
use CommDiagnostics;

config param detailedTiming=false;
config const N = 4;
config param optComm = true;
const space = {0..#N, 0..#N};
const dom = space dmapped Block(space);

var a: [dom] real;
var b: [dom] real;

forall (i,j) in dom {
  a[i,j] = sin(i*N+j);
  b[i,j] = cos(i+j);
}

/*writeln(a);*/
/*writeln(b);*/

var c: [dom] real;

startCommDiagnostics();
const t = new Timer();
const detailT = new Timer();
var commTime = 0.0;
var compTime = 0.0;

t.start();
if optComm {
  if detailedTiming then detailT.start();
  a._value.rowWiseAllGather();
  b._value.colWiseAllGather();
  if detailedTiming {
    detailT.stop();
    commTime += detailT.elapsed();
    detailT.clear();
    detailT.start();
  }
  local forall (i,j) in dom {
    for k in dom.dim(1) {
      c[i,j] += a[i,k] * b[k,j];
    }
  }
  if detailedTiming {
    detailT.stop();
    compTime += detailT.elapsed();
    detailT.clear();
  }
}
else {
  forall (i,j) in dom {
    for k in dom.dim(1) {
      c[i,j] += a[i,k] * b[k,j];
    }
  }
}
t.stop();
stopCommDiagnostics();

/*writeln(c);*/

writeln("Checksum : ", + reduce c);
writeln("N : ", N);
writeln("Time : ", t.elapsed());
if detailedTiming {
  writeln("\t CommTime : ", commTime);
  writeln("\t CompTime : ", compTime);
}

writeln(getCommDiagnostics());
