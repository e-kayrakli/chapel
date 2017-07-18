use Time;
use BlockDist;
use PrefetchPatterns;

config const N = 1000000;
config const stride = 1;
config const numToRead = 10000;

assert(stride*numToRead <= N);
config const accessType = 0;

// 0 : write to remote part
// 1 : write to prefetched remote part (consistent)
// 2 : write to prefethced remote part (inconsistent)

select(accessType) {
  when 0 do writeRemote();
  when 1 do writeRemote(prefetch=true);
  when 2 do writeRemote(prefetch=true, consistent=false);
}

inline proc initVal(i) {
  return i+10;
}

inline proc finalVal(i) {
  return i+20;
}

proc writeRemote(param prefetch=false, param consistent=true) {
  var space = {0..#2*N}; // run with two locales
  var dom = space dmapped Block(space);
  var arr: [dom] real;
  var sum = 0.0;
  var t = new Timer();

  forall i in arr.domain do arr[i] = initVal(i);

  on Locales[1] {

    var detailTimer_calc = new Timer();
    var detailTimer_acc = new Timer();
    //these calls are moved in the generated c code
    detailTimer_calc.start();
    detailTimer_calc.stop();
    detailTimer_acc.start();
    detailTimer_acc.stop();

    var localSum = 0.0;
    t.start();
    for i in 0..#numToRead*stride by stride {
      arr[i%N] = finalVal(i);
    }
    t.stop();
    sum = localSum;
    writeln("Time = ", t.elapsed());
    writeln("Sum = ", sum);

    writeln("Detail timer calc : ", detailTimer_calc.elapsed());
    writeln("Detail timer acc : ", detailTimer_acc.elapsed());
  }
}
