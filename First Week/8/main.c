#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,len;
    char buffer1[500],buffer2[500];
    printf("Input: ");
    scanf("%s",buffer1);
    for (len=0; buffer1[len]!=0; len++)
        ;
    for (i=len-1; i>=0; i--)
        buffer2[len-i-1] = buffer1[i];
    printf("%s",buffer2);
    getchar();
    return 0;
}
