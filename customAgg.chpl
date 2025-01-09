use CopyAggregation;
use CTypes;
use BlockDist;

record testAggHandler {
  type elemType;

  proc init(type elemType) {
    this.elemType = elemType;
    writeln("testAggHandler.init called");
  }

  proc init=(other: testAggHandler(?)) {
    this.elemType = other.elemType;
    writeln("testAggHandler.init= called");
  }

  inline proc handle(dstAddr: c_ptr(elemType), srcVal: elemType) {
    writeln("testAggHandler.handle called");
    dstAddr.deref() = 2*srcVal;
  }
}

const Space = {1..10};

var DistArr = blockDist.createArray(Space, int);
var LocalArr: [Space] int;

DistArr = 1;




forall i in DistArr.domain
    with (var agg = new DstAggregator(int, new testAggHandler(int))) {
  /*LocalArr[i] = DistArr[i];*/
  agg.copy(LocalArr[i], DistArr[i]);
}

writeln(LocalArr);
