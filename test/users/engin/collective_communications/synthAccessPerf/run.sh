#! /bin/sh

n=$1
numToRead=$2
for type in 0 1 2 3 4 5 6;
do
  for str in 01 02 04 08 16 32 64;
  do
    echo "./bin/syntheticPerfTest -nl2 --N=$n --numToRead=$numToRead --accessType=$type --stride=$str >./out/type$type.str$str.out;"
    ./bin/syntheticPerfTest -nl2 --N=$n --numToRead=$numToRead --accessType=$type --stride=$str >./out/type$type.str$str.out;
  done;
done

for type in 4 5 6;
do
  for str in 01 02 04 08 16 32 64;
  do
    echo "./bin/syntheticPerfTest_u -nl2 --N=$n --numToRead=$numToRead --accessType=$type --stride=$str >./out/type$((type+3)).str$str.out;r"
    ./bin/syntheticPerfTest_u -nl2 --N=$n --numToRead=$numToRead --accessType=$type --stride=$str >./out/type$((type+3)).str$str.out;
  done;
done
