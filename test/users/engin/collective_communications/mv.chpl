use Time;
use BlockDist;
use commMethods;
use CommDiagnostics;

config param detailedTiming=false;
config param optComm = false;
config param commDiag = false;
config param verboseComm = false;
config param rtPrefetch = false;
config const N = 4;
config const printData = false;
config const printDataAfterPrefetch = false;
config param partial = false;
const space = {0..#N, 0..#N};
const matdom = space dmapped Block(space);
const vecspace = {0..#N};
const vecdom = vecspace dmapped Block(vecspace);

var A: [matdom] real;
var b: [vecdom] real;

forall (i,j) in matdom {
  A[i,j] = sin(i*N+j);
}
forall i in vecdom {
  b[i] = cos(i);
}

if printData {
  /*for i in matdom do writeln(A[i]);*/
  /*for i in vecdom do writeln(b[i]);*/
  writeln(A);
  writeln(b);
}

var c: [vecdom] real;

if commDiag then startCommDiagnostics();

const t = new Timer();
const detailT = new Timer();
var commTime = 0.0;
var compTime = 0.0;

t.start();
if optComm {
  if detailedTiming then detailT.start();
  /*if partial then A._value.rowWiseAllPartialGather();*/
              /*else A._value.rowWiseAllGather();*/
  A._value.rowWiseAllGather();
  b._value.allGather();
  if printDataAfterPrefetch{
    directWriteA();
    directWriteB();
  }
  /*halt("All gather was successful");*/
  if detailedTiming {
    detailT.stop();
    commTime += detailT.elapsed();
    detailT.clear();
    detailT.start();
  }
  forall i in vecdom {
    for k in vecdom {
      c[i] += A[i,k] * b[k];
      /*c[i] += b[k];*/
    }
  }
  if detailedTiming {
    detailT.stop();
    compTime += detailT.elapsed();
    detailT.clear();
  }
}
else {
  forall i in vecdom {
    for k in vecdom {
      c[i] += A[i,k] * b[k];
    }
  }
}
t.stop();
if commDiag then stopCommDiagnostics();

if printData || printDataAfterPrefetch {
  writeln(c);
}

inline proc directWriteA() {
  for l in Locales do on l {
    writeln("On ", here);
    for i in A.domain.dim(1) {
      for j in A.domain.dim(2) {
        write(A[i,j], " ");
      }
      writeln();
    }
  }
}

inline proc directWriteB(){
  for l in Locales do on l {
    for i in b.domain {
      write(b[i], " ");
    }
    writeln();
  }
}


writeln("Checksum : ", + reduce c);
writeln("N : ", N);
writeln("Time : ", t.elapsed());
if detailedTiming {
  writeln("\t CommTime : ", commTime);
  writeln("\t CompTime : ", compTime);
}

if commDiag then writeln(getCommDiagnostics());

