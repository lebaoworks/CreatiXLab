#include <stdio.h>
#include <stdlib.h>

int remove_double_space(char *str)
{
    int len = strlen(str);
    if (!len)
        return 0;
    int i,j;
    for (i=1,j=0; i<=len; i++)
        if (!(str[i]==str[j] && str[j]==' '))
            str[++j]=str[i];
}
int remove_space_before(char *str)
{
    int len = strlen(str);
    if (!len)
        return 0;
    int i,j;
    for (i=1,j=0; i<=len; i++)
        if (!(str[j]==' ' && (str[i]==',' || str[i]=='.')))
            str[++j]=str[i];
        else
            str[j]=str[i];
}
int remove_double_comma(char* str)
{
    int len = strlen(str);
    if (!len)
        return 0;
    int i,j;
    for (i=1,j=0; i<=len; i++)
        if (!(str[i]==str[j] && str[j]==','))
            str[++j]=str[i];
}
int remove_double_dot(char* str)
{
    int len = strlen(str);
    if (!len)
        return 0;
    int i,j;
    for (i=1,j=0; i<=len; i++)
        if (!(str[i]==str[j] && str[j]=='.'))
            str[++j]=str[i];
}
int trim(char* str)
{
    int len = strlen(str);
    if (!len)
        return 0;
    int t,b;
    for (t=0; t<len && str[t]==' '; t++)
        ;
    memcpy(str,str+t,len-t+1);
    for (b=strlen(str)-1; b>=0 && str[b]==' '; b--)
        str[b]=0;
}
int add_space(char* str)
{
    char buffer[500];
    int i,j;
    int len=strlen(str);
    for (i=0,j=0; i<=len; i++,j++)
    {
        buffer[j]=str[i];
        if ((str[i]==',' || str[i]=='.') && str[i+1]!=' ')
            buffer[++j]=' ';
    }
    memcpy(str,buffer,strlen(buffer)+1);
}
int main()
{
    char buffer[500];
    printf("Input: ");
    scanf("%[^\n]%*c",buffer);
    remove_double_space(buffer);
    remove_space_before(buffer);
    remove_double_comma(buffer);
    remove_double_dot(buffer);
    add_space(buffer);
    trim(buffer);
    printf("%s",buffer);
    getchar();
    return 0;
}
