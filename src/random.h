/**
 * Preliminary C++ implementation random.h using fnv1a
 * Copyright (C) 2014 Trevor Brown
 *
 * Additional Pseudo Random Number Generators (PRNGs) added 2021
 */

#ifndef RANDOM_H
#define RANDOM_H



//-------------------------------------------------------------------------
/* The list of PRNGs software and hardware for possible use in Random.h */
/* Descriptions of PRNGs. Additional information on PRNGs in README

MURMUR2     -  Murmur hash2
MURMUR3     -  Murmur hash3 
MURMUR64    -  Murmur hash3 64-bit version
XORSH       -  Marsalgia XORSH* algorithm
MT          -  Mersenne Twister
MRG         -  Combined Multiple Recursive Random Number Generators
FNV1A       -  fnv1a non-cyrptographic hash algorithm

//------------------------------------------------------------------------- */
// These are defined in Makefile or at the command line when compiling
// #define RDRAND       
// #define MURMUR3
// #define MURMUR64
// #define XORSH
// #define XORSH_RDSEED     // Re-seed XORSH with RDSEED
// #define XORSH_RDRAND     // Re-seed XORSH with RDRAND
// #define XORSH_RAND       // Re-seed XORSH with rand()
// #define MT
// #define MRG
// #define FNV1A
// #define RNG1             // Array of Pre-generated Random Numbers
// #define RNG2             // Array of Pre-generated Random Numbers

#define RDSEED_SEED     //if reseeding option is selected, RDSEED will be used to RESEED.
// #define RDRAND_SEED  //option to also use RDRAND for reseeding which is slightly faster

#define MAX_RNG_SIZE 10000000  //maximum size for RNG Array
#define RESEED_NUM 10000       //reseeding interval is decided Here

#include "plaf.h"
#include <random>
#include <iostream>
#include <cstring>
#include <ctime>
#include <immintrin.h>
#include <x86intrin.h>
#include "assert.h"

using namespace std;

//-------------------------------------
// Random class containing state and PRNG functions
// for generating random numbers
//-------------------------------------
class Random
{
private:
    uint64_t seed;
    PAD;
    struct RNGState
    {
        uint64_t x;
        uint64_t y;
        uint64_t z;
        uint64_t w;
        uint64_t c;
    };
    PAD;
    struct RNGState_64
    {
        uint64_t a;
        // uint64_t y;
        // uint64_t z;
        // uint64_t w;
        // uint64_t c;
    };
    PAD;
    RNGState state;
    PAD;
    RNGState_64 state_64;
    PAD;
    mt19937_64 mt_rand;
    PAD;
    uint64_t *rnglist; // for array of random numbers
    // uint64_t *rnglist[MAX_RNG_SIZE];
    // new uint64_t[MAX_RNG_SIZE];
    PAD;
    uint32_t index = 0;
    PAD;
    int64_t __MRG32k3a_s10 = 1, __MRG32k3a_s11 = 1, __MRG32k3a_s12 = 1, __MRG32k3a_s20 = 1, __MRG32k3a_s21 = 1, __MRG32k3a_s22 = 1;
    PAD;
    int count;

public:
    Random()
    {
        //_init();
        this->seed = 0;
    }

