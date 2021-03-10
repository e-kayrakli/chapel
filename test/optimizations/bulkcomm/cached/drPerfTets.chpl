use CommDiagnostics;
use Time;

config const n = 10;
config const niters = 5;

config const verboseComm = false;
config const commDiags = false;
config const timing = false;

var source: [0..#n] int;

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

  writeln(dest);
  if timing then writeln(t.elapsed());
}

