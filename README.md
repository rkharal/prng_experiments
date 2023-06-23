# prng_experiments
Experiments related to PRNG (Pseudo Random Number Generator) usage in microbenchmarks experiements for testing
 conconurrent data structures.

 We test various PRNGs (Hardware and Software) for randomness in bit positions.
 Produce results that indicate the bitwise random behaviour generated by different PRNGs.

 Full Paper:  ["Performance Anomalies in Concurrent Data Structure Microbenchmarks"](
 https://arxiv.org/pdf/2208.08469.pdf)

Work related to PRNG Experiments (Section 6) from this work:

 This repository contains the following:
 
 - various PRNGs to test with in random.h

 - an nth-bit summation test program to test for patterns in the n-th bit positions of random numbers

 - scripts to run experiments

 - plot scripts to automate plot generation for visualizing summation results

 See USAGE instructions

 # Further Information
 Software PRNG and Hardware RNGs:
 
   - *Murmur3/Murmur64* - ["Austin Appleby. Murmurhash3, 2012."](https://github.com/aappleby/smhasher/wiki/)
 
   - *XORSH* - ["George Marsalia XOR-Shift: Xorshift. 2022."](https://en.wikipedia.org/wiki/Xorshift)

   - *MT*- Makoto Matsumoto and Takuji Nishimura. Mersenne twister: ["A 623-dimensionally equidistributed uniform pseudo-random number generator"](https://dl.acm.org/doi/pdf/10.1145/272991.272995)
 
   - *MRG*- ["Morita Naoyuki. Pseudo random number generator with mrg (multiple recursive generator),2020"](https://www.schneier.com/blog/archives/2008/05/random_number_b.html)

   - *RDRAND/RDSEED* - Intel Secure Key Instructions Gael Hofemeier and Robert Chesebrough. Introduction to intel aes-ni and intel secure key instructions. Intel, White Paper, 62, 2012.


 USAGE:

 

