

/* Generating Random Numbers */
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h> /* srand, rand */
#include <stdint.h> /* uint64_t */
#include <time.h>   /* time */
#include <math.h>   
#include <assert.h> 
#include <omp.h>

using namespace std;
#include "random.h"
#include "RndSet.h"
                     
#define RESEED_INTERVAL 10000

bool pattern_test(int n, RndSet *list[])
{
    bool pass = true;
    int i = 0;
    //find first even number
    for (i = 0; i < n; ++i)
    {
        if (list[i]->isEven())
            break;
    }

    if (i == n)
    {
        pass = false;
        return pass;
    }

    //now check for consecutive even odd pattern
    //beginning with even
    while (true)
    {
        if (i >= n - 1)
            break;

        i++;
        (list[i - 1]->isEven()) && (list[i]->isOdd()) ? pass = false : pass = true;
        i++;
        //want to check the next two
        if (pass == true)
            break; // 1 condition where pattern is not met is sufficient
    }

    return pass;
}

bool test_pattern_test(int n, RndSet *list[])
{
    bool pass = true;

    printf(" Pattern Test for %i Nums \n", n);
    for (int i = 0; i < n; ++i)
    {
        list[i] = new RndSet;
        list[i]->num = i;
        printf(" %lu, \n ", list[i]->num);
        //printf("",list[i]->num%2);
    }
    pass = pattern_test(n, list);
    printf(" Pattern Test Passed: %s \n ", pass ? "TRUE" : "FALSE");
    return pass;
}

void print_usage(char **argv)
{
    cout << "USAGE: " << argv[0] << " [options]" << endl;
    cout << "Options:" << endl;
    cout << "    -r [int]     reseed: on or off (r 1 or r 0)" << endl;
    cout << "    -n [int]     size of the key range that random keys will be drawn from (i.e., range [1, n])" << endl;
    cout << "    -p [int]     number of random numbers to print (every 5th, p 5)" << endl;
    cout << endl;
}

int calculate_reseed(bool reseed, uint64_t total)
{
    if (!reseed)
        return 0;

    int rs_freq = (RESEED_INTERVAL);
    return rs_freq;
}

void run_RNG(uint64_t total, int print, Random *rngs, bool reseed)
{
    //determine reseeding

    int reseed_freq = calculate_reseed(reseed, total);

    assert(total >= 1);
    printf("%lu \n", rngs->next());

    for (int i = 0; i < total - 1; ++i)
    {

        for (int j = 0; j < print - 1; ++j)
        {
            rngs->next();
            i++;
        }

        //during execution reseeding the PRNG 
        if ((reseed) && (total > RESEED_INTERVAL) )
        {

            if ( (i % reseed_freq) == 0) 
                {
                    rngs->reSeed();
                }
        }
        if (i < total - 1)
            printf("%lu \n", rngs->next());
    }
}

void setUp(int total_rngs, Random *rngs)
{

    timespec seedtime;

    clock_gettime(CLOCK_REALTIME, &seedtime);
    uint64_t nanotime = seedtime.tv_nsec;
    srand(nanotime);
    

    rngs->setSeed(rand());
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        print_usage(argv);
        return 1;
    }

    ofstream RNGfile;
    int n = 1; //total random number generators to use
    Random rngs;
    RndSet *listR[n];
    bool pass1, pass2, pass3;
    

    bool fine = false;
    bool reseed = false;
    int total_RN = 1;
    int print_num = 0;
  
    // read command line args
    for (int i = 1; i < argc; ++i)
    {

        if (strcmp(argv[i], "-r") == 0)
        {
            // specify reseeding.
           
            int rs = atoi(argv[++i]);
            if (rs == 1)
                reseed = true;
            if (rs == 0)
                reseed = false;
            
        }
        else if (strcmp(argv[i], "-n") == 0)
        {
            // specify total number of random numbers requested
            total_RN = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-p") == 0)
        {
            // specify skip level: print every 5 random numbers
            print_num = atoi(argv[++i]);
        }
        else
        {
            cout << "bad arguments" << endl;
            print_usage(argv);
            exit(1);
        }
    }

    // print command and args for debugging
    std::cerr << "Cmd:";
    for (int i = 0; i < argc; ++i)
    {
        std::cerr << " " << argv[i];
    }
    std::cerr << std::endl;


    setUp(total_RN, &rngs);


    run_RNG(total_RN, print_num, &rngs, reseed);

    return 0;
}