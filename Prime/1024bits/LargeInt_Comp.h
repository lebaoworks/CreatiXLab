#ifndef __LARGEINT_COMP__
#define __LARGEINT_COMP__

#include "LargeInt_Conf.h"
#include "LargeInt_Set.h"
#include "bool.h"

// a == b
bool li_equal_li(li b, li a)
{
    for (ii i=0; i<LI_Size; i++)
        if (a[i] != b[i])
            return false;
    return true;
}
// a == b
bool li_equal_int(uin b, li a)
{
    li _b; li_set_int(b, _b);
    return li_equal_li(_b,a);
}
// a <= b
bool li_less_equal_li(li a, li b)
{
    for (ii i = LI_Size - 1; i>=0; i--)
    {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    return true;
}
// a <= b
bool li_less_equal_int(uin a, li b)
{
    li _a; li_set_int(a,_a);
    return li_less_equal_li(_a,b);
}
// a % 2 == 0
bool li_is_even(li a)
{
    return !(a[0]&1);
}
// a % 2 == 1
bool li_is_odd(li a)
{
    return (a[0]&1);
}
#endif