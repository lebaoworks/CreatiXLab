#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef __LargeInteger__
#define __LargeInteger__

#ifndef min(a,b)
#define min(a,b) (a<b)?a:b
#endif

#ifndef max(a,b)
#define max(a,b) (a>b)?a:b
#endif

#define bool uint8_t
#define true 1
#define false 0
#define u8 uint8_t
#define i8 int8_t
#define u16 uint16_t
#define ii int16_t

#define LI_Size 128
#define LI_Base 256
#define LI_Bits 8


typedef uint8_t li[LI_Size];

li li_cache[LI_Base+1];
bool li_cache_empty = true;
li li_lastnum;

/*
    Compare
*/
// a == b
bool li_equal(const li a, const li b)
{
    for (ii i=0; i<LI_Size; i++)
        if (a[i] != b[i])
            return false;
    return true;
}
// a < b
bool li_less(const li a, const li b)
{
    for (ii i=LI_Size-1; i>=0; i--)
    {
        if (a[i]<b[i])
            return true;
        if (a[i]>b[i])
            return false;
    }
    return false;
}
// a <= b
bool li_less_equal(const li a, const li b)
{
    for (ii i=LI_Size-1; i>=0; i--)
    {
        if (a[i]<b[i])
            return true;
        if (a[i]>b[i])
            return false;
    }
    return true;
}
/*
    Check Special Value
*/
bool li_is_zero(const li a)
{
    for (ii i=0; i<LI_Size; i++)
        if (a[i]!=0)
            return false;
    return true;
}
bool li_is_even(const li a)
{
    return !(a[0]&1);
}
bool li_is_odd(const li a)
{
    return a[0]&1;
}
/*
    Set Value
*/
// a = 0
void li_set_zero(li a)
{
    memset(a,0,LI_Size);
}
// a = b
void li_set_int(const u8 b, li a)
{
    li_set_zero(a);
    a[0] = b;
}
// a = b
void li_set_li(const li b, li a)
{
    memcpy(a,b,LI_Size);
}
/*
    Digit Operations
*/
// a <<= LI_Bits*sh (Shift digits)
void li_shl(li a, const u8 sh)
{
    if (!sh)
        return;
    u8 shift = min(sh,LI_Size);
    for (ii i=LI_Size-1; i>=0; i--)
        a[i] = a[i - shift];
    for (ii i=0; i<shift; i++)
        a[i] = 0;
}
// a >>= LI_Bits*sh (Shift digits)
void li_shr(li a, const u8 sh)
{
    if (!sh)
        return;
    u8 shift = min(sh,LI_Size);
    for (ii i=0; i<LI_Size - shift; i++)
        a[i] = a[i + shift];
    for (ii i=0; i<shift; i++)
        a[LI_Size - 1 - i] = 0;
}
// a <<= sh (Shift bits)
void li_shbl(li a, const u8 sh)
{
    if (!sh)
        return;
    li_shl(a, sh / LI_Bits);
    u8 shift = sh % LI_Bits;
    u16 mask = LI_Base - (1 << (LI_Bits - shift));
    u8 bits_0 = 0, bits_1 = 0;
    for (ii i=0; i<LI_Size; i++)
    {
        bits_1 = a[i] & mask;
        a[i] <<= shift;
        a[i] |= bits_0 >> (LI_Bits - shift);
        bits_0 = bits_1;
    }
}
// a >>= sh (Shift bits)
void li_shbr(li a, const u8 sh)
{
    if (!sh)
        return;
    li_shr(a, sh / LI_Bits);
    u8 shift = sh % LI_Bits;
    u16 mask = (1<<shift) - 1;
    u8 bits_0 = 0, bits_1 = 0;
    for (ii i=LI_Size-1; i>=0; i--)
    {
        bits_1 = a[i] & mask;
        a[i] >>= shift;
        a[i] |= bits_0 << (LI_Bits - shift);
        bits_0 = bits_1;
    }
}
/*
    Math
*/
// a = a + b
void li_add_int(const u8 b, li a)
{
    ii x = b;
    for (ii i=0; i<LI_Size; i++)
    {
        x += a[i];
        a[i] = x % LI_Base;
        x /= LI_Base;
        if (x==0)
            break;
    }
}
// a = a + b
void li_add_li(const li b, li a)
{
    ii x = 0;
    for (ii i=0; i<LI_Size; i++)
    {
        x = x + b[i] + a[i];
        a[i] = x % LI_Base;
        x /= LI_Base;
    }
}
// a = a - b
void li_sub_int(const u8 b, li a)
{
    ii r = b;
    for (ii i=0; i<LI_Size; i++)
        if (a[i]<r)
        {
            a[i] = -r + a[i] + LI_Base;
            r = 1;
        }
        else
        {
            a[i] -= r;
            r = 0;
        }
}
// a = a - b
void li_sub_li(const li b, li a)
{
    ii r = 0;
    for (ii i=0; i<LI_Size; i++)
        if (a[i]<r+b[i])
        {
            a[i] = (ii) a[i] + LI_Base - b[i] - r;
            r = 1;
        }
        else
        {
            a[i] -= r + b[i];
            r = 0;
        }
}
// a = a * b
void li_mul_int(const u8 b, li a)
{
    u16 r = 0;
    for (ii i=0; i<LI_Size; i++)
    {
        r += (u16)b * a[i];
        a[i] = r % LI_Base;
        r /= LI_Base;
    }
}
// a = a * b
void li_mul_li(const li b, const li a, li p)
{
    li t;
    li_set_zero(p);
    for (ii i=0; i<LI_Size; i++)
    {
        li_set_li(a,t);
        li_mul_int(b[i],t);
        li_shl(t,i);
        li_add_li(t,p);
    }
}
// c = a / b
// d = a % b
void li_div_li(const li b, const li a, li c, li d)
{
    li_set_zero(c);
    li_set_zero(d);
    li t;
    li_set_zero(t);
    for (ii i=LI_Size-1; i>=0; i--)
    {
        li_shl(d, 1);
        li_add_int(a[i], d);
        if (li_less_equal(b, d))
        {
            li_set_zero(t);
            u8 k = 0;
            do
            {
                k++;
                li_add_li(b, t);
            }
            while (li_less_equal(t, d));
            c[i] = k-1;
            li_sub_li(b,t);
            li_sub_li(t,d);
        }
        else
        {
            c[i] = 0;
        }
    }
}
// c = a % b
void li_mod_li(const li b, const li a, li c)
{
    if (li_less(a,b))
    {
        li_set_li(c,a);
        return;
    }

    li_set_zero(c);
    li t;
    
    //Init Cache
    if (li_cache_empty || li_equal(b, li_lastnum) == false)
    {
        li_set_zero(t);
        for (ii k=0; k<LI_Base; k++)
        {
            li_set_li(t,li_cache[k]);
            li_add_li(b,t);
        }
        li_set_li(li_lastnum,b);
    }

    for (ii i=LI_Size-1; i>=0; i--)
    {
        li_shl(c,1);
        li_add_int(a[i], c);

        if (li_less_equal(b,c))
        {
            if (li_less_equal(li_cache[LI_Base-1], c))
                li_sub_li(li_cache[LI_Base - 1],c);
            else
            {
                u16 k0 = 0, k1 = LI_Base;
                while (true)
                {
                    u16 m = (k0 + k1) >> 1;
                    if (li_less_equal(li_cache[m], c))
                        k0 = m;
                    else
                        k1 = m;
                    if (k1 == k0 + 1)
                        break;
                }
                li_sub_li(li_cache[k0], c);
            }
        }
    }
}
// c = a % b
void li_mod_int(const u8 b, const li a, u8* c)
{
    *c = 0;
    for (ii i=LI_Size-1; i>=0; i--)
        *c = (*c*LI_Base + a[i])%b;
}
// r = a^x mod n
void li_pow_mod(const li a, const li x, const li n, li r)
{
    li t,q;
    li_set_int(1,r);
    li_set_zero(t);
    li_set_li(x,q);

    while (li_is_zero(q) == false)
    {
        if (li_is_odd(q))
        {
            li_mul_li(a,r,t);
            li_mod_li(n,t,r);
        }
        li_shbr(q,1);
        li_mul_li(a,a,t);
        li_mod_li(n,t,a);
    }
    
}
/*
    Generate random
*/
// random a
void li_rand(li a)
{
    srand(time(0));
    for (ii i=0; i<LI_Size; i++)
        a[i] = rand() % LI_Base;
}
// rand in range(0,b)
void li_rand_range(li a, const li b)
{
    li_rand(a);
    li t,q;
    li_set_li(a,t);
    li_div_li(b,t,q,a);
}
/*
    IO
*/
void li_print_arr(const li a)
{
    for (ii i=LI_Size-1; i>=0; i--)
        printf("%3d",a[i]);
    printf("\n\n");
}
void li_print_bin(const li a)
{
    char str[4096];
    memset(str,0,4096);
    ii n = 0;
    li x,q,r,_10;
    li_set_li(a,x);
    li_set_int(10,_10);

    while (li_is_zero(x) == false)
    {
        li_div_li(_10,x,q,r);
        li_set_li(q,x);
        str[n++] = '0'+r[0];
    }
    if (n == 0)
        str[n++] = '0';
    for (ii i=n-1; i>=0; i--)
        printf("%c",str[i]);
    printf("\n");
}
int main(int argc, char** argv)
{
    li a,b,c,d;
    li_set_int(250,a);
    li_set_int(10,b);
    li_set_int(10,c);
    li_set_int(3,d);
    li_div_li(b,c,a,d);
    li_print_bin(d);
    return 0;
}
#endif