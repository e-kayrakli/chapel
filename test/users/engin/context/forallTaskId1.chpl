use Memory.Diagnostics;

config param hoistArray = true;

config const n = 20;
config const taskPerLoc = 2;
config const doDebug = false;
config const doVerboseMem = true;

proc debug(args...) {
  if doDebug then writeln((...args));
}

iter foo() {
  const iterRange = 0..<n;
  for i in iterRange do yield i;
}

pragma "context type"
record Context {

}

iter foo(param tag: iterKind) where tag==iterKind.leader {
  coforall l in Locales {
    var outerCtx = new Context();

    on l {
      var onCtx = new Context();
      const perLocSize = n/numLocales;
      const localeLow = l.id * perLocSize;
      const localeHigh = localeLow+perLocSize-1;

      debug(here, " ", localeLow, " " , localeHigh);

      coforall taskId in 0..<taskPerLoc {
        var innerCtx = new Context();

        const perTaskSize = perLocSize/taskPerLoc;
        const taskLow = localeLow+(taskId*perTaskSize);
        const taskHigh = taskLow+perTaskSize-1;

        debug(here, ":", taskId, " ", taskLow, " " , taskHigh);

        yield (taskLow..taskHigh, innerCtx);
      }
    }
  }
}

iter foo(param tag: iterKind, followThis) where tag==iterKind.follower {
  for i in followThis[0] do yield (i, followThis[1]);
}

if doVerboseMem then startVerboseMem();
forall (i, context) in foo() {  // context should be coming from a new syntax
  const localTaskContext = __primitive("outer context", context);
  const localeContext = __primitive("outer context", localTaskContext);
  const preLocaleTaskContext = __primitive("outer context", localeContext);

  var a: [0..<n] int;
  if hoistArray then // needs to be param-folded
    __primitive("hoist array to context", localeContext, a);

  writeln(a[i]);
}
if doVerboseMem then stopVerboseMem();
