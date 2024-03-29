


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h> /* srand, rand */
#include <stdint.h> /* uint64_t */
#include <time.h>   /* time */
#include <math.h>   
#include <assert.h> 
#include <string>   
#include <cstring>  
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

long int Sum = 0;
uint64_t print_sum = 0;
uint64_t print_sum_count = 0;
bool final_total = false;

void print_usage(char **argv)
{
    cout << "USAGE: " << argv[0] << " [options]" << endl;
    cout << "Options:" << endl;
    cout << "    -b [int]     Bit postion to test for" << endl;
    cout << "    -s [int]     Sum frequency (how often to print out the ongoing Sum of bits)" << endl;
    cout << "    -t [int]     Generate a single total (final sum of bitwise values). This overrides sum frequency." << endl;
    

    cout << endl;
}

void print_sums(int sum_freq, uint64_t bit, vector<uint64_t> *nums)
{
    int64_t next_sum = 0;
    printf("2^bit= %lu  \n", bit);
    // AND the next RN with correct bit
    for (int i = 0; i < nums->size(); ++i)
    {

        uint64_t result = (nums->at(i) & bit);
        printf("logic AND with %lu result is %lu \n", nums->at(i), result);
        if ((result > 0))
        {
            next_sum++;
        }
        else
        {
            next_sum += -1;
        }
    }

    printf("final sum of n= %i numbers:  %i \n", (int)nums->size(), (int)next_sum);
}

void process_num(uint64_t num, uint64_t bit, uint64_t total_rn)
{
    int64_t next_sum = 0;

    uint64_t result = (num & bit);
 
    if ((result > 0))
    {
        next_sum++;
    }
    else
    {
        next_sum += -1;
    }

    Sum += next_sum;
    if ( !final_total && ( (total_rn % print_sum) == 0) )
    //if ( (total_rn % print_sum) == 0) 
    {
        print_sum_count++;
        cout << "Sum #" << print_sum_count << ": of " << total_rn << " numbers. Sum is : " << Sum << "\n";
        //
    }
}

uint64_t get_position(int bit)
{

    return ((uint64_t)1) << bit;
}

int main(int argc, char **argv)
{

    if (argc == 1)
    {
        print_usage(argv);
        return 1;
    }

    int bit_position = 0;
    uint64_t sum_freq = 1;
    bool one_total = false;

    // read command line args
    for (int i = 1; i < argc; ++i)
    {

        if (strcmp(argv[i], "-b") == 0)
        {
          
            bit_position = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            // specify sum interval
            sum_freq = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            // specify if only 1 single total is needed
            int Stotal = atoi(argv[++i]);
            
            one_total = (Stotal == 1) ? true : false;
        }
        else
        {
            cout << "bad arguments" << endl;
            print_usage(argv);
            exit(1);
        }
    }

    string rawInput;
    //vector<int> temp;
    stringstream ss;
    //vector<uint64_t> numbers;
    uint64_t total = 0;
    uint64_t bit_word = get_position(bit_position);
    print_sum = sum_freq;

   
    final_total = one_total;

    const int BUFSIZE = 1024;
    char buf[BUFSIZE];
    while (fgets(buf, BUFSIZE, stdin))
    {
        
        uint64_t x = strtoul(buf, NULL, 10);
        total++;
        //printf("going to process next num x: %lu  \n",x);
        process_num(x, bit_word, total);
    }

    if (final_total) {

        uint64_t absSum= abs(Sum);
        //cout << "Final #" << print_sum_count << ": of " << total << " numbers. Sum is : " << absSum << "\n";
        cout << "Final Total: " << absSum << "\n";
        
    }
    
    return 0;
}