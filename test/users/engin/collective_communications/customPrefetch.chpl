use BlockDist;
use commMethods;

config const N = 10;
config const consistent = true;

const space = {0..#N};
const dom = space dmapped Block(space);

var arr: [dom] int;

forall i in dom do arr[i] = i*2;

const descTableDom = {0..#numLocales, 0..#numLocales};
var descTable: [descTableDom] domain(1);

descTable[0,1] = {8..9};
descTable[1,0] = {1..2};

arr._value.customPrefetch(consistent=false, descTable);

var sum = 0;

on Locales[0] {
  local {
    sum += arr[8];
    sum += arr[9];
  }
}

on Locales[1] {
  var localSum = 0;
  local {
    localSum += arr[1];
    localSum += arr[2];
  }
  sum += localSum;
}

writeln(sum);
