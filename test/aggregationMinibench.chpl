use CommAggregation;
use BlockDist;
use Random;
use Time;

config const arrSize = 1024;
config const localRatio = 0.1;
config const numIters = 10;

var dom = newBlockDom(0..#arrSize);
var A: [dom] int;
var B: [dom] int;

var r = createRandomStream(int);

proc generateIndices() {
  const localDom = dom.localSubdomain();
  const numAccesses = localDom.size;

  const numLocalAccesses = (numAccesses * localRatio):int;
  const numRemoteAccesses = numAccesses - numLocalAccesses;

  const remoteDom = {localDom.high+1..dom.high};

  var indices: [0..#numAccesses] int;

  if numLocalAccesses > 0 then
    indices[0..#numLocalAccesses] = r.choice(localDom, size=numLocalAccesses);

  if numRemoteAccesses > 0 then
    indices[numLocalAccesses..numAccesses-1] = r.choice(remoteDom, size=numRemoteAccesses);

  shuffle(indices);

  return indices;
}


on Locales[0] {
  var t = new Timer();
  var indicesToGet = generateIndices();
  for i in 0..#numIters {
    if i > 0 then t.start();
    forall i in dom.localSubdomain() {
      A[i] = B[indicesToGet[i]];
    }
    if i > 0 then t.stop();
  }
  writeln("Per access time (us): ", 1000000*t.elapsed()/(numIters-1)/dom.localSubdomain().size);
}
