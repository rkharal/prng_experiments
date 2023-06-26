
<h1 style="color: blue;">EXPERIMENT INSTRUCTIONS</h1>
These instructions explain how to test and perform
experiments using various random number generators in the Random.h class.

<h2 style="color: maroon;">Reseeding Option </h2>

- run_rng.cpp takes an option to reseed the PRNGs **-r** (1) for reseeding every 10 000 random numbers. Currently **random.h** reseeds with RDSEED. This option can be changed.
- **run_experiments_reseeding.sh** 

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



