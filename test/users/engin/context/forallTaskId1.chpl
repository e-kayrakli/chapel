config const n = 20;
config const taskPerLoc = 2;
config const doDebug = false;


proc debug(args...) {
  if doDebug then writeln((...args));
}

iter foo() {
  const iterRange = 0..<n;
  for i in iterRange do yield i;
}

/*class Context {*/
  /*var parent: unmanaged Context?;*/
  /*var name: string;*/

  /*proc init(parent: Context = nil, name:string) {*/
    /*this.parent = parent;*/
    /*this.name = name;*/
  /*}*/
/*}*/

/*class ForallContext: Context {*/
  /*proc init(parent: Context = nil, name:string) { super.init(parent, name); }*/
/*}*/
/*class CoforallContext: Context {*/
  /*proc init(parent: Context = nil, name:string) { super.init(parent, name); }*/
/*}*/
/*class OnContext: Context {*/
  /*proc init(parent: Context = nil, name:string) { super.init(parent, name); }*/
/*}*/

pragma "context type"
record Context { 

}

iter foo(param tag: iterKind) where tag==iterKind.leader {
  coforall l in Locales {
    /*var outerCtx = new unmanaged CoforallContext(nil:unmanaged Context?, "outer");*/
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

forall (i, context) in foo() {  // context should be coming from a new syntax
  // can we get this with some compiler magic?
  const localeContext = __primitive("outer context", context);

  /*
   var sharedDom = {1..10} dmapped Context(localeContext);
  */
  writeln(i);
 
}
