# prng_experiments
Experiments related to PRNG (Pseudo Random Number Generator) usage in microbenchmarks experiements for testing
 conconurrent data structures.

 We test various PRNGs (Hardware and Software) for randomness in bit positions.
 Produce results that indicate the bitwise random behaviour generated by different PRNGs.

 Work related to PRNG Experiments (Section 6) from this work:
 "Performance Anomalies in Concurrent Data Structure Microbenchmarks"
 https://arxiv.org/pdf/2208.08469.pdf

 This repository contains the following:
 
 - various PRNGs to test with in random.h

 - an nth-bit summation test program to test for patterns in the n-th bit positions of random numbers

 - scripts to run experiments

 - plot scripts to automate plot generation for visualizing summation results.

 See USAGE instructions below

 Further Information
 Software PRNG and Hardware RNGs:
 
    Murmur2-

    Murmur3-
 
    Murmur64-

    XORSH -

    MT-

    MRG-

    RDRAND-

    RDSEED-








 USAGE:

 

