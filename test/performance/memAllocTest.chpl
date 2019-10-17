use Time;

config const numBytes = 1;
config const numIterations = 10;

var t = new Timer();
var allocTime: real;
var freeTime: real;

writef("%4s\t%10s\t%10s\n", "iter", "alloc (us)", "free (us)");

for i in 1..numIterations {
  t.start();
  var c = c_calloc(uint(8), numBytes);
  t.stop();

  allocTime = t.elapsed()*1000000;
  t.clear();

  t.start();
  c_free(c);
  t.stop();

  freeTime = t.elapsed()*1000000;
  t.clear();

  writef("%4i\t%10r\t%10r\n", i, allocTime, freeTime);
}

