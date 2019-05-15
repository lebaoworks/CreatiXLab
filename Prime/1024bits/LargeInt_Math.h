#ifndef __LARGEINT_MATH__
#define __LARGEINT_MATH__

#include "LargeInt_Conf.h"
#include "LargeInt_Set.h"
#include "LargeInt_Bits.h"
#include "LargeInt_Comp.h"

// res = a + b
void li_add_li(li b, li a, li res)
{
    li _res;
    uin x = 0;
    for (ii i = 0; i < LI_Size; i++)
    {
        x += b[i];
        x += a[i];
        _res[i] = x % LI_Base;
        x /= LI_Base;
    }
    li_set_li(_res, res);
}
// res = a + b
void li_add_int(uin b, li a, li res)
{
    li _res;
    uin x = b;
    for (ii i = 0; i < LI_Size; i++)
    {
        x += a[i];
        _res[i] = x % LI_Base;
        x /= LI_Base;
    }
    li_set_li(_res, res);
}
// res = a - b
void li_sub_li(li b, li a, li res)
{
    li _res;
    uin r = 0;
    for (ii i = 0; i < LI_Size; i++)
        if (a[i] < b[i] + r)
        {
            _res[i] = LI_Base - b[i] - r + a[i];
            r = 1;
        }
        else
        {
            _res[i] = a[i] - b[i] - r;
            r = 0;
        }
    li_set_li(_res, res);
}
// res = a - b
void li_sub_int(uin b, li a, li res)
{
    li _res;
    uin r = b;
    for (ii i = 0; i < LI_Size; i++)
        if (a[i] < r % LI_Base)
        {
            _res[i] = LI_Base - r % LI_Base + a[i];
            r = r / LI_Base + 1;
        }
        else
        {
            _res[i] = a[i] - r % LI_Base;
            r /= LI_Base;
        }
    li_set_li(_res,res);
}
// res = a * b
void li_mul_int(uin b, li a, li res)
{
    li _res;
    uin r = 0;
    for (ii i = 0; i < LI_Size; i++)
    {
        r += (uin)b * a[i];
        _res[i] = r % LI_Base;
        r /= LI_Base;
    }
    li_set_li(_res, res);
}
// res = a * b
void li_mul_li(li a, li b, li res)
{
    li _res, t;
    li_set_zero(_res);
    for (ii i = 0; i < LI_Size; i++)
    {
        li_mul_int(a[i], b, t);
        li_shl(t, i);
        li_add_li(t, _res, _res);
    }
    li_set_li(_res, res);
}
// c = a / b, d = a % b
void li_div_li(li b, li a, li c, li d)
{
    li_set_zero(c);
    li_set_zero(d);
    li t;
    for (ii i = LI_Size - 1; i >= 0; i--)
    {
        li_shl(d, 1);
        li_add_int(a[i], d, d);
        if (li_less_equal_li(b, d))
        {
            li_set_zero(t);
            uin k = 0;
            do
            {
                k++;
                li_add_li(b, t, t);
            } while (li_less_equal_li(t, d));
            c[i] = k - 1;
            li_sub_li(b, t, t);
            li_sub_li(t, d, d);
        }
        else
            c[i] = 0;
    }
}
// c = a % b
void li_mod_li(li b, li a, li c)
{
    li d;
    li_div_li(b,a,d,c);
}
// return a % b
uin li_mod_int(uin b, li a)
{
    uin _res = 0;
    for (ii i=LI_Size -1; i>=0; i--)
        _res = (_res*LI_Base + a[i]) % b;
    return _res;
}
// res = a^x mod n
void li_pow_mod(li a, li x, li n, li res)
{
    li t, _a, _x, _res;
    li_set_li(a,_a);
    li_set_li(x,_x);
    li_set_int(1,_res);
    li_set_zero(t);

    while (!li_equal_int(0,_x))
    {
        if (li_is_odd(_x))
        {
            li_mul_li(_a,_res,t);
            li_mod_li(n, t,_res);
        }
        li_shbr(_x,1);
        li_mul_li(_a,_a,t);
        li_mod_li(n,t,_a);
    }
    li_set_li(_res,res);
}
#endif