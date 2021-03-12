use CommDiagnostics;
use Time;

config const n = 10;
config const niters = 5;

config const verboseComm = false;
config const commDiags = false;
config const timing = false;
config const printResult = false;

config const lhsRemote = false;
config const rhsRemote = true;

config const verify = false;

var arrOnLoc0: [0..#n] int;
forall (s,i) in zip(arrOnLoc0, arrOnLoc0.domain) do s=i+10;

on Locales[1] {
  var arrOnLoc1: [0..#n] int;
  var t = new Timer();

  if !lhsRemote && rhsRemote {
    if verboseComm then startVerboseCommHere();
    if timing then t.start();
    for i in 0..#niters {
      arrOnLoc1 = arrOnLoc0;
      if verify {
        if verboseComm then stopVerboseCommHere();
        doVerify(arrOnLoc0, arrOnLoc1);
        arrOnLoc1 = 0;
        if verboseComm then startVerboseCommHere();
      }
    }
    if verboseComm then stopVerboseCommHere();
    if timing then t.stop();
  }
  else if lhsRemote && !rhsRemote {
    arrOnLoc0 = 0;
    forall (s,i) in zip(arrOnLoc1, arrOnLoc1.domain) do s=i+10;

    if verboseComm then startVerboseCommHere();
    if timing then t.start();
    for i in 0..#niters {
      arrOnLoc0 = arrOnLoc1;
      if verify {
        if verboseComm then stopVerboseCommHere();
        doVerify(arrOnLoc0, arrOnLoc1);
        arrOnLoc0 = 0;
        if verboseComm then startVerboseCommHere();
      }
    }
    if verboseComm then stopVerboseCommHere();
    if timing then t.stop();
  }



  if printResult then writeln(arrOnLoc1);
  if timing then writeln(t.elapsed());

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

