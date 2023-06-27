
<h1 style="color: blue;">EXPERIMENT INSTRUCTIONS</h1>
These instructions explain examples of how to run tests and perform
comparative experiments using various random number generators in the Random.h class.

Full Paper:  ["Performance Anomalies in Concurrent Data Structure Microbenchmarks"](https://arxiv.org/pdf/2208.08469.pdf)
Work related to PRNG Experiments (Section 6) from this work is shared in this repository.
<h2 style="color: maroon;">Pre-Generated Array of Random Numbers </h2>

- In addition to various types of PRNGs available in **random.h**, we provide an option to create pre-generated arrays of random numbers (RNs). The pre-generated array of RNs is created using either (1) XORSH PRNG based on the Marsaglia XOR-Shift or, (2) Mersenne Twisters. During execution next() function will return the next value in the array and requires no time for in-place RN generation.
Note, in our work we discuss the potential drawbacks of this approach in [Section 6.1](https://arxiv.org/pdf/2208.08469.pdf). In order to test with pre-generated arrays use compile option -DRNG1 (XORSH array) or -DRNG2 (MT array). Please also see src/Makefile.

<h2 style="color: maroon;">Reseeding Option </h2>

- run_rng.cpp takes an option to reseed the PRNGs **-r** (1) for reseeding every 10 000 random numbers. Currently **random.h** reseeds with the **rdseed** instruction. This option can be changed in random.h to reseed with **rdrand** which is slightly faster for reseeding. **Rdseed** and **rdrand** are both hardware intrinsic instructions. The frequency of reseeding a PRNG can also be modified in **run_rng.cpp** by changing RESEED_INTERVAL to a new value.

<h2 style="color: maroon;">Bitwise Randomness: How It Works</h2>

- The file **parse_rng.cpp** assesses the bitwise randomness of varying bit positions in each generated RN. 
- We assess the bitwise random behaviour of generated RNs by assigning a value of +1 or -1 to each bit. 
- For example, if we are examining the zero bit of an RN, we assign +1 if the bit is on (equal to 1) and -1 if the bit is off (equal to 0).
- We take the sum of all these values and write the result to output at a specified frequency using the -s option. The sum is an ongoing value, it is printed at a particular rate given by -s. In the experiment scripts (**run_experiment_noreseeding.sh**) we write out the sum every 1000 RNs and display the result.
- We plot the summation results in the python scripts. Summation results indicate if the generated RNs are favouring positive values or negative values in a specific bit position. A PRNG that shows summation results that are always positive indicates that the bit in the specified position favours a setting of 1 over a value of 0. There can be strong favouring towards one direction in the values of bits.
- See scripts showing the fnv1a bitwise results (**run_experiment_fnv1a.sh** and corresponding plots **fnv1a_compare.png**). Here we took every RN and printed the bit as a -1 or +1 (summation was set to 1 in **parse_rng** using the -s option).
- The FNV1a results indicate the sum of all RNs have patterns in each bit position.
   
<h2 style="color: maroon;">Sample Experiments</h2>

- There are various scripts to run experiments in the scripts directory.
- The user is encouraged to create their own experiments by following directions given in the execution and ploting scripts found in the scripts directory.

