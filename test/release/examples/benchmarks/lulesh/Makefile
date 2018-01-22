CHPL=chpl
CHPLFLAGS=--fast -suseSparseMaterials=false

all: lulesh lulesh_log lulesh_log_stat

lulesh: lulesh.chpl
	$(CHPL) $(CHPLFLAGS) -o ./bin/$@ $^

lulesh_log: lulesh.chpl
	$(CHPL) $(CHPLFLAGS) -senableAccessLogs=true -o ./bin/$@ $^

lulesh_log_stat: lulesh.chpl
	$(CHPL) $(CHPLFLAGS) -senableAccessLogs=true -o ./bin/$@ $^ --ccflags -DGENERATE_COMPRESSION_STATS

cleanout:
	rm -f {err,out}/lulesh*

clean:
	rm -f {bin,err,out}/lulesh* 

