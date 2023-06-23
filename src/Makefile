CC=g++
##CFLAGS= -fno-omit-frame-pointer -g -I.
CFLAGS= -g -I.
LIBS=-mrdrnd -mrdseed
OBJS=run_rng.cpp parse_rng.cpp

.PHONY: all run parse

all: all_rngs parse

run: run_rng.cpp
	g++ -o run_rng run_rng.cpp -DMURMUR3 $(LIBS) $(CFLAGS)

parse: parse_rng.cpp
	$(CC) -o parse_rng parse_rng.cpp $(LIBS) $(CFLAGS)

all_rngs: xorsh mm3 mm64 mt mrg fnv1a rdrand 

xorsh: run_rng.cpp	
	g++ -o ../bin/xorsh_rng run_rng.cpp -DXORSH $(LIBS) $(CFLAGS)

mm3: run_rng.cpp	
	g++ -o ../bin/mm3_rng run_rng.cpp -DMURMUR3 $(LIBS) $(CFLAGS)	

mm64: run_rng.cpp	
	g++ -o ../bin/m64_rng run_rng.cpp -DMURMUR64 $(LIBS) $(CFLAGS)

mt: run_rng.cpp	
	g++ -o ../bin/mt_rng run_rng.cpp -DMT $(LIBS) $(CFLAGS)	

mrg: run_rng.cpp	
	g++ -o ../bin/mrg_rng run_rng.cpp -DMRG $(LIBS) $(CFLAGS)	

fnv1a: run_rng.cpp	
	g++ -o ../bin/fnv1a_rng run_rng.cpp -DFNV1A $(LIBS) $(CFLAGS)	

rdrand: run_rng.cpp	
	g++ -o ../bin/rdrand_rng run_rng.cpp -DRDRAND $(LIBS) $(CFLAGS)

