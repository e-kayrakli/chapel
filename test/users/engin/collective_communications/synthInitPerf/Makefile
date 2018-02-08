FLAGS=--fast --cache-remote
MISCFLAGS=
PYFLAGS=

MAIN=synthInitPerf

all: $(MAIN) $(MAIN)_u
$(MAIN): $(MAIN).chpl
	chpl $(FLAGS) $(MISCFLAGS) -o ./bin/$@ $^
$(MAIN)_u: $(MAIN).chpl
	chpl $(FLAGS) -sallowPrefetchUnpacking=true $(MISCFLAGS) -o ./bin/$@ $^

cleanout:
	rm -f ./out/*.out ./err/*.err

clean:
	rm -f ./bin/$(MAIN)*

runlocal:
	python scripts/run.py RUN $(SIZE) $(NUMTRIES)
plotlocal:
	python scripts/run.py PLOT $(SIZE) $(NUMTRIES)

runslurm:
	python scripts/run.py --slurm RUN $(SIZE) $(NUMTRIES)
plotslurm:
	python scripts/run.py --slurm PLOT $(SIZE) $(NUMTRIES) $(PYFLAGS)
