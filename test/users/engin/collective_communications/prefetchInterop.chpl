use BlockDist;
use Time;

config const N = 100;
config const prefetch = true;
config const detailedTime = false;
const space = {0..#N};
const dom = space dmapped Block(space);
var arr: [dom] real;
/*forall a in arr do a = a.locale.id*5;*/
forall i in dom do arr[i] = sin(i);


var t = new Timer();
var detailT = new Timer();
var sum = 0.0;
t.start();
if prefetch {
  if detailedTime then detailT.start();
  var handle=chpl_comm_prefetch(node=1,c_ptrTo(arr[N/2]), (N/2)*8, 
      getSerializedIdx(N/2));
  if detailedTime {
    detailT.stop();
    writeln("Prefetch : ", detailT.elapsed());
    detailT.clear();
    detailT.start();
  }
  var data: arr._value.eltType;
  local for i in space {
    var isFound=get_prefetched_data(handle,8,getSerializedIdx(i), data);
    if isFound >= 0 {
      /*get_prefetched_data(handle, result, 8, data);*/
      sum+=data;
    }
    else {
      sum+=arr[i];
    }
  }
  if detailedTime {
    detailT.stop();
    writeln("Comp :", detailT.elapsed());
    detailT.clear();
  }
}
else {
  for i in space do sum += arr[i];
}
t.stop();
writeln(t.elapsed());
writeln(sum);


// TODO this will be one of the serialization helper
inline proc getSerializedIdx(idx) {
  return idx*8;
}
