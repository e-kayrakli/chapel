#!/bin/sh

hosts=( pyramid george )

for h in "${hosts[@]}"
do
  echo Host: $h
  make cleanout
  cd out
  tar xzvf datapack_synthReprefetchPerf_$h\_512_10.tar.gz
  cd ..
  make plotslurm SIZE=100 NUMTRIES=1
  cp synthReprefetchPerf_ss.png ~/papers/prefetch_v3/plots_new/synth/synthReprefetchPerf_ss_$h.png
done
