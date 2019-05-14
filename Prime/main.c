#include "BigInt.h"
#include "common.h"
#include <stdio.h>
#include <time.h>

const size_t kDigits = 256; // max num : 2^(256*8) = 2^2048
// sieve
size_t smallPrimes[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,
                        101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,
                        193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,
                        293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,
                        409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541};
size_t smallPrimesCount = 100;

int main(int argc, char ** argv)
{
    printf("Usage: %s nbits\n", argv[0]);

    srand(time(0));

    int nbits = 512;
    if (argc > 1)
    {
        nbits = max(8, atoi(argv[1]));
        nbits = min(1024, nbits);
    }

    gint n_lo, n_hi, _1;
    ggint_one(n_lo);
    ggint_one(n_hi);
    ggint_one(_1);
    ggint_shbl(n_lo, nbits - 1);
    ggint_shbl(n_hi, nbits);
    ggint_sub_gint(n_lo, n_hi);

    gint n;
    ggint_zero(n);
    size_t pmod[541];

    printf("Searching for %d-bit prime ...\n", nbits);

    clock_t start,end;
    double cpu_time_used;
    start = clock();

    size_t ncheck = 0;
    size_t i,p,r;
    while (true)
    {
        if (ggint_is_zero(n))
        {
            ggint_rand_range(n, n_hi);
            ggint_add_gint(n_lo, n);
            if (ggint_is_even(n))
                ggint_add_int(1, n);
            for (i=0; i<smallPrimesCount; i++)
            {
                p = smallPrimes[i];
                ggint_mod_int(p, n, &r);
                pmod[i] = r;
            }
        }

        bool do_fast = true;
        while (true)
        {
            for (i = 0; i < smallPrimesCount; ++i)
            {
                if (pmod[i] == 0)
                {
                    do_fast = false;
                    break;
                }
            }
            if (do_fast == false)
            {
                ncheck++;
                ggint_add_int(2, n);
                for (i=0; i < smallPrimesCount; i++)
                {
                    p = smallPrimes[i];
                    pmod[i] += 2;
                    if (pmod[i] >= p)
                        pmod[i] -= p;
                }
                do_fast = true;
                continue;
            }
            else
                break;
            if (do_fast == false)
                break;
        }

        if (is_prime(n, max(10, nbits/16)))
        {
            printf("\nFound prime p:\n");
            ggint_print_format("p", n,true);
            break;
        }
        else
        {
            printf(".");
            fflush(stdout);
        }

        ncheck++;
        ggint_add_int(2, n);
        for (i = 0; i < smallPrimesCount; ++i)
        {
            p = smallPrimes[i];
            pmod[i] += 2;
            if (pmod[i] >= p)
                pmod[i] -= p;
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
    printf("Checked %d numbers in %d ms: %g num/sec\n", (int) ncheck, (int) cpu_time_used, 1000.0*((double)(ncheck))/cpu_time_used);

    return 0;
}
