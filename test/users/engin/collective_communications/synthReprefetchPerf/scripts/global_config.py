import argparse

plot_path = './'
parser = argparse.ArgumentParser()

parser.add_argument("--slurm", action="store_true")
parser.add_argument("--no_legend", action="store_true")
parser.add_argument("mode", choices=['RUN', 'PLOT'])
parser.add_argument("size")
parser.add_argument("num_tries", type=int, default=5)

args = parser.parse_args()
no_legend = args.no_legend
s=args.size
control_s = int(s) # make sure its actually an int

# these two can also be an argument
use_slurm = args.slurm
slurm_part = "all" # no effect if !use_slurm. george:hpcl, pyramid:all

locales=["02" , "04"]
locales_int = [2,4]

if use_slurm:
    locales=["02" , "04", "08", "16", "32"]
    locales_int = [2,4,8,16,32]

tries = range(1, args.num_tries+1)
