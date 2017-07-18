#! /bin/sh

n=$1
numToRead=$2
for type in 0 1 2;
do
  for str in 01 02 04 08 16 32 64;
  do
    echo "./bin/syntheticPutTest -nl2 --N=$n --numToRead=$numToRead --accessType=$type --stride=$str >./out/type$type.str$str.out;"
    ./bin/syntheticPutTest -nl2 --N=$n --numToRead=$numToRead --accessType=$type --stride=$str >./out/type$type.str$str.out;
  done;
done

for type in 0 1 2;
do
  for str in 01 02 04 08 16 32 64;
  do
    echo "./bin/syntheticPutTest_u -nl2 --N=$n --numToRead=$numToRead --accessType=$type --stride=$str >./out/type$((type+3)).str$str.out;r"
    ./bin/syntheticPutTest_u -nl2 --N=$n --numToRead=$numToRead --accessType=$type --stride=$str >./out/type$type.unpack.str$str.out;
  done;
done
