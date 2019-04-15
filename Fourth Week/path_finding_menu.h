#include <stdio.h>
#include <windows.h>
#include "path_finding.h"
#include "input.h"

void path_finding_menu()
{
    do
    {
        //clear screen
        system("cls");
        path_finding_print_result();
        printf("---------------------------\n");
        //print menu
        printf("Select one of the following choices:\n");
        printf("---------------------------\n");
        printf("Enter/ Read data from \"input.txt\" and export to \"output.txt\".\n");
        printf("ESC/ Back to main menu.\n");
        printf("---------------------------\n");
        //input
        printf("Select: \n");
        fflush(stdin);

        switch (input_key())
        {
        case enter:
            path_finding();
            break;
        case esc:
            return;
        }
    }
    while (1);
}
