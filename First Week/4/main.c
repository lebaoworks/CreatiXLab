#include <stdio.h>
#include <stdlib.h>

int main()
{
    int h, i, j;
    printf("input: ");
    scanf("%d", &h);
    fflush(stdin);
    for (i=0; i<h; i++)
    {
        for (j=0; j<h-i-1; j++)
            printf("   ");
        for (j=0; j<i*2+1; j++)
            printf(" * ");
        printf("\n");
    }
    getchar();

    return 0;
}
