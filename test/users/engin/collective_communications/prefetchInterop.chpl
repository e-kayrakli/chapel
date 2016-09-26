extern type prefetch_entry_t;
extern type c_nodeid_t;

extern proc chpl_comm_prefetch(node, raddr, size): prefetch_entry_t;
extern proc is_prefetched(node, raddr, size): c_int;
extern proc is_prefetched_in_entry(handle, node, raddr, size): c_int;
extern proc get_data_offset(handle, node, raddr, size): c_int;
extern proc get_prefetched_data(handle, offset, size, ref dest);

use BlockDist;
use Time;

config const N = 100;
config const prefetch = true;
const space = {0..#N};
const dom = space dmapped Block(space);
var arr: [dom] int;
forall a in arr do a = a.locale.id*5;


var t = new Timer();
var sum = 0;
t.start();
if prefetch {
  var handle=chpl_comm_prefetch(arr[N/2].locale.id,c_ptrTo(arr[N/2]),
      (N/2)*8);
  for i in space {
    var result = get_data_offset(handle, arr[i].locale.id,
        c_ptrTo(arr[i]), 8);

    var data: arr._value.eltType;
    local { // given that I know everythin is prefetched
      if result >= 0{
        get_prefetched_data(handle, result, 8, data);
        sum+=data;
      }
      else {
        sum+=arr[i];
      }
    }
  }
}
else {
  for i in space do sum += arr[i];
}
t.stop();
writeln(t.elapsed());
writeln(sum);
