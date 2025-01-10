use CopyAggregation;
use CTypes;
use BlockDist;

config const idxBufSize = 10;

class DestHandler {
  var locIdxBuf: SparseIndexBuffer(?);

  proc init(DVal) {
    this.locIdxBuf = DVal.locDoms[DVal.dist.targetLocsIdx(here.id)]!.mySparseBlock.createIndexBuffer(idxBufSize);
    writeln(here, " DestHandler.init ", DVal.myLocDom.locale);
  }

  inline proc handle(dstAddr: c_ptr(?t), srcVal: t) {
    assert(dstAddr == nil);
    this.locIdxBuf.add(srcVal);
  }

  proc ref deinit() {
    this.locIdxBuf.commit();
  }

}
class AggregatedAddHandler {
  var domVal;
  /*var locImplDomVal: LocSparseBlockDom(?);*/
  /*var locIdxBuf: SparseIndexBuffer(rank=domVal.rank,*/
                                   /*domVal.myLocDom!.mySparseBlock._value.type,*/
                                   /*domVal.idxType);*/
  /*var locIdxBuf: SparseIndexBuffer(?);*/
  type elemType;
  /*type destHandlerType;*/

  proc init(D) {
    this.domVal = D._value;
    if D.rank == 1 then
      this.elemType = D.idxType;
    else
      this.elemType = D.rank*D.idxType;
    /*this.destHandlerType = DestHandler(D._value.myLocDom!.mySparseBlock.createIndexBuffer(0).type);*/
    /*this.locIdxBuf = D._value.myLocDom!.mySparseBlock.createIndexBuffer(0);*/
    /*this.locImplDomVal = D._value.myLocDom;*/
  }

  proc sourceCopy() {
    return new unmanaged DestHandler(this.domVal);
  }

  /*proc init=(other: AggregatedAddHandler(?)) {*/
    /*this.domVal = other.domVal;*/
    /*this.locIdxBuf = this.domVal.myLocDom!.mySparseBlock.createIndexBuffer(idxBufSize);*/
    /*this.elemType = other.elemType;*/

    /*init this;*/

    /*writeln("AggregatedAddHandler copied on ", here, " PTR: ", c_ptrTo(this));*/
  /*}*/

  /*inline proc ref handle(dstAddr: c_ptr(elemType), srcVal: elemType) {*/
    /*assert(dstAddr == nil);*/
    /*this.locIdxBuf.add(srcVal);*/
  /*}*/

  /*proc ref deinit() {*/
    /*this.locIdxBuf.commit();*/
  /*}*/

  proc destLocale(val: elemType) {
    writeln(val, " ", domVal.dist.dsiIndexToLocale(val));

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

/*writeln(LocalArr);*/
