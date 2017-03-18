use BlockDist;
use commMethods;

config type dataType = 3*int;

var space = {0..9};
var dom = space dmapped Block(space);

var arr: [dom] dataType;

forall i in dom do arr[i] = (i+10, i+15, i+20);

arr._value.allGather(consistent=false);

on Locales[0] {
  local for i in space do writeln(arr[i]);
}
