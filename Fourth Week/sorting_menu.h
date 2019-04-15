#include <stdio.h>
#include <windows.h>
#include "sorting.h"
#include "input.h"

void sorting_menu()
{
    int n = 0;
    int *arr;
    do
    {
        //clear screen
        system("cls");
        sorting_print_array(arr, n);
        //print menu
        printf("Select one of the following choices:\n");
        printf("---------------------------\n");
        printf("1/ Input Array.\n");
        printf("2/ Bubble Sort.\n");
        printf("3/ Insertion Sort.\n");
        printf("4/ Selection Sort.\n");
        printf("ESC/ Back to main menu.\n");
        printf("---------------------------\n");
        //input
        printf("Select: \n");
        fflush(stdin);

        switch (input_key())
        {
        case '1':
            input_sorting(&arr, &n);
            break;
        case '2':
            bubble_sort(arr, n);
            input_key();
            break;
        case '3':
            insertion_sort(arr, n);
            input_key();
            break;
        case '4':
            selection_sort(arr, n);
            input_key();
            break;
        case esc:
            return;
        }
    }
    while (1);
}
void sorting_print_array(int *arr, int n)
{
    printf("Array: ");
    for (int i=0; i<n; i++)
        printf("%d ",arr[i]);
    printf("\n");
}
