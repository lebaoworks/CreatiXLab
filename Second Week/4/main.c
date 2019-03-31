#include <stdio.h>
#include <stdlib.h>

int main()
{
    //init data
    int n, i, limit = 1;
    scanf("%d", &n);

    //init limit
    for (i=0; i<n; i++)
        limit*=10;

    //print
    for (i=11; i<limit; i+=11)
        printf("%d\n",i);

    getchar();
    return 0;
}
