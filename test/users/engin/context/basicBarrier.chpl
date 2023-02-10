use IO;
use Barriers;
use Memory.Diagnostics;

use Iterators.SimpleOneDim;

config param hoistArray = true;

config const n = 20;
config const doVerboseMem = true;

if doVerboseMem then startVerboseMem();
forall (i, context) in simpleOneDim(n) {  // context should be coming from a new syntax
  const localTaskContext = __primitive("outer context", context);
  const localeContext = __primitive("outer context", localTaskContext);
  const preLocaleTaskContext = __primitive("outer context", localeContext);

  var a: [0..<n] int;
  __primitive("hoist to context", localeContext, a);

  var b;
  { // AST is too complicated without this block
    b = new Barrier(1);
    b.multiply(1);
  }
  __primitive("hoist to context", localeContext, b);

  b.barrier();

  if localTaskContext.taskId == 0 then
    a[i] = i%10;

  b.barrier();

  if localTaskContext.taskId == 1 then
    writeln("%2i: ".format(i), a);
}

if doVerboseMem then stopVerboseMem();