    Random(uint64_t seed)
    {
        this->seed = seed;
    }
    //-------------------------------------
    /* init function will intialize different PRNGs by invoking their individual init functions where necessary depending on which PRNG is defined*/
    //-------------------------------------
    void _init()
    {
        count = 0;
#ifdef MT
        mt_rand.seed(time(0));
#endif

#ifdef MRG

        MRG32k3a_init(seed);
        // MRG32k3a_init_rdrand();

#endif

// pre-generated array of random numbers RNG1- KISS_Array, RNG2- MT_Array
#ifdef RNG1
        // uint64_t *rnglist[MAX_RNG_SIZE]=new uint64_t[MAX_RNG_SIZE];
        rnglist = new uint64_t[MAX_RNG_SIZE];

        index = 0;
        rnglist[0] = 10;
        // printf("KISS Init: item 0 %lu \n", rnglist[0]);
        initialize_xorsh_array();
        initialize_xorsh_rngarray(); // CREATE ARRAY

#elif defined RNG2

        rnglist = new uint64_t[MAX_RNG_SIZE];
        // rnglist[1]=10;
        // printf("MT item 1 %lu \n", rnglist[1]);
        mt_rand.seed(time(0));
        index = 0;
        initialize_mt_rngarray(); // CREATE ARRAY
#endif

#ifdef XORSH
                                    // All XORSH Initialization here
        initialize_xorsh();
#endif

#ifdef XORSH_RDSEED
        // All XORSH Initialization here
        initialize_xorsh();
#endif

#ifdef XORSH_RAND
        // All XORSH Initialization here
        initialize_xorsh();
#endif

#ifdef XORSH_RDRAND
        // All XORSH Initialization here
        initialize_xorsh();
#endif
    }

    void setSeed(uint64_t seed)
    {
        this->seed = seed;
        _init();
    }

    void setSeed()
    {
        this->seed = 0;
        _init();
    }

    uint64_t getSeed(uint64_t seed = 1)
    {
        //_init();
        return this->seed;
    }

    /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      Re-Seed Option
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
    void reSeed()
    {
      seedReset();
    }

    uint32_t get_index()
    {
        return index;
    }

    void reset_index()
    {
        index = 0;
    }

    ~Random()
    {
#ifdef RNG1
        delete[] rnglist;

#elif defined RNG2
        delete[] rnglist;
#endif
    }


//-------------------------------------
//Functions for Reseeding option
//Reseeding a PRNG- options using RDREED or RDRAND
//-------------------------------------
#ifdef RDSEED_SEED

    uint64_t next_rdseed()
    {
        unsigned long long hash = 0ULL;
        int pass;

        do
        {
            pass = _rdseed64_step(&hash);
        } while (!pass);
        // printf("RDSEED gave back this value %llu: \n", hash);
        return hash;
    }
    // int _rdseed64_step(uint64_t*);

    uint64_t next_seed(uint64_t n)
    {

        unsigned long long hash = 0ULL;
        hash = next_rdseed();
        return hash % n;
    }

    uint64_t next_seed()
    {
        // printf("reseeding in RD SEED \n");
        return next_rdseed();
    }

#elif defined RDRAND_SEED
    uint64_t next_rdseed()
    {
        unsigned long long hash = 0ULL;
        int pass;

        do
        {
            pass = _rdrand64_step(&hash);
        } while (!pass);

        return hash;
    }
    // int _rdseed64_step(uint64_t*);

    uint64_t next_seed(uint64_t n)
    {

        unsigned long long hash = 0ULL;
        hash = next_rdseed();
        return hash % n;
    }

    uint64_t next_seed()
    {

        return next_rdseed();
    }
#endif

//------------------------------------------------------
/* The set of PRNGs follow */

//------------------------------------------------------
#ifdef RDRAND
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% USING RDRAND

    uint64_t next_rdrand()
    {
        unsigned long long hash = 0ULL;
        int pass;

        do
        {
            pass = _rdrand64_step(&hash);
        } while (!pass);

        return hash;
    }

    uint64_t next(uint64_t n)
    {

        unsigned long long hash = 0ULL;
        hash = next_rdrand();
        return hash % n;
    }

    uint64_t next()
    {

        return next_rdrand();
    }

    void seedReset()
    {
        seed = next_seed();
    }

#elif defined MRG

    /*
    Combined Multiple Recursive Random Number Generators
    */

    uint64_t next(uint64_t n)
    {
        return ((MRG32k3a_next()) % n);
    }
    uint64_t next()
    {
        return (MRG32k3a_next());
    }

    static inline uint64_t __MRG32k3a_staffordMix13(uint64_t z)
    {
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        // This is necessary in Java to guarantee that we return a positive number
        return (z >> 1) ^ (z >> 32);
    }

    /** Initializes the generator starting from a 64-bit seed. */

