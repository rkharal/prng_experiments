CC=g++
##CFLAGS= -fno-omit-frame-pointer -g -I.
CFLAGS= -I #path to include
#CFLAGS= -g -I.
LIBS=-mrdrnd -mrdseed
OBJS=run_rng.cpp parse_rng.cpp

.PHONY: all run parse

all: all_rngs parse

run: run_rng.cpp
	$(CC) -o run_rng run_rng.cpp -DMURMUR3 $(LIBS) 

parse: parse_rng.cpp
	$(CC) -o ../bin/parse_rng parse_rng.cpp $(LIBS) 

all_rngs: xorsh mm3 mm64 mt mrg fnv1a rdrand 

xorsh: run_rng.cpp	
	$(CC) -o ../bin/xorsh_rng run_rng.cpp -DXORSH $(LIBS) 

mm3: run_rng.cpp	
	$(CC) -o ../bin/mm3_rng run_rng.cpp -DMURMUR3 $(LIBS) 

mm64: run_rng.cpp	
	$(CC) -o ../bin/m64_rng run_rng.cpp -DMURMUR64 $(LIBS) 

mt: run_rng.cpp	
	$(CC) -o ../bin/mt_rng run_rng.cpp -DMT $(LIBS) 

mrg: run_rng.cpp	
	$(CC) -o ../bin/mrg_rng run_rng.cpp -DMRG $(LIBS) 

fnv1a: run_rng.cpp	
	$(CC) -o ../bin/fnv1a_rng run_rng.cpp -DFNV1A $(LIBS) 

rdrand: run_rng.cpp	
	$(CC) -o ../bin/rdrand_rng run_rng.cpp -DRDRAND $(LIBS) 

rngarry1: run_rng.cpp	
	$(CC) -o ../bin/rngarry1_rng run_rng.cpp -DRNG1 $(LIBS)

rngarry2: run_rng.cpp	
	$(CC) -o ../bin/rngarry2_rng run_rng.cpp -DRNG2 $(LIBS)

