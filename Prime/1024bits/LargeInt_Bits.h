#ifndef __LARGEINT_BITS__
#define __LARGEINT_BITS__

#include "LargeInt_Conf.h"

//a = a << 8*sh (base 256)
void li_shl(li a, uin sh)
{
    if (sh == 0)
        return;
    
    // sh = min(sh, LI_Size)
    if (sh>LI_Size)
        sh = LI_Size;

    for (ii i = LI_Size - 1; i >= sh; i--)
        a[i] = a[i - sh];

    for (ii i = 0; i < sh; i++)
        a[i] = 0;
}
//a = a >> 8*sh (base 256)
void li_shr(li a, uin sh)
{
    if (sh == 0)
        return;
        
    // sh = min(sh, LI_Size)
    if (sh>LI_Size)
        sh = LI_Size;

    for (ii i = 0; i < LI_Size - sh; i++)
        a[i] = a[i + sh];

    for (ii i = 0; i < sh; i++)
        a[LI_Size - 1 - i] = 0;
}
//a = a >> sh
void li_shbr(li a, uin sh)
{
    if (sh == 0)
        return;
    
    li_shr(a, sh / LI_Bits);
    sh = sh % LI_Bits;
    
    for (ii i=0; i<LI_Size-1; i++)
    {
        a[i] >>= sh;
        a[i] |= a[i+1]<<(LI_Bits - sh);
    }
    a[LI_Size-1] >>= sh;
}
// a = a << sh
void li_shbl(li a, uin sh)
{
    if (sh == 0)
        return;

    li_shl(a, sh / LI_Bits);
    sh = sh % LI_Bits;

    for (ii i=LI_Size-1; i>0; i--)
    {
        a[i] <<= sh;
        a[i] |= a[i-1]>>(LI_Bits - sh);
    }
    a[0] <<= sh;
}

#endif