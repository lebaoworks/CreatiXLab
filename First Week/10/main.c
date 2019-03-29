//input a string, remove "sdf" until there is not "sdf" in the string
#include <stdio.h>
#include <stdlib.h>

int remove(char* substr, char* str)
{
    int sublen = strlen(substr);
    int len = strlen(str);
    int i,j;
	
    for (i=0; i<len; i++)
    {
        for (j=i; j<i+sublen; j++) //check if "sdf" starts from i
            if (str[j]!=substr[j-i])
                break;
        if (j==i+sublen) // if "sdf" starts from i
        {
			//replace from i by i+sublen
            memcpy(str+i, str+i+sublen, len-i-sublen+1);
            return 1;
        }
    }
    return 0; //there is not "sdf" in the string
}
int main()
{
    char buffer[500];
	
    printf("Input: ");
    scanf("%[^\n]%*c",buffer);
	
    while (remove("sdf",buffer))
        ;
	
    printf("%s",buffer);
    return 0;
}
