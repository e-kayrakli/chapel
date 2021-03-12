use CommDiagnostics;
use Time;

config const n = 10;
config const niters = 5;

config const verboseComm = false;
config const commDiags = false;
config const timing = false;
config const printResult = false;

var source: [0..#n] int;
forall (s,i) in zip(source, source.domain) do s=i+10;

on Locales[1] {
  var dest: [0..#n] int;
  var t = new Timer();
  if verboseComm then startVerboseCommHere();
  if timing then t.start();
  for i in 0..#niters {
    dest = source;
  }
  if verboseComm then stopVerboseCommHere();
  if timing then t.stop();

  if printResult then writeln(dest);
  if timing then writeln(t.elapsed());

  var success = true;
  for (s,d) in zip(source, dest) {
    if s != d then {
      writeln("Mismatch");
      writeln(dest);
      success  = false;
    }
  }

  if success then writeln("Success");
}


