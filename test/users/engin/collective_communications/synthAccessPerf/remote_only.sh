#! /bin/sh

n=$1
numToRead=$2
suffix=`echo $CHPL_HOME | grep fork_dev -c`
type=3
for str in 01 02 04 08 16 32 64;
do
  echo "./bin/syntheticPerfTest -nl2 --N=$n --numToRead=$numToRead --accessType=$type --stride=$str >./out/remote_only.$suffix.type$type.str$str.out;"
  ./bin/syntheticPerfTest -nl2 --N=$n --numToRead=$numToRead --accessType=$type --stride=$str >./out/remote_only.$suffix.type$type.str$str.out;
done;
