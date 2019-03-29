#include <stdio.h>
#include <stdlib.h>

int replace(char* substr, char* str)
{
    int sublen = strlen(substr);
    int len = strlen(str);
    int i,j;
    for (i=0; i<len; i++)
    {
        for (j=i; j<i+sublen; j++)
            if (str[j]!=substr[j-i])
                break;
        if (j==i+sublen)
        {
            memcpy(str+i,str+i+sublen,len-i-sublen+1);
            return 1;
        }
    }
    return 0;
}
int main()
{
    char buffer[500];
    printf("Input: ");
    scanf("%[^\n]%*c",buffer);
    while (replace("sdf",buffer))
        ;
    printf("%s",buffer);
    return 0;
}
