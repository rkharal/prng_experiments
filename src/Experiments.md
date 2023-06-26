
<h1 style="color: blue;">EXPERIMENT INSTRUCTIONS</h1>
These instructions explain how to run tests and perform
comparative experiments using various random number generators in the Random.h class.

<h2 style="color: maroon;">Pre-Generated Array of Random Numbers </h2>

- In addition to various types of PRNGs available in **random.h**, we provide an option to create pre-generated arrays of random numbers (RNs). The pre-generated array of RNs is created using either (1) XORSH PRNG based on the Marsaglia XOR-Shift or, (2) Mersenne Twisters. During execution next() function will return the next value in the array and requires no time for in-place RN generation.
Note, in our work we discuss the potential drawbacks of this approach in [Section 6.1](https://arxiv.org/pdf/2208.08469.pdf). In order to test with pre-generated arrays use compile option -DRNG1 (XORSH array) or -DRNG2(MT array). Please also see src/Makefile.

<h2 style="color: maroon;">Reseeding Option </h2>

- run_rng.cpp takes an option to reseed the PRNGs **-r** (1) for reseeding every 10 000 random numbers. Currently **random.h** reseeds with the **rdseed** instruction. This option can be changed in random.h to reseed with **rdrand** which is slightly faster for reseeding. **Rdseed** and **rdrand** are both hardware intrinsic instructions. The frequency of reseeding a PRNG can also be modified in **run_rng.cpp** by changing RESEED_INTERVAL to a new value.


<h2 style="color: maroon;">Bitwise Randomness: How It Works</h2>

- Option **-r** to allow reseeding (1) or no reseeding (0). Reseeding occurs every 10 000 random numbers.  
- Generating 10 000 000 random numbers  
- See /src/run_rng.cpp to modify the frequency of reseeding (default 10 000)
<h2 style="color: maroon;">Bitwise Randomness Assessment</h2>

- (a) Option -r to allow reseeding (1) or no reseeding (0). Reseeding occurs every 10 000 random numbers  
- (b) Generating 10 000 000 random numbers  
- (c) See /src/run_rng.cpp to modify the frequency of reseeding (default 10000)
- (d) See **run_experiments_reseeding.sh** to modify frequency of summing bit results (default is every 1 000 random numbers). 
- (e) This script will assess **bitwise randomness** properties for bits [0,9] in each generated random number.  
- (f) To update the bit postions you would like to monitor in this experiment from [0 , **nbits-1**]  see the test script: **run_experiments_reseeding.sh**. Modify the value of **nbits**.
   
<h2 style="color: maroon;">To Test a Pre-Generated Array of Random Numbers</h2>

- (a) Option -r to allow reseeding (1) or no reseeding (0)    
    Reseeding occurs every 10 000 random numbers  
- (b) Generating 10 000 000 random numbers  
- (c) See /src/run_rng.cpp to modify range or frequency of reseeding  
- (e) This script will assess bitwise randomness properties for bits [0,9] in the random number.  
- (f) To update the bit postions from [0 ,**nbits**] set **nbits** to the new value in the script **run_experiments_reseeding.sh**. 
- (g) **./run_experiments_reseeding.sh**  to generate all output .txt files in the Output directory  



