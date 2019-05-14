#ifndef __Miller__
#include "BigInt.h"

// Miller-Robin primality test
// return false: number n is composite
// return true:  number n is very likely to be a prime
//
bool is_prime(gint n, size_t trials)
{
    if (ggint_is_even(n))
        return false;


    gint _1;
    ggint_one(_1);
    gint n_1;
    ggint_set_gint(n_1,n);
    ggint_sub_gint(_1, n_1);

    size_t s = 0;
    gint m;
    ggint_set_gint(m,n_1);
    while (ggint_is_even(m))
    {
        ++s;
        ggint_shbr(m, 1);
    }

    gint d;
    {
        ggint_set_gint(m,n_1);
        gint t;
        ggint_set_gint(t, _1);
        gint r;
        ggint_shbl(t, s);
        ggint_div_gint(t, m, d, r);
    }

    if (trials == 0)
        trials = 3;

    size_t i;
    for (i = 0; i < trials; i++)
    {
        gint a;
        {
            gint _max; ggint_set_gint(_max, n);
            gint _2; ggint_set(_2, 2);
            gint _4; ggint_set(_4, 4);
            ggint_sub_gint(_4, _max);

            ggint_rand_range(a, _max);
            ggint_add_gint(_2, a);
        }

        gint x;
        ggint_pow_mod(a, d, n, x);

        if (ggint_equal(x, _1) || ggint_equal(x, n_1))
            continue;
        size_t r;
        for (r = 0; r < s - 1; r++)
        {
            gint x2, g;
            ggint_mul_gint(x, x, x2);
            ggint_mod_gint(n, x2, g);
            ggint_set_gint(x, g);

            if (ggint_equal(x, _1))
                return false;

            if (ggint_equal(x, n_1))
                break;
        }

        if (ggint_equal(x, n_1) == false)
            return false;
    }
    return true;
}
#endif
