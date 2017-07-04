use Time;
use BlockDist;
use PrefetchPatterns;


config const N = 1000000;
config const stride = 1;
config const numToRead = 10000;

assert(stride*numToRead <= N);
config const accessType = 0;

// 0 : access private array
// 1 : access local part of shared array
// 2 : access local part of shared array from inside local block
// 3 : access remote part of shared array
// 4 : access prefetched part of shared array

select(accessType) {
  when 0 do accessPrivate();
  when 1 do accessLocalFast();
  when 2 do accessLocal();
  when 3 do accessRemote();
  when 4 do accessRemotePrefetched(consistent=true);
  when 5 do accessRemotePrefetched(consistent=false);
  when 6 do accessRemotePrefetched(consistent=false, isLocal=true);
}

inline proc initVal(i) {
  return i+10;
}

proc accessPrivate() {
  var space = {0..#N};
  var arr: [space] real;
  var sum = 0.0;
  var t = new Timer();

  var detailTimer_calc = new Timer();
  var detailTimer_acc = new Timer();
  //these calls are moved in the generated c code
  detailTimer_calc.start();
  detailTimer_calc.stop();
  detailTimer_acc.start();
  detailTimer_acc.stop();

  forall i in arr.domain do arr[i] = initVal(i);

  t.start();
  local for i in 0..#numToRead*stride by stride {
    sum += arr[i%N];
  }
  t.stop();

  writeln("Time = ", t.elapsed());
  writeln("Sum = ", sum);

  writeln("Detail timer calc : ", detailTimer_calc.elapsed());
  writeln("Detail timer acc : ", detailTimer_acc.elapsed());
}

proc accessLocalFast() {
  var space = {0..#2*N}; // run with two locales
  var dom = space dmapped Block(space);
  var arr: [dom] real;
  var sum = 0.0;
  var t = new Timer();

  forall i in arr.domain do arr[i] = initVal(i);

  on Locales[0] {

    var detailTimer_calc = new Timer();
    var detailTimer_acc = new Timer();
    //these calls are moved in the generated c code
    detailTimer_calc.start();
    detailTimer_calc.stop();
    detailTimer_acc.start();
    detailTimer_acc.stop();

    t.start();
    local for i in 0..#numToRead*stride by stride {
      sum += arr[i%N];
    }
    t.stop();

    writeln("Time = ", t.elapsed());
    writeln("Sum = ", sum);

    writeln("Detail timer calc : ", detailTimer_calc.elapsed());
    writeln("Detail timer acc : ", detailTimer_acc.elapsed());
  }
}

proc accessLocal() {
  var space = {0..#2*N}; // run with two locales
  var dom = space dmapped Block(space);
  var arr: [dom] real;
  var sum = 0.0;
  var t = new Timer();


  forall i in arr.domain do arr[i] = initVal(i);
  on Locales[0] {

    var detailTimer_calc = new Timer();
    var detailTimer_acc = new Timer();
    //these calls are moved in the generated c code
    detailTimer_calc.start();
    detailTimer_calc.stop();
    detailTimer_acc.start();
    detailTimer_acc.stop();

    t.start();
    for i in 0..#numToRead*stride by stride {
      sum += arr[i%N];
    }
    t.stop();

    writeln("Time = ", t.elapsed());
    writeln("Sum = ", sum);

    writeln("Detail timer calc : ", detailTimer_calc.elapsed());
    writeln("Detail timer acc : ", detailTimer_acc.elapsed());
  }
}

proc accessRemote() {
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
      localSum += arr[i%N];
    }
    t.stop();
    sum = localSum;
    writeln("Time = ", t.elapsed());
    writeln("Sum = ", sum);

    writeln("Detail timer calc : ", detailTimer_calc.elapsed());
    writeln("Detail timer acc : ", detailTimer_acc.elapsed());
  }
}

proc accessRemotePrefetched(consistent, param isLocal=false) {
  var space = {0..#2*N}; // run with two locales
  var dom = space dmapped Block(space);
  var arr: [dom] real;
  var sum = 0.0;

  forall i in arr.domain do arr[i] = initVal(i);

  arr._value.allGather(consistent);
  on Locales[1] {

    var detailTimer_calc = new Timer();
    var detailTimer_acc = new Timer();
    //these calls are moved in the generated c code
    detailTimer_calc.start();
    detailTimer_calc.stop();
    detailTimer_acc.start();
    detailTimer_acc.stop();

    var junk: real;
    if consistent then junk = arr[0]; // make sure we bring the data
    var t = new Timer();
    var localSum = 0.0;
    t.start();
    for i in 0..#numToRead*stride by stride {
      if isLocal then
        local localSum += arr[i%N];
      else
        localSum += arr[i%N];
    }
    t.stop();
    sum = localSum;

    writeln("Junk = ", junk);
    writeln("Time = ", t.elapsed());
    writeln("Sum = ", sum);

    writeln("Detail timer calc : ", detailTimer_calc.elapsed());
    writeln("Detail timer acc : ", detailTimer_acc.elapsed());
  }
}
