config param flag = true;
var myRange = 1..2;

record R1 {
  var scalarData: if flag then int else real;
  var leakyData: if flag then [1..2] int else [1..2] real;
  var leakyData2: if flag then [myRange] int else [myRange] real;
  var nonLeakyData: [1..2] int;
}

proc main() {
  var x : R1;
  writeln(x);
}
