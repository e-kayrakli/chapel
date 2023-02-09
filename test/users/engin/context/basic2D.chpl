use BlockDist;
use ChapelContextSupport;

use Iterators.TertiaryDRDomIterators;

config const n = 8;


var dom = newBlockDom(0..<n, 0..<n);
var arr: [dom] int;

type ctx1 = Context(1, int(64));
type ctx2 = Context(2, (int(64), int(64)));

forall (idx, context) in dom.customThese() {
  const localTaskContext = __primitive("outer context", ctx1, context);
  const localeContext = __primitive("outer context", ctx2, localTaskContext);

  writeln(here, " ", idx, ": ", localTaskContext, " ", localeContext);
}
