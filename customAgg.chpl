use CopyAggregation;
use CTypes;
use BlockDist;

config const idxBufSize = 10;

class DestHandler {
  var locIdxBuf: SparseIndexBuffer(?);

  proc init(DVal) {
    this.locIdxBuf = DVal.locDoms[DVal.dist.targetLocsIdx(here.id)]!.mySparseBlock.createIndexBuffer(idxBufSize);
  }

  inline proc handle(dstAddr: c_ptr(?t), srcVal: t) {
    assert(dstAddr == nil);
    this.locIdxBuf.add(srcVal);
  }

  proc deinit() {
    this.locIdxBuf.commit();
  }
}

class AggregatedAddHandler {
  var domVal;
  type elemType;

  proc init(D) {
    this.domVal = D._value;
    if D.rank == 1 then
      this.elemType = D.idxType;
    else
      this.elemType = D.rank*D.idxType;
  }

  proc sourceCopy() {
    return new unmanaged DestHandler(this.domVal);
  }

  proc destLocale(val: elemType) {
    return domVal.dist.dsiIndexToLocale(val);
  }
}

config const nnz = 50;
config const n = 5000;

const Space = {1..n};
const DenseDom = Space dmapped new blockDist(Space);
const SparseDom: sparse subdomain(DenseDom);

var IndexArr = blockDist.createArray(1..nnz, int);
assert(nnz*10 < n);
forall i in IndexArr.domain {
  IndexArr[i] = i*10;
}

forall elem in IndexArr
    with (var agg = new DstAggregator(new shared AggregatedAddHandler(SparseDom))) {

  agg.copy(elem);
}


writeln(SparseDom.size);
