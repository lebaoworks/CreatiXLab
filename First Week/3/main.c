//input distance (meters)
//first 1000 meters costs 10000
//until 30th kilometer, each 200 meters costs 1500
//after 30th kilometer, each 1000 meters costs 8000
//print total cost
#include <stdio.h>
#include <stdlib.h>


int main()
{
    int price = 0;
    int m;
    int countdown;
	
    printf("Input: ");
    scanf("%d",&m);
	
	//first 1000 meters
    if (m>0)
    {
        price=10000;
        m-=1000;
    }
	//until 30th kilometer
    if (m>0)
        for (countdown=29000; countdown!=0 && m>0; countdown-=200,m-=200)
            price+=1500;
	//the rest
    if (m>0)
        for (; m>0; m-=1000)
            price+=8000;
		
    printf("%d",price);
    getchar();
    return 0;
}
