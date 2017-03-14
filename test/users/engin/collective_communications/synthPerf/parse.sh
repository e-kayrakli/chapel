#! /bin/sh

for type in 0 1 2 3 4 5 6 7 8 9;
do
  echo
  echo TYPE$type
  echo --------------------
  grep Time out/type$type* | cut -d" " -f3
done
