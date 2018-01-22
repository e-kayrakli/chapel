nl=$1
size=$2

./bin/fft -nl$nl --n=$size > out/aal_fft_base.out
./bin/fft_log -nl$nl --n=$size --samplingRate=1.0 > out/aal_fft_log_10.out
./bin/fft_log -nl$nl --n=$size --samplingRate=0.5 > out/aal_fft_log_05.out
./bin/fft_log -nl$nl --n=$size --samplingRate=0.1 > out/aal_fft_log_01.out
./bin/fft_log_stat -nl$nl --n=$size --samplingRate=1.0 > out/aal_fft_log_stat_10.out
./bin/fft_log_stat -nl$nl --n=$size --samplingRate=0.5 > out/aal_fft_log_stat_05.out
./bin/fft_log_stat -nl$nl --n=$size --samplingRate=0.1 > out/aal_fft_log_stat_01.out


