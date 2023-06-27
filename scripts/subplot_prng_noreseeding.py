import numpy as np
import matplotlib.pyplot as plt
import argparse
import glob
import platform
import sys, getopt
import fileinput
import argparse

############################################

# This file generates 6 subplots in one loop using plot_groups
# This is an alternative to subplots_noreseeding.py

############################################

WIN = (platform.system() == 'Windows' or 'CYGWIN' in platform.system())
parser = argparse.ArgumentParser(description='Produce a plot of 6 subplots. Output file provided using -o')
parser.add_argument('-o', dest='outfile', type=argparse.FileType('w'), default=None, help='output file with any image format extension such as .png or .svg; if none specified then plt.show() will be used')
#parser.add_argument('-f', dest='alg_name', default=None, help='which file to run')
args = parser.parse_args()


# Define the list of file groups for each row of plots
plot_groups = [["xorsh", "mm3", "mt"], ["m64", "rdrand", "mrg"]]

fig, axs = plt.subplots(2, 3, figsize=(12, 8))  # Create a 2x3 grid of subplots
fig.tight_layout(pad=3.0)  # Adjust subplot spacing

for k, row in enumerate(plot_groups):
    for i, run_name in enumerate(row):
        pos = [0, 1, 2, 3]
        files = []

        for p in pos:
            file_path = "../output/{}_rng/{}_rng_{}_noreseed.txt".format(run_name, run_name, p)
            files.extend(glob.glob(file_path))

        # Loop through traces and plot them
        for trace in files:
            x, y = np.loadtxt(trace, delimiter=' ', unpack=True)
            name_rng = trace.split('_')[2].split('/')
            legendname = trace.split('_')[3] + "-bit"
            axs[k, i].plot(x, y, linewidth=0.75, linestyle='solid', label=legendname)

        axs[k, i].set_title("Bitwise Sum No Reseed {}:".format(run_name.upper()))
        #axs[k, i].legend(loc=(0.94, 0.6))
    axs[k, i].legend(loc=(0.90, 0.6))
# Saving or displaying the figure
if args.outfile is None:
    plt.show()
else:
    print("Saving figure image: {}\n".format(args.outfile.name))
    plt.savefig(args.outfile.name)
