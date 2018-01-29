CHPL=chpl
CHPLFLAGS=--fast 

all: ptrans ptrans_log ptrans_log_stat

ptrans: ptrans.chpl
	$(CHPL) $(CHPLFLAGS) -o ./bin/$@ $^

ptrans_log: ptrans.chpl
	$(CHPL) $(CHPLFLAGS) -senableAccessLogs=true -o ./bin/$@ $^

ptrans_log_stat: ptrans.chpl
	$(CHPL) $(CHPLFLAGS) -senableAccessLogs=true -o ./bin/$@ $^ --ccflags -DGENERATE_COMPRESSION_STATS

cleanout:
	rm -f {err,out}/ptrans*

clean:
	rm -f {bin,err,out}/ptrans* 

