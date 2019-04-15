#include <conio.h>

#ifndef INPUT
#define INPUT

#define esc 27
#define enter 13

char input_key()
{
    fflush(stdin);
    char input = 0;
    while (!input)
        if (kbhit())
            input = getch();
    return input;
}
int input_int(int *x)
{
    int a=0;
    char c = input_key();
    while (c != enter)
    {
        if (c>='0' && c<='9')
        {
            printf("%c",c);
            a = a*10 + c-'0';
        }
        if (c == esc)
            return 0;
        c = input_key();
    }
    *x = a;
    printf("\n");
    return 1;
}
#endif