    void MRG32k3a_init(uint64_t s)
    {
        const int64_t m1 = UINT64_C(4294967087);
        const int64_t m2 = UINT64_C(4294944443);

        __MRG32k3a_s10 = __MRG32k3a_staffordMix13(s += 0x9e3779b97f4a7c15) % m1;
        __MRG32k3a_s11 = __MRG32k3a_staffordMix13(s += 0x9e3779b97f4a7c15) % m1;
        __MRG32k3a_s12 = __MRG32k3a_staffordMix13(s += 0x9e3779b97f4a7c15) % m1;
        __MRG32k3a_s20 = __MRG32k3a_staffordMix13(s += 0x9e3779b97f4a7c15) % m2;
        __MRG32k3a_s21 = __MRG32k3a_staffordMix13(s += 0x9e3779b97f4a7c15) % m2;
        __MRG32k3a_s22 = __MRG32k3a_staffordMix13(s += 0x9e3779b97f4a7c15) % m2;
    }

    /** Initializes directly the generator state. The first three values must be
in the range [0..4294967087) and the last three values in the range [0..4294944443). */

    void MRG32k3a_init6(const uint32_t s10, const uint32_t s11, const uint32_t s12, const uint32_t s20, const uint32_t s21, const uint32_t s22)
    {
        const int64_t m1 = INT64_C(4294967087);
        const int64_t m2 = INT64_C(4294944443);

        if (s10 == 0 && s11 == 0 && s12 == 0)
        {
            // fprintf(stderr, "s10, s11 and s12 cannot be all zero\n");
            abort();
        }
        if (s20 == 0 && s21 == 0 && s22 == 0)
        {
            // fprintf(stderr, "s20, s21 and s22 cannot be all zero\n");
            abort();
        }
        if (s10 >= m1 || s11 >= m1 || s12 >= m1)
        {
            // fprintf(stderr, "s10 (%" PRIu32 "), s11 (%" PRIu32 "), and s12 (%" PRIu32 ") must be smaller than %" PRId64 "\n", s10, s11, s12, m1);
            abort();
        }

        if (s20 >= m2 || s21 >= m2 || s22 >= m2)
        {
            // fprintf(stderr, "s20 (%" PRIu32 "), s21 (%" PRIu32 "), and s22 (%" PRIu32 ") must be smaller than %" PRId64 "\n", s20, s21, s22, m2);
            abort();
        }

        __MRG32k3a_s10 = s10;
        __MRG32k3a_s11 = s11;
        __MRG32k3a_s12 = s12;
        __MRG32k3a_s20 = s20;
        __MRG32k3a_s21 = s21;
        __MRG32k3a_s22 = s22;
        // Throw away one value to align output with L'Ecuyer original version
        MRG32k3a_next();
    }

    /** Returns the next pseudorandom double in (0..1). */
    uint64_t MRG32k3a_next()
    {
        const int64_t m1 = INT64_C(4294967087);
        const int64_t m2 = INT64_C(4294944443);
        const int32_t a12 = INT32_C(1403580);
        const int32_t a13 = INT32_C(810728);
        const int32_t a21 = INT32_C(527612);
        const int32_t a23 = INT32_C(1370589);
        const int64_t corr1 = (m1 * a13);
        const int64_t corr2 = (m2 * a23);
        // This is equivalent to 2.328306549295727688e-10, but more precise as there's no rounding involved.
        // const double norm = 0x1.000000d00000bp-32;

        int64_t p, r;

        /* Combination */
        r = __MRG32k3a_s12 - __MRG32k3a_s22;
        r -= m1 * ((r - 1) >> 63);

        /* Component 1 */
        p = (a12 * __MRG32k3a_s11 - a13 * __MRG32k3a_s10 + corr1) % m1;
        __MRG32k3a_s10 = __MRG32k3a_s11;
        __MRG32k3a_s11 = __MRG32k3a_s12;
        __MRG32k3a_s12 = p;

        /* Component 2 */
        p = (a21 * __MRG32k3a_s22 - a23 * __MRG32k3a_s20 + corr2) % m2;
        __MRG32k3a_s20 = __MRG32k3a_s21;
        __MRG32k3a_s21 = __MRG32k3a_s22;
        __MRG32k3a_s22 = p;
        uint64_t multiplyfactor = (1000000000000000000);
        // return (r * norm * multiplyfactor);
        return r;
    }

