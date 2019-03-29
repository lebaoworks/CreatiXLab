#include <stdio.h>
#include <stdlib.h>


int main()
{
    int price = 0;
    int m;
    int countdown;
    printf("Input: ");
    scanf("%d",&m);
    if (m>0)
    {
        price=10000;
        m-=1000;
    }
    if (m>0)
        for (countdown=29000; countdown!=0 && m>0; countdown-=200,m-=200)
            price+=1500;
    if (m>0)
        for (; m>0; m-=1000)
            price+=8000;
    printf("%d",price);
    getchar();
    return 0;
}
