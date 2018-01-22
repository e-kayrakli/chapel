CHPL=chpl
CHPLFLAGS=--fast --ieee-float

all: fft fft_log fft_log_stat

fft: fft.chpl
	$(CHPL) $(CHPLFLAGS) -o ./bin/$@ $^

fft_log: fft.chpl
	$(CHPL) $(CHPLFLAGS) -senableAccessLogs=true -o ./bin/$@ $^

fft_log_stat: fft.chpl
	$(CHPL) $(CHPLFLAGS) -senableAccessLogs=true -o ./bin/$@ $^ --ccflags -DGENERATE_COMPRESSION_STATS

cleanout:
	rm -f {err,out}/fft*

clean:
	rm -f {bin,err,out}/fft* 

