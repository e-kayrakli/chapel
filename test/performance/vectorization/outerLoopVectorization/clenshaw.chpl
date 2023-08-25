use Random.NPBRandom;
use Time;

config const printTime = false;

config const n = 100000;
config const m = 40960;

var coeffs:[0..n] real;
var xs:[1..m] real;
var ys:[1..m] real;

proc init() {
  var R = new owned NPBRandomStream(seed=11);
  R.fillRandom(coeffs);
  R.fillRandom(xs);
  R.fillRandom(ys);
}

proc clenshaw() {
  var t: stopwatch;
  // for i in 1..m {
  // forall i in 1..m {
  t.start();
  @llvm.assertVectorized
  foreach i in 1..m {
    var x:real = xs[i];
    var u0:real = 0;
    var u1:real = 0;
    var u2:real = 0;
    for k in 1..n by -1 {
      u2 = u1;
      u1 = u0;
      u0 = 2*x*u1-u2+coeffs[k];
    }
    ys[i] = 0.5*(coeffs[0]+u0-u2);
  }
  t.stop();
  if printTime then writeln(t.elapsed());
}

init();
clenshaw();

var total:real = 0;
for i in 1..m {
  total += ys[i];
}
writeln(total);
