#include <stdio.h>
#include <windows.h>

#include "multiples_11.h"
#include "input.h"

void multiples_11_menu()
{
    int n;
    do
    {
        //clear screen
        system("cls");
        printf("Number of digits: %d\n",n);
        printf("---------------------------\n");
        //print menu
        printf("Select one of the following choices:\n");
        printf("---------------------------\n");
        printf("1/ Input number of digits.\n");
        printf("Enter/ Print multiples of 11.\n");
        printf("ESC/ Back to main menu.\n");
        printf("---------------------------\n");
        //input
        printf("Select: \n");
        fflush(stdin);

        switch (input_key())
        {
        case '1':
            multiples_11_input_menu(&n);
            break;
        case enter:
            multiples_11(n);
            input_key();
            break;
        case esc:
            return;
        }
    }
    while (1);
}
void multiples_11_input_menu(int *n)
{
    //clear screen
    system("cls");

    char x = 0;
    printf("Input number of digits: ");
    while ((x<'0' || x>'9') && x!=esc)
        x = input_key();

    if (x!= esc)
        *n = x - '0';
}
