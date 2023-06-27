#!/usr/bin/python3
import matplotlib.pyplot as plt
import numpy as np
import platform
import sys, getopt
import fileinput
import argparse
import csv
import os
from cycler import cycler
import glob

WIN = (platform.system() == 'Windows' or 'CYGWIN' in platform.system())

######################
## parse arguments
######################

parser = argparse.ArgumentParser(description='Produce subplots, 2x3 from column data in txt files from output directory')
#parser.add_argument('-i', dest='infile', type=argparse.FileType('r'), default=sys.stdin, help='input file containing lines of form <x> <y>; if none specified then will use stdin')
parser.add_argument('-o', dest='outfile', type=argparse.FileType('w'), default=None, help='output file with any image format extension such as .png or .svg; if none specified then plt.show() will be used')

args = parser.parse_args()

######################
## create figure
######################
path='../'
traces= os.listdir( path )
start_colour=12
plt.figure(figsize=(15,15))

fig, ax= plt.subplots(2,2,sharey=True)
fig.set_figheight(6)
fig.set_figwidth(10)
#---------------------------------------############################ 
# Bit Positions to plot
pos = [0, 1, 2, 3, 4]


######################
## TOP ROW of PLOTS
######################
### File list for first row of plots
list = ["fnv1a","xorsh"]
i=0
k=0
for run in list:
    run_name = run # Replace with your desired run name
    files = []

    for p in pos:
        file_path = "../output/{}_rng/{}_rng_{}_noreseed_fnv1a.txt".format(run_name, run_name, p)
        files.extend(glob.glob(file_path))

    #print(files)

    # Grab colormap -option to change colours
    #cmap = plt.cm.get_cmap('jet')
    #j = start_colour +10
    # Loop through traces and plot them
    for trace in files:

        x, y = np.loadtxt(trace, delimiter=' ', unpack=True)

        # Grab color  unused
        #c = cmap(float(j)/len(trace))
        name = trace[22:26]
        #print(name)
        namesplit = trace.split('_')
        #print(namesplit)
        name_rng = namesplit[2].split('/')

        #print("i is {}".format(i))
        #print("k is {}".format(k))
        #print(name_rng[0]

        legendname = namesplit[3] + "-bit"
        
        
        # Define a custom color cycle
        colors = ['blue', 'green', 'red', 'orange']
        plt.rcParams['axes.prop_cycle'] = cycler(color=colors)
        #ax[k,i].plot(x, y, color=c, linewidth=0.75,
        ax[k,i].plot(x, y, linewidth=0.75,
                 linestyle='solid', label=legendname)
        # plt.figure(figsize=(6,9))
        #j = j+10

    ax[k,i].set_title("Bitwise Sum Every Number: {}:".format(run_name.upper()))
    i=i+1

ax[k,i-1].legend(loc=(0.94,0.6))

######################
## SECOND ROW of PLOTS
######################
### File list for second row of plots
list = ["mm3","rdrand"]
i=0
k=1
for run in list:
    
    files = []
    run_name = run
    #print(run_name)

    run_name = run # Replace with your desired run name

    files = []

    for p in pos:
        file_path = "../output/{}_rng/{}_rng_{}_noreseed_fnv1a.txt".format(run_name, run_name, p)
        files.extend(glob.glob(file_path))
    
    #print(files)

    #files= sorted(glob.glob("outputs/FNV1a/fnv1a_rng_{pos}bit_test.txt".format(pos=[0,1] )))

    # Grab colormap
    cmap = plt.cm.get_cmap('jet')
    j = start_colour
    # Loop through traces and plot them
    for trace in files:

        # Load file
        #####dataArray= np.loadtxt(trace, delimiter=' ', unpack=True)
        x, y = np.loadtxt(trace, delimiter=' ', unpack=True)

        # Grab color
        c = cmap(float(j)/len(traces))

        # Plot
        #ax.plot(dataArray.T,color=c)
        name = trace[22:26]
        #print(name)
        namesplit = trace.split('_')
    
        name_rng = namesplit[2].split('/')

    
        # Define a custom color cycle
        colors = ['blue', 'green', 'red', 'orange']
        plt.rcParams['axes.prop_cycle'] = cycler(color=colors)
        legendname = namesplit[3] + "-bit"
        #ax2.subplot(1, 3, 2)
        ax[k,i].plot(x, y, linewidth=0.75,
                 linestyle='solid', label=legendname)
        # plt.figure(figsize=(6,9))
        j = j+10

        #plt.xlabel('Total Random Numbers')
        #plt.ylabel('SUM')
    ax[k,i].set_title("Bitwise Sum Every Number: {}:".format(run_name.upper()))
    i=i+1

ax[k,i-1].legend(loc=(0.94,0.6))

#-------------------------------SAVING OUTPUT
plt.tight_layout()


if args.outfile == None:
    if WIN:
        mng = plt.get_current_fig_manager()
        mng.window.state('zoomed')
    plt.show()
else:
    print("saving figure image %s\n" % args.outfile.name)
    plt.savefig(args.outfile.name)
