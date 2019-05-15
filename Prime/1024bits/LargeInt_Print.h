#ifndef __LARGEINT_PRINT__
#define __LARGEINT_PRINT__

#include <stdio.h>
#include "LargeInt_Conf.h"
#include "LargeInt_Set.h"
#include "LargeInt_Comp.h"
#include "LargeInt_Math.h"

void li_print_arr(li a)
{
    for (ii i = LI_Size - 1; i >= 0; i--)
        printf("%3d", a[i]);
    printf("\n");
}
void li_print_dec(li a)
{
    char str[4096];
    memset(str, 0, 4096);

    ii n = 0;
    li _a, q, r, _10;
    li_set_li(a, _a);
    li_set_int(10, _10);

    while (!li_equal_int(0, _a))
    {
        li_div_li(_10, _a, q, r);
        li_set_li(q, _a);
        str[n++] = '0' + r[0];
    }
    if (n == 0)
        str[n++] = '0';
    for (ii i = n - 1; i >= 0; i--)
        printf("%c", str[i]);
    printf("\n");
}
#endif