    void seedReset()
    {
        seed = next_seed();
        MRG32k3a_init(seed);
    }

#elif defined MURMUR3

    uint64_t next(uint64_t n)
    {

        seed = murmur3(seed);
#ifdef RNDPRINT
        printf(" Murmur HASH next(uint) %lu , ", hash);
#endif
        return seed % n;
    }

    uint64_t next()
    {

        seed = murmur3(seed);
        return seed;
    }


    uint32_t murmur3(uint32_t key)
    {

        constexpr uint32_t seed = 0x1a8b714c;
        constexpr uint32_t c1 = 0xCC9E2D51;
        constexpr uint32_t c2 = 0x1B873593;
        constexpr uint32_t n = 0xE6546B64;

        uint32_t k = key;
        k = k * c1;
        k = (k << 15) | (k >> 17);
        k *= c2;

        uint32_t h = k ^ seed;
        h = (h << 13) | (h >> 19);
        h = h * 5 + n;

        h ^= 4;

        h ^= (h >> 16);
        h *= 0x85EBCA6B;
        h ^= (h >> 13);
        h *= 0xC2B2AE35;
        h ^= (h >> 16);
        return h;
    }

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% USING MURMUR 64

    void seedReset()
    {
        seed = next_seed();
    }

#elif defined MURMUR64

    // const char *key = "hi";
    //  MurmurHash3_x64_128(key, (uint64_t)strlen(key), seed, hash_otpt);
    //  cout << "hashed" << hash_otpt << endl;

    uint64_t next(uint64_t n)
    {
        int len = 8;
        const char *key = "hello world";

        seed = murmur_hash_64(key, (uint64_t)strlen(key), seed);
#ifdef RNDPRINT
        printf(" Murmur HASH next(uint) %lu , ", hash);
#endif
        return seed % n;
    }

    uint64_t next()
    {
        int len = 8;
        const char *key = "hello world";

        seed = murmur_hash_64(key, (uint64_t)strlen(key), seed);
        // seed = murmur_hash_64(len,seed);
        return seed;
    }

    uint64_t murmur_hash_64(const void *key, int len, uint64_t seed)
    {
        const uint64_t m = 0xc6a4a7935bd1e995ULL;
        const int r = 47;

        uint64_t h = seed ^ (len * m);

        const uint64_t *data = (const uint64_t *)key;
        const uint64_t *end = data + (len / 8);

        while (data != end)
        {
           
            uint64_t k = *data++;

            k *= m;
            k ^= k >> r;
            k *= m;

            h ^= k;
            h *= m;
        }

        const unsigned char *data2 = (const unsigned char *)data;

        switch (len & 7)
        {
        case 7:
            h ^= uint64_t(data2[6]) << 48;
        case 6:
            h ^= uint64_t(data2[5]) << 40;
        case 5:
            h ^= uint64_t(data2[4]) << 32;
        case 4:
            h ^= uint64_t(data2[3]) << 24;
        case 3:
            h ^= uint64_t(data2[2]) << 16;
        case 2:
            h ^= uint64_t(data2[1]) << 8;
        case 1:
            h ^= uint64_t(data2[0]);
            h *= m;
        };

        h ^= h >> r;
        h *= m;
        h ^= h >> r;

        return h;
    }

    void seedReset()
    {
        seed = next_seed();
    }

#elif defined MT

    uint64_t next(uint64_t n)
    {

        seed = mt_rand();
        return seed % n;
    }

    uint64_t next()
    {

        seed = mt_rand();
        return seed;
    }

    void seedReset()
    {
        seed = next_seed();
        mt_rand.seed(seed);
    }

#elif defined XORSH


    uint64_t next(uint64_t n)
    {
        seed = _xorsh();
        return seed % n;
    }

    uint64_t next()
    {
        seed = _xorsh();
        return seed;
    }

