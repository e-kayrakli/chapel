use Time;
use BlockDist;
use commMethods;


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
}

proc accessPrivate() {
  var space = {0..#N};
  var arr: [space] real;
  var sum = 0.0;
  var t = new Timer();

  forall i in arr.domain do arr[i] = sin(i);

  t.start();
  for i in 0..#numToRead*stride by stride {
    sum += arr[i%N];
  }
  t.stop();

  writeln("Time = ", t.elapsed());
  writeln("Sum = ", sum);
}

proc accessLocalFast() {
  var space = {0..#2*N}; // run with two locales
  var dom = space dmapped Block(space);
  var arr: [dom] real;
  var sum = 0.0;
  var t = new Timer();

  forall i in arr.domain do arr[i] = sin(i);

  on Locales[0] {
    t.start();
    local for i in 0..#numToRead*stride by stride {
      sum += arr[i%N];
    }
    t.stop();

    writeln("Time = ", t.elapsed());
    writeln("Sum = ", sum);
  }
}

proc accessLocal() {
  var space = {0..#2*N}; // run with two locales
  var dom = space dmapped Block(space);
  var arr: [dom] real;
  var sum = 0.0;
  var t = new Timer();


  forall i in arr.domain do arr[i] = sin(i);
  on Locales[0] {
    t.start();
    for i in 0..#numToRead*stride by stride {
      sum += arr[i%N];
    }
    t.stop();

    writeln("Time = ", t.elapsed());
    writeln("Sum = ", sum);
  }
}

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
    for i in 0..#numToRead*stride by stride {
      localSum += arr[i%N];
    }
    t.stop();
    sum = localSum;
    writeln("Time = ", t.elapsed());
    writeln("Sum = ", sum);
  }
}

proc accessRemotePrefetched(consistent) {
  var space = {0..#2*N}; // run with two locales
  var dom = space dmapped Block(space);
  var arr: [dom] real;
  var sum = 0.0;

  forall i in arr.domain do arr[i] = sin(i);

  arr._value.allGather(consistent);
  on Locales[1] {
    var t = new Timer();
    /*const locNumToRead = numToRead;*/
    /*const locStride = stride;*/
    var localSum = 0.0;
    t.start();
    for i in 0..#numToRead*stride by stride {
      localSum += arr[i%N];
    }
    t.stop();
    sum = localSum;

    writeln("Time = ", t.elapsed());
    writeln("Sum = ", sum);

    /*arr._value.myLocArr.getPrefetchHook().printTimeStats();*/
  }
}
