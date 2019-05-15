#ifndef __LARGEINT_SET__
#define __LARGEINT_SET__

#include "LargeInt_Conf.h"
#include <string.h>

// a = 0
void li_set_zero(li a)
{
    memset(a, 0, LI_Size);
}
// a = b
void li_set_int(uin b, li a)
{
    li_set_zero(a);
    for (ii i=0; i<LI_Size && b>0; i++)
    {
        a[i] = b % LI_Base;
        b /= LI_Base;
    }
}
// a = b
void li_set_li(li b, li a)
{
    memcpy(a, b, LI_Size);
}

#endif
