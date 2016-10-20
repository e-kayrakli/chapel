use Time;
use BlockDist;

config const N = 1000000;
config const numToRead = 10000;

accessRemote();

proc accessRemote() {
  var space = {0..#2*N}; // run with two locales
  var dom = space dmapped Block(space);
  var arr: [dom] real;
  var sum = 0.0;
  var t = new Timer();

  forall i in arr.domain do arr[i] = sin(i);

  on Locales[1] {
    var localSum = 0.0;
    t.start();
    for i in 0..#numToRead {
      localSum += arr[i];
    }
    t.stop();
    sum = localSum;
    writeln("Time = ", t.elapsed());
    writeln("Sum = ", sum);
  }
}

