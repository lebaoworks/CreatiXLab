#include <stdio.h>
#include <stdlib.h>

int main()
{
    int on[10] = {0,0,0,0,0,0,0,0,0};
    int input_int, i, j;
    printf("Input: ");
    scanf("%d",&input_int);
    for(;input_int; input_int/=10)
        on[input_int%10]++;
    for (i=9; i>=0; i--)
        for (j=0; j<on[i]; j++)
            printf("%d",i);
    return 0;
}
