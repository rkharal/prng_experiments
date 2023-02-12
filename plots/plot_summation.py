#!/usr/bin/python3
import matplotlib.pyplot as plt
import numpy as np
import platform
import sys, getopt
import fileinput
import argparse
import csv
import os

import glob
"""
x = []
y = []
"""
WIN = (platform.system() == 'Windows' or 'CYGWIN' in platform.system())

######################
## parse arguments
######################

parser = argparse.ArgumentParser(description='Produce a single-curve (x,y)-line plot from TWO COLUMN data provided via a file or stdin.')
parser.add_argument('-i', dest='infile', type=argparse.FileType('r'), default=sys.stdin, help='input file containing lines of form <x> <y>; if none specified then will use stdin')
parser.add_argument('-o', dest='outfile', type=argparse.FileType('w'), default=None, help='output file with any image format extension such as .png or .svg; if none specified then plt.show() will be used')
parser.add_argument('-b', dest='position', default=None, help='bit position to look for in outputs/files')
args = parser.parse_args()

#x, y = np.loadtxt('outputs/kiss_rng_5_test.txt', delimiter=' ', unpack=True)
#plt.plot(x,y, label='KISS 5bit')

##path='./outputs'
"""
with open('example.txt','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(int(row[0]))
        y.append(int(row[1]))
 -b 5
"""
## GLOB

##########################################

#Read in list of files. You might want to look into os.listdir()

path='../'
traces= os.listdir( path )

files =[]
#sstring = "*"+ args.position + "_test.txt"
files= sorted(glob.glob("outputs/FNV1a/fnv1a_rng_{pos}bit_test.txt".format(pos= args.position)))
print(files)
print("done")

# Create figure 
fig=plt.figure()
fig.show()
ax=fig.add_subplot(111)

# Grab colormap
cmap = plt.cm.get_cmap('jet')
j=1
# Loop through traces and plot them
for trace in files:

    # Load file
    #####dataArray= np.loadtxt(trace, delimiter=' ', unpack=True)
    x, y = np.loadtxt(trace, delimiter=' ', unpack=True)
    
    # Grab color
    c=cmap(float(j)/len(traces))

    # Plot
    #ax.plot(dataArray.T,color=c)
    name = trace[8:14]
    namesplit= trace.split('/')
    name_rng = namesplit[1].split('_')
    #print(name_rng[0])

    plt.plot( x, y, color=c, linewidth=2, linestyle='solid', label=name_rng[0]+name_rng[2])
    j=j+7

plt.xlabel('Total Sums')
plt.ylabel('Value')
plt.title("Position " +args.position + '-bit Summation FNV1A 10Million RNumbs \n')
plt.legend()
plt.show()
############################ FILE 02

if args.outfile == None:
    if WIN:
        mng = plt.get_current_fig_manager()
        mng.window.state('zoomed')
    plt.show()
else:
    print("saving figure image %s\n" % args.outfile.name)
    plt.savefig(args.outfile.name)
"""

x, y = np.loadtxt('mm64_rng_5_test.txt', delimiter=' ', unpack=True)
plt.plot( x, y, color='blue', linewidth=2, linestyle='solid', label="MM64 High")
plt.legend()

x, y = np.loadtxt('MT_rng_5_test.txt', delimiter=' ', unpack=True)
plt.plot( x, y, color='green', linewidth=2, linestyle='solid', label="MT High")
plt.legend()


x, y = np.loadtxt('mm3_rng_5_test.txt', delimiter=' ', unpack=True)
plt.plot( x, y, color='olive', linewidth=2, linestyle='solid', label="MM3 High")
plt.legend()

x, y = np.loadtxt('fnv1a_rng_5_test.txt', delimiter=' ', unpack=True)
plt.plot( x, y, color='red', linewidth=2, linestyle='solid', label="Fnv1a High")
plt.legend()

#x, y = np.loadtxt('MRG_high.txt', delimiter=' ', unpack=True)
#plt.plot( x, y, color='orange', linewidth=2, linestyle='solid', label="MRG High")
#plt.legend()


x, y = np.loadtxt('RDRand_high.txt', delimiter=' ', unpack=True)
plt.plot( x, y, color='purple', linewidth=2, linestyle='solid', label="RDRAND Low")
plt.legend() 


x, y = np.loadtxt('FNV1_high.txt', delimiter=' ', unpack=True)
plt.plot( x, y, color='purple', linewidth=2, linestyle='solid', label="FNV1 High")
plt.legend()
"""

"""
#plt.plot(x,b, label='Loaded from KISS!')

if args.outfile == None:
    if WIN:
        mng = plt.get_current_fig_manager()
        mng.window.state('zoomed')
    plt.show()
else:
    print("saving figure image %s\n" % args.outfile.name)
    plt.savefig(args.outfile.name
    
"""