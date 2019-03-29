//Input a word and print number of upcase-characters, number of lowcase-characters
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char x[200];
    int i,u=0,l=0;
	
    scanf("%s",x);
    fflush(stdin);
	
    for (i=0; x[i]!=0; i++)
    {
        if ('A'<=x[i] && x[i]<='Z')
            u++;
        if ('a'<=x[i] && x[i]<='z')
            l++;
    }
	
    printf("So ki tu hoa: %d\n",u);
    printf("So ki tu thuong: %d\n",l);
    getchar();
    return 0;
}
