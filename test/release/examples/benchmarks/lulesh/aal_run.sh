nl=$1
size=$2

./bin/lulesh --maxcycles=1 -nl$nl --elemsPerEdge=$size > out/aal_lulesh_base.out
./bin/lulesh_log --maxcycles=1 -nl$nl --elemsPerEdge=$size --samplingRate=1.0 > out/aal_lulesh_log_10.out
./bin/lulesh_log --maxcycles=1 -nl$nl --elemsPerEdge=$size --samplingRate=0.5 > out/aal_lulesh_log_05.out
./bin/lulesh_log --maxcycles=1 -nl$nl --elemsPerEdge=$size --samplingRate=0.1 > out/aal_lulesh_log_01.out
./bin/lulesh_log_stat --maxcycles=1 -nl$nl --elemsPerEdge=$size --samplingRate=1.0 > out/aal_lulesh_log_stat_10.out
./bin/lulesh_log_stat --maxcycles=1 -nl$nl --elemsPerEdge=$size --samplingRate=0.5 > out/aal_lulesh_log_stat_05.out
./bin/lulesh_log_stat --maxcycles=1 -nl$nl --elemsPerEdge=$size --samplingRate=0.1 > out/aal_lulesh_log_stat_01.out


