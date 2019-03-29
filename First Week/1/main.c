//Input an integer and print out its digit(s) in ascending order//
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int on[10] = {0,0,0,0,0,0,0,0,0};
    int input_int, i, j;
    printf("Input: ");
    scanf("%d",&input_int);
	
	while (input_int)
	{
		on[input_int%10]++;		//increase the frequency of unit digit
		input_int/=10;			//remove unit digit
	}
        
    for (i=9; i>=0; i--)
        for (j=0; j<on[i]; j++) //print digit i, on[i] time(s)
            printf("%d",i);
    return 0;
}
