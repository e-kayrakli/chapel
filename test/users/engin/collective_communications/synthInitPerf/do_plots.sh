#!/bin/sh

hosts=( pyramid george )

for h in "${hosts[@]}"
do
  echo Host: $h
  make cleanout
  cd out
  tar xzvf datapack_synthInitPerf_$h\_2048_1.tar.gz
  cd ..
  make plotslurm SIZE=2048 NUMTRIES=1
  cp synthInitPerf_ss.png ~/papers/prefetch_v3/plots_new/synth/synthInitPerf_ss_$h.png
  cp synthInitPerf_ss.eps ~/papers/prefetch_v3/plots_new/synth/synthInitPerf_ss_$h.eps
  make plotslurm SIZE=2048 NUMTRIES=1 PYFLAGS=--no_legend
  cp synthInitPerf_ss.png ~/papers/prefetch_v3/plots_new/synth/synthInitPerf_ss_noleg_$h.png
  cp synthInitPerf_ss.eps ~/papers/prefetch_v3/plots_new/synth/synthInitPerf_ss_noleg_$h.eps
done
