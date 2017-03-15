FLAGS=--fast --cache-remote -M $(CHPL_HOME)/test/users/engin/collective_communications
MISCFLAGS=

MAIN=synthInitPerf

all: $(MAIN) $(MAIN)_u
$(MAIN): $(MAIN).chpl
	chpl $(FLAGS) $(MISCFLAGS) -o ./bin/$@ $^
$(MAIN)_u: $(MAIN).chpl
	chpl $(FLAGS) -sallowPrefetchUnpacking=true $(MISCFLAGS) -o ./bin/$@ $^

cleanout:
	rm -f ./out/*.out

clean:
	rm -f ./bin/$(MAIN)*
