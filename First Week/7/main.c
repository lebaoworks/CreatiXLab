//input 2 integers and calculate LCM, BCD
#include <stdio.h>
#include <stdlib.h>

int BCD(int a, int b)
{
    while (a!=b)
        if (a>b)
            a%=b;
        else
            b%=a;
    return a;
}
int LCM(int a, int b)
{
    int bcd = BCD(a,b);
    return a/bcd*b;
}

int main()
{
    int a,b;
	
    printf("Input: ");
    scanf("%d %d",&a,&b);
	
    printf("UCLN: %d\n",BCD(a,b));
    printf("BCNN: %d",LCM(a,b));
    getchar();
    return 0;
}
