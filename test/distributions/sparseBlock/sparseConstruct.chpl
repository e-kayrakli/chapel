config const locIdxBufSize = -1;
config const profile = true;
use BlockDist;
use LayoutCS;
use Time;

proc constructCS(const ref rows, const ref cols, const ref vals) {
  var totalTimer, reduceTimer, initTimer, commTimer, addTimer: stopwatch;

  if profile then totalTimer.start();

  if profile then reduceTimer.start();
  const minRow = min reduce rows;
  const maxRow = max reduce rows;
  const minCol = min reduce cols;
  const maxCol = max reduce cols;
  if profile then reduceTimer.stop();


  if profile then initTimer.start();
  const Space = {minRow..maxRow, minCol..maxCol};
  const DenseDom = Space dmapped new blockDist(Space,
                                             sparseLayoutType=CS(compressRows=true));
  var SparseDom: sparse subdomain(DenseDom);
  var Arr: [SparseDom] vals.eltType;
  if profile then initTimer.stop();

  coforall (loc, locDom) in zip(SparseDom.targetLocales(),
                                SparseDom._value.locDoms) with (ref commTimer,
                                                                ref addTimer) {
    on loc {
      for _srcLocId in loc.id..#numLocales {
        const srcLocId = _srcLocId % numLocales;

        if profile && here.id == 0 then commTimer.start();
        var rowChunk = rows[rows.localSubdomain(Locales[srcLocId])];
        var colChunk = cols[rows.localSubdomain(Locales[srcLocId])];
        var valChunk = vals[rows.localSubdomain(Locales[srcLocId])];
        if profile && here.id == 0 then commTimer.stop();

        if profile && here.id == 0 then addTimer.start();
        for (r,c,v) in zip(rowChunk, colChunk, valChunk) {
          if locDom!.parentDom.contains(r,c) {
            locDom!.mySparseBlock += (r,c);
            Arr[r,c] = v;
          }
        }
        if profile && here.id == 0 then addTimer.stop();
      }
    }
  }

  if profile then totalTimer.stop();

  if profile {
    const totalT = totalTimer.elapsed();
    const reduceT = reduceTimer.elapsed();
    const initT = initTimer.elapsed();
    const commT = commTimer.elapsed();
    const addT = addTimer.elapsed();

    param timeFmt = "%20s %5.2dr ms (%%%2.1dr)\n";
    writef(timeFmt, "Reduce time:", reduceT, reduceT/totalT);
    writef(timeFmt, "Init time:", initT, initT/totalT);
    writef(timeFmt, "Comm time:", commT, commT/totalT);
    writef(timeFmt, "Add time:", addT, addT/totalT);
    writef("%20s %5.2dr ms\n", "TOTAL time:", totalT);
  }

  return Arr;
}

config const x = 100, y = x;
config const nnz = 20;
config const val = 1;

use Random;

var rows, cols, vals: [1..nnz] int;

fillRandom(rows, min=1, max=x, seed=13);
fillRandom(cols, min=1, max=x, seed=17);
vals = val;

var Arr = constructCS(rows,cols,vals);

for i in Arr.domain {
  assert(Arr[i] == 1);
}