    uint64_t _xorsh()
    {
        return advance_xorsh();
    }

    uint64_t advance_xorsh()
    {
        uint64_t x = state_64.a; /* The state must be seeded with a nonzero value. */
        x ^= x >> 12;            // a
        x ^= x << 25;            // b
        x ^= x >> 27;            // c
        state_64.a = x;
        return x * UINT64_C(0x2545F4914F6CDD1D);
    }

    void
    initialize_xorsh()
    {

        state_64.a = seed;
        
    }
    void seedReset()
    {
        seed = next_seed();
        initialize_xorsh();
    }

#elif defined FNV1A

    uint64_t next(uint64_t n)
    {
        uint64_t offset = 14695981039346656037ULL;
        uint64_t prime = 1099511628211;
        uint64_t hash = offset;
        hash ^= seed;
        hash *= prime;
        seed = hash;
       
        return hash % n;
    }

    size_t next()
    {
        uint64_t offset = 14695981039346656037ULL;
        uint64_t prime = 1099511628211;
        uint64_t hash = offset;
        hash ^= seed;
        hash *= prime;
        seed = hash;
        
        return hash;
    }

    void seedReset()
    {
        seed = next_seed();
    }

    //------------------------------------------------------
    /* RNG Array OPTION: Array of Random Numbers
    or RNG1- Array of RN using XORSH PRNG
    or RNG2- Array of RN using MT PRNG
    */
   //------------------------------------------------------
#elif defined RNG1  // XORSH based Array

    uint64_t next(uint64_t n)
    {
        if (index >= MAX_RNG_SIZE)
        {
            index = 0;
        }
        // assert(index < MAX_RNG_SIZE);
        uint64_t hash = rnglist[index];
        index++;
        return hash % n;
    }

    size_t next()
    {

        if (index >= MAX_RNG_SIZE)
        {
            index = 0;
        }
        // assert(index < MAX_RNG_SIZE);
        uint64_t hash = rnglist[index];
        index++;
        return hash;
    }

    void initialize_xorsh_rngarray()
    {

        for (int i = 0; i < MAX_RNG_SIZE; ++i)
        {
            rnglist[i] = advance_xorsh_array();
            
        }
       
    }

    void
    initialize_xorsh_array()
    {
        // srand(time(0))
        // state_64.a = xorsh_rdrand_array();
        state_64.a = seed;
    }

    uint64_t advance_xorsh_array()
    {
        uint64_t x = state_64.a; /* The state must be seeded with a nonzero value. */
        x ^= x >> 12;            // a
        x ^= x << 25;            // b
        x ^= x >> 27;            // c
        state_64.a = x;
        return x * UINT64_C(0x2545F4914F6CDD1D);
    }

    void seedReset()
    {
        seed = next_seed();
    }

#elif defined RNG2  // MT based Array

    uint64_t next(uint64_t n)
    {
        if (index >= MAX_RNG_SIZE)
        {
            index = 0;
        } // assert(index < MAX_RNG_SIZE);
        uint64_t hash = rnglist[index];
        index++;
        return hash % n;
    }

    size_t next()
    {
        if (index >= MAX_RNG_SIZE)
        {
            index = 0;
        } // assert(index < MAX_RNG_SIZE);
        uint64_t hash = rnglist[index];
        index++;
        return hash;
    }

    void initialize_mt_rngarray()
    {

        for (int i = 0; i < MAX_RNG_SIZE; ++i)
        {
            // printf("MT about to initialize array in RNGARRAY2 with i: %i \n",i);
            // rnglist[i]= (uint64_t *) (new advance_xorsh();
            rnglist[i] = mt_rand();

            // printf("IN MT ARRAY i %lu \n", rnglist[i]);
        }

        // printf("Done init Array MT \n");
    }

    void seedReset()
    {
        seed = next_seed();
    }

    //-----------------------------------------------------------------
    /* These functions are specific to reseeding the XORSH PRNG Only */
    /* RESEEDING the XORSH PRNG THOURH RDRAND
    or RESEEDING through RDSEED
    or RESEEDING through rand()
    */

#elif defined XORSH_RDSEED

