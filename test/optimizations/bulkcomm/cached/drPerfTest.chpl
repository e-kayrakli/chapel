use CommDiagnostics;
use Time;

type eltType = int(8);

config const arrSize = 10;   // in bytes
config const iterPerPeriod = 1000;

config const verboseComm = false;
config const printResult = false;

config param useGet = true;

config param verify = false;

config const timeLimit = 5;   // seconds

writeln("Will run for at least ", timeLimit, " seconds");
writeln("Array size in bytes: ", arrSize*numBytes(eltType));

var arrOnLoc0: [0..#arrSize] eltType;
forall (s,i) in zip(arrOnLoc0, arrOnLoc0.domain) do s=(i+10):eltType;

on Locales[1] {
  var arrOnLoc1: [0..#arrSize] eltType;
  var t = new Timer();

  var numPeriods = 0;

  if useGet {
    if verboseComm then startVerboseCommHere();
    t.start();

    do {
      for i in 0..#iterPerPeriod {
        arrOnLoc1 = arrOnLoc0;

        if verify {
          if verboseComm then stopVerboseCommHere();
          doVerify(arrOnLoc0, arrOnLoc1);
          arrOnLoc1 = 0;
          if verboseComm then startVerboseCommHere();
        }
      }

      numPeriods += 1;
    } while (t.elapsed() < timeLimit);

    if verboseComm then stopVerboseCommHere();
    t.stop();
  }
  else {
    arrOnLoc0 = 0:eltType;
    forall (s,i) in zip(arrOnLoc1, arrOnLoc1.domain) do s=(i+10):eltType;

    if verboseComm then startVerboseCommHere();
    t.start();

    do {
      for i in 0..#iterPerPeriod {
        arrOnLoc0 = arrOnLoc1;

        if verify {
          if verboseComm then stopVerboseCommHere();
          doVerify(arrOnLoc0, arrOnLoc1);
          arrOnLoc0 = 0;
          if verboseComm then startVerboseCommHere();
        }
      }

      numPeriods += 1;
    } while (t.elapsed() < timeLimit);

    if verboseComm then stopVerboseCommHere();
    t.stop();
  }

  if printResult then writeln(arrOnLoc1);

  const arraysCopied = numPeriods*iterPerPeriod;

  writeln("Total time: ", t.elapsed(), " seconds");
  writeln("Per-array time: ", t.elapsed()/arraysCopied*1000000, " microseconds");
}


proc doVerify(arr1, arr2) {
  var success = true;
  for (s,d) in zip(arr1, arr2) {
    if s != d then {
      writeln("Mismatch");
      writeln(arr1);
      writeln(arr2);
      success  = false;
    }
  }

  if success then writeln("Success");
}

