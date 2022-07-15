use GPUDiagnostics;

startGPUDiagnostics();
on here.gpus[0] {
  var A: [0..10] int;

  foreach a in A do
    a = foo();

  writeln("A ", A);
}

var B: [0..10] int;
foreach b in B do
  b = foo();

writeln("B ", B);
stopGPUDiagnostics();

assert(getGPUDiagnostics()[0].kernel_launch == 1);


proc foo() {
  return 1;
}

pragma "codegen for GPU"
pragma "last resort"
pragma "always resolve function"
export proc foo() {
  return 2;
}