    // #ifdef XORSH

    uint64_t next(uint64_t n)
    {
        count++;
        if (count == RESEED_NUM)
        {

            seedReset();

            // printf(" KISS_RDSEED next RN with parameter reseeding count is: %i",count);
            count = 0;
        }
        seed = _xorsh();
        return seed % n;
    }

    uint64_t next()
    {
        count++;
        if (count == RESEED_NUM)
        {

            seedReset();
            // printf(" KISS_RDSEED next RN withOUT parameter reseeding count is: %i",count);
            count = 0;
        }
        seed = _xorsh();
        return seed;
    }

    uint64_t _xorsh()
    {
        return advance_xorsh();
    }

    uint64_t advance_xorsh()
    {
        uint64_t x = state_64.a; /* The state must be seeded with a nonzero value. */
        x ^= x >> 12;            // a
        x ^= x << 25;            // b
        x ^= x >> 27;            // c
        state_64.a = x;
        return x * UINT64_C(0x2545F4914F6CDD1D);
    }

    void
    initialize_xorsh()
    {
        state_64.a = seed;
    }


    void seedReset()
    {

        seed = next_seed();
        initialize_xorsh();
    }

#elif defined XORSH_RDRAND
    // #ifdef XORSH

    uint64_t next(uint64_t n)
    {
        count++;
        if (count == RESEED_NUM)
        {

            seedReset();

            // printf(" KISS_RDRAND next RN with parameter reseeding count is: %i",count);
            count = 0;
        }
        seed = _xorsh();
        return seed % n;
    }

    uint64_t next()
    {
        count++;
        if (count == RESEED_NUM)
        {

            seedReset();
            // printf(" KISS_RDRAND next RN withOUT parameter reseeding count is: %i",count);
            count = 0;
        }
        seed = _xorsh();
        return seed;
    }

    uint64_t _xorsh()
    {
        return advance_xorsh();
    }

    uint64_t advance_xorsh()
    {
        uint64_t x = state_64.a; /* The state must be seeded with a nonzero value. */
        x ^= x >> 12;            // a
        x ^= x << 25;            // b
        x ^= x >> 27;            // c
        state_64.a = x;
        return x * UINT64_C(0x2545F4914F6CDD1D);
    }

    void
    initialize_xorsh()
    {

        state_64.a = seed;
      
    }

    uint64_t xorsh_rdrand()
    {
        unsigned long long hash = 0ULL;
        int pass;

        do
        {
            pass = _rdrand64_step(&hash);
        } while (!pass);

        return hash;
    }

    void seedReset()
    {

        seed = xorsh_rdrand();
        initialize_xorsh();
    }

#elif defined XORSH_RAND
    // #ifdef XORSH

    uint64_t next(uint64_t n)
    {
        count++;
        if (count == RESEED_NUM)
        {

            seedReset();

            // printf(" KISS_RAND next RN with parameter reseeding count is: %i",count);
            count = 0;
        }
        seed = _xorsh();
        return seed % n;
    }

    uint64_t next()
    {
        count++;
        if (count == RESEED_NUM)
        {

            seedReset();
            // printf(" KISS_RAND next RN withOUT parameter reseeding count is: %i",count);
            count = 0;
        }
        seed = _xorsh();
        return seed;
    }

    uint64_t _xorsh()
    {
        return advance_xorsh();
    }

    uint64_t advance_xorsh()
    {
        uint64_t x = state_64.a; /* The state must be seeded with a nonzero value. */
        x ^= x >> 12;            // a
        x ^= x << 25;            // b
        x ^= x >> 27;            // c
        state_64.a = x;
        return x * UINT64_C(0x2545F4914F6CDD1D);
    }

    void
    initialize_xorsh()
    {
        srand(time(0));
        state_64.a = seed;
       
    }

    void seedReset()
    {
        seed = rand();
        initialize_xorsh();
    }

#else
#error Forgot Params
#endif
};

#endif /* RANDOM_H */
