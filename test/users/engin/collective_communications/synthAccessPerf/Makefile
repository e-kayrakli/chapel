FLAGS=--fast --cache-remote
MISCFLAGS=

MAIN=syntheticPerfTest

all: syntheticPerfTest syntheticPerfTest_u
$(MAIN): $(MAIN).chpl
	chpl $(FLAGS) $(MISCFLAGS) -o ./bin/$@ $^
$(MAIN)_u: $(MAIN).chpl
	chpl $(FLAGS) -sallowPrefetchUnpacking=true $(MISCFLAGS) -o ./bin/$@ $^

cleanout:
	rm -f ./out/*.out

clean:
	rm -f ./bin/$(MAIN)*
