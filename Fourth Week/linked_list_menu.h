#include <stdio.h>
#include <windows.h>
#include "linked_list.h"
#include "input.h"

void linked_list_menu()
{
    do
    {
        //clear screen
        system("cls");
        //print menu
        printf("Select one of the following choices:\n");
        printf("---------------------------\n");
        printf("1/ Single Linked List.\n");
        printf("2/ Double Linked List.\n");
        printf("3/ Circular Linked List.\n");
        printf("ESC/ Back to main menu.\n");
        printf("---------------------------\n");
        //input
        printf("Select: \n");
        fflush(stdin);

        switch (input_key())
        {
        case '1':
            single_linked_list_menu();
            break;
        case '2':
            double_linked_list_menu();
            break;
        case '3':
            circular_linked_list_menu();
            break;
        case esc:
            return;
        }
    }
    while (1);
}
void single_linked_list_menu()
{
    do
    {
        //clear screen
        system("cls");
        single_print();
        printf("---------------------------\n");
        //print menu
        printf("Select one of the following choices:\n");
        printf("---------------------------\n");
        printf("1/ Add Element.\n");
        printf("2/ Remove Element.\n");
        printf("3/ Modify Element.\n");
        printf("ESC/ Back to main menu.\n");
        printf("---------------------------\n");
        //input
        printf("Select: \n");
        fflush(stdin);

        switch (input_key())
        {
        case '1':
            single_linked_list_add_menu();
            break;
        case '2':
            single_linked_list_remove_menu();
            break;
        case '3':
            single_linked_list_modify_menu();
            break;
        case esc:
            return;
        }
    }
    while (1);
}
void single_linked_list_add_menu()
{
    //clear screen
    system("cls");
    //print menu
    printf("ESC to skip.\n");
    printf("Input new element value: ");

    int value,pos;
    if (input_int(&value))
    {
        printf("\n----------\n");
        printf("ESC to skip.\n");
        printf("Input position: ");
        if (input_int(&pos))
            if (single_add(value, pos))
            {
                printf("\nSucess.");
                Sleep(200);
                return;
            }
    }
    printf("\nFail.");
    Sleep(200);
}
void single_linked_list_remove_menu()
{
    //clear screen
    system("cls");
    //print menu
    printf("ESC to skip.\n");
    printf("Input position to remove: ");

    int pos;
    if (input_int(&pos))
        if (single_remove(pos))
        {
            printf("\nSucess.");
            Sleep(200);
            return;
        }
    printf("\nFail.");
    Sleep(200);
}
void single_linked_list_modify_menu()
{
    //clear screen
    system("cls");
    //print menu
    printf("ESC to skip.\n");
    printf("Input position to modify: ");

    int value,pos;
    if (input_int(&pos))
    {
        printf("\n----------\n");
        printf("ESC to skip.\n");
        printf("Input new value: ");
        if (input_int(&value))
            if (single_mod(value, pos))
            {
                printf("\nSucess.");
                Sleep(200);
                return;
            }
    }
    printf("\nFail.");
    Sleep(200);
}

void double_linked_list_menu()
{
    do
    {
        //clear screen
        system("cls");
        double_print();
        printf("---------------------------\n");
        //print menu
        printf("Select one of the following choices:\n");
        printf("---------------------------\n");
        printf("1/ Add Element.\n");
        printf("2/ Remove Element.\n");
        printf("3/ Modify Element.\n");
        printf("ESC/ Back to main menu.\n");
        printf("---------------------------\n");
        //input
        printf("Select: \n");
        fflush(stdin);

        switch (input_key())
        {
        case '1':
            double_linked_list_add_menu();
            break;
        case '2':
            double_linked_list_remove_menu();
            break;
        case '3':
            double_linked_list_modify_menu();
            break;
        case esc:
            return;
        }
    }
    while (1);
}
void double_linked_list_add_menu()
{
    //clear screen
    system("cls");
    //print menu
    printf("ESC to skip.\n");
    printf("Input new element value: ");

    int value,pos;
    if (input_int(&value))
    {
        printf("\n----------\n");
        printf("ESC to skip.\n");
        printf("Input position: ");
        if (input_int(&pos))
            if (double_add(value, pos))
            {
                printf("\nSucess.");
                Sleep(200);
                return;
            }
    }
    printf("\nFail.");
    Sleep(200);
}
void double_linked_list_remove_menu()
{
    //clear screen
    system("cls");
    //print menu
    printf("ESC to skip.\n");
    printf("Input position to remove: ");

    int pos;
    if (input_int(&pos))
        if (double_remove(pos))
        {
            printf("\nSucess.");
            Sleep(200);
            return;
        }
    printf("\nFail.");
    Sleep(200);
}
void double_linked_list_modify_menu()
{
    //clear screen
    system("cls");
    //print menu
    printf("ESC to skip.\n");
    printf("Input position to modify: ");

    int value,pos;
    if (input_int(&pos))
    {
        printf("\n----------\n");
        printf("ESC to skip.\n");
        printf("Input new value: ");
        if (input_int(&value))
            if (double_mod(value, pos))
            {
                printf("\nSucess.");
                Sleep(200);
                return;
            }
    }
    printf("\nFail.");
    Sleep(200);
}

void circular_linked_list_menu()
{
    do
    {
        //clear screen
        system("cls");
        circular_print();
        printf("---------------------------\n");
        //print menu
        printf("Select one of the following choices:\n");
        printf("---------------------------\n");
        printf("1/ Add Element.\n");
        printf("2/ Remove Element.\n");
        printf("3/ Modify Element.\n");
        printf("ESC/ Back to main menu.\n");
        printf("---------------------------\n");
        //input
        printf("Select: \n");
        fflush(stdin);

        switch (input_key())
        {
        case '1':
            circular_linked_list_add_menu();
            break;
        case '2':
            circular_linked_list_remove_menu();
            break;
        case '3':
            circular_linked_list_modify_menu();
            break;
        case esc:
            return;
        }
    }
    while (1);
}
void circular_linked_list_add_menu()
{
    //clear screen
    system("cls");
    //print menu
    printf("ESC to skip.\n");
    printf("Input new element value: ");

    int value,pos;
    if (input_int(&value))
    {
        printf("\n----------\n");
        printf("ESC to skip.\n");
        printf("Input position: ");
        if (input_int(&pos))
            if (circular_add(value, pos))
            {
                printf("\nSucess.");
                Sleep(200);
                return;
            }
    }
    printf("\nFail.");
    Sleep(200);
}
void circular_linked_list_remove_menu()
{
    //clear screen
    system("cls");
    //print menu
    printf("ESC to skip.\n");
    printf("Input position to remove: ");

    int pos;
    if (input_int(&pos))
        if (circular_remove(pos))
        {
            printf("\nSucess.");
            Sleep(200);
            return;
        }
    printf("\nFail.");
    Sleep(200);
}
void circular_linked_list_modify_menu()
{
    //clear screen
    system("cls");
    //print menu
    printf("ESC to skip.\n");
    printf("Input position to modify: ");

    int value,pos;
    if (input_int(&pos))
    {
        printf("\n----------\n");
        printf("ESC to skip.\n");
        printf("Input new value: ");
        if (input_int(&value))
            if (circular_mod(value, pos))
            {
                printf("\nSucess.");
                Sleep(200);
                return;
            }
    }
    printf("\nFail.");
    Sleep(200);
}
