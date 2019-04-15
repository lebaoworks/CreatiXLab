#include <stdio.h>

#include "linked_list_menu.h"
#include "sorting_menu.h"
#include "path_finding_menu.h"
#include "multiples_11_menu.h"

int main()
{
    main_menu();
    return 0;
}
void main_menu()
{
    do
    {
        //clear screen
        system("cls");
        //print menu
        printf("Select one of the following choices:\n");
        printf("---------------------------\n");
        printf("1/ Linked List.\n");
        printf("2/ Sorting.\n");
        printf("3/ Path Finding.\n");
        printf("4/ Multiples of 11.\n");
        printf("ESC/ Exit.\n");
        printf("---------------------------\n");
        //input
        printf("Select: \n");
        fflush(stdin);

        switch (input_key())
        {
        case '1':
            linked_list_menu();
            break;
        case '2':
            sorting_menu();
            break;
        case '3':
            path_finding_menu();
            break;
        case '4':
            multiples_11_menu();
            break;
        case esc:
            return;
        }
    }
    while (1);
}

