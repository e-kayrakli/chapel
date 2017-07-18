FLAGS=--fast --cache-remote
MISCFLAGS=

MAIN=syntheticPutTest

all: syntheticPutTest syntheticPutTest_u
$(MAIN): $(MAIN).chpl
	chpl $(FLAGS) $(MISCFLAGS) -o ./bin/$@ $^
$(MAIN)_u: $(MAIN).chpl
	chpl $(FLAGS) -sallowPrefetchUnpacking=true $(MISCFLAGS) -o ./bin/$@ $^

cleanout:
	rm -f ./out/*.out

clean:
	rm -f ./bin/$(MAIN)*
