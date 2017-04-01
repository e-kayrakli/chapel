#! /home/ngnk/builds/env_python2/python
import math

from global_config import *
from util import *
from plot_utils import *

versions = [
    VersionType("synthInitPerf", "Hand", "", "b", "o", "solid"),
    VersionType("synthInitPerf", "Prefetch", "--prefetch", "g", "v", "solid"),
    VersionType("synthInitPerf", "Prefetch-Static", "--prefetch --staticDomain", "r", "^", "solid")]

# create weak scaling data size lookup table
for l in locales:
    ws_sizes[l] = str(int(math.sqrt(int(s)**2*int(l)/float(max(locales_int)))))


if args.mode == 'PLOT':
    create_plots(versions, "synthInitPerf")
elif args.mode == 'RUN':
    run_test(versions)
else:
    print("Unknown mode" + args.MODE)

