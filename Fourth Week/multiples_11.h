#include <stdio.h>
#include <stdlib.h>

#ifndef MULTIPLES_11
#define MULTIPLES_11
void multiples_11(int n)
{
    //init data
    int i, limit = 1;

    //init limit
    for (i=0; i<n; i++)
        limit*=10;

    //print
    for (i=11; i<limit; i+=11)
        printf("%d\n",i);
}
#endif // MULTIPLES_11
