#! /bin/sh

for type in 0 1 2;
do
  echo
  echo TYPE$type
  echo --------------------
  grep Time out/type$type.str* | cut -d" " -f3
done

for type in 0 1 2;
do
  echo
  echo TYPE$type.unpack
  echo --------------------
  grep Time out/type$type.unpack.str* | cut -d" " -f3
done
