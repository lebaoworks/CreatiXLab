#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------//
//-------------------Declare Data Types-------------------//
//--------------------------------------------------------//
typedef struct SINGLE_NODE_DATA
{
    int value;
    struct SINGLE_NODE_DATA* next;
} SINGLE_NODE;
typedef struct DOUBLE_NODE_DATA
{
    int value;
    struct DOUBLE_NODE_DATA* next;
    struct DOUBLE_NODE_DATA* prev;
} DOUBLE_NODE;
typedef struct CIRCULAR_NODE_DATA
{
    int value;
    struct CIRCULAR_NODE_DATA* next;
} CIRCULAR_NODE;

//--------------------------------------------------------//
//----------------------Declare Data----------------------//
//--------------------------------------------------------//
SINGLE_NODE single_start;
DOUBLE_NODE double_start;
CIRCULAR_NODE circular_start;

//--------------------------------------------------------//
//-------------------Declare Functions--------------------//
//--------------------------------------------------------//
SINGLE_NODE* single_add(int value, int pos)
{
    //Seek to pos-1
    SINGLE_NODE* this_node = &single_start;
    while (this_node->next && pos>0)
    {
        pos--;
        this_node = this_node->next;
    }
    if (pos!=0) //pos out of list range
        return 0;

    //Make a node
    SINGLE_NODE* new_node = malloc(sizeof(SINGLE_NODE));
    new_node->value = value;
    //Link the node
    new_node->next = this_node->next;
    this_node->next = new_node;
    //Increase number of nodes
    single_start.value++;

    //return new_node address
    return this_node;
}
int single_remove(int pos)
{
    //Seek to pos-1
    SINGLE_NODE* this_node = &single_start;
    while (this_node->next && pos>0)
    {
        pos--;
        this_node = this_node->next;
    }
    if (pos!=0) //pos out of list range
        return 0;
    if (this_node->next == 0) //last node
        return 0;
    //Link the node
    this_node->next = this_node->next->next;
    //Decrease number of nodes
    single_start.value--;
    return 1;
}
int single_mod(int value, int pos)
{
    //Seek to pos
    SINGLE_NODE* this_node = &single_start;
    while (this_node->next && pos>0)
    {
        pos--;
        this_node = this_node->next;
    }
    if (pos!=0) //pos out of list range
        return 0;
    if (this_node->next == 0) //last node
        return 0;
    this_node = this_node->next;

    //Modify value
    this_node->value = value;
    return 1;
}
void single_print()
{
    SINGLE_NODE* this_node = &single_start;
    int i=0;
    printf("\n---Single List---\n");
    printf("Number of elements: %d\n", single_start.value);
    while (this_node->next)
    {
        this_node = this_node->next;
        printf("At %p: list[%d] = %d\n",this_node, i, this_node->value);
        i++;
    }
}

DOUBLE_NODE* double_add(int value, int pos)
{
    //Seek to pos-1
    DOUBLE_NODE* this_node = &double_start;
    while (this_node->next && pos>0)
    {
        pos--;
        this_node = this_node->next;
    }
    if (pos!=0) //pos out of list range
        return 0;

    //Make a node
    DOUBLE_NODE* new_node = malloc(sizeof(DOUBLE_NODE));
    new_node->value = value;
    //Link the node
    DOUBLE_NODE* node_prev = this_node;
    DOUBLE_NODE* node_next = this_node->next;

    node_prev->next = new_node;
    new_node->next = node_next;

    if (node_next) //exist next node
        node_next->prev = new_node;
    new_node->prev = node_prev;

    //Increase number of nodes
    double_start.value++;

    //return new_node address
    return this_node;
}
int double_remove(int pos)
{
    //Seek to pos-1
    DOUBLE_NODE* this_node = &double_start;
    while (this_node->next && pos>0)
    {
        pos--;
        this_node = this_node->next;
    }
    if (pos!=0) //pos out of list range
        return 0;
    if (this_node->next == 0) //last node
        return 0;

    //Link the node
    DOUBLE_NODE* node_to_remove = this_node->next;
    if (!node_to_remove) //not exist
        return 0;

    if (node_to_remove->next) //exist next node
        node_to_remove->next->prev = this_node;
    this_node->next = node_to_remove->next;

    //Decrease number of nodes
    double_start.value--;
    return 1;
}
int double_mod(int value, int pos)
{
    //Seek to pos
    DOUBLE_NODE* this_node = &double_start;
    while (this_node->next && pos>0)
    {
        pos--;
        this_node = this_node->next;
    }
    if (pos!=0) //pos out of list range
        return 0;
    if (this_node->next == 0) //last node
        return 0;
    this_node = this_node->next;

    //Modify value
    this_node->value = value;
    return 1;
}
void double_print()
{
    DOUBLE_NODE* this_node = &double_start;
    int i=0;
    printf("\n---Double List---\n");
    printf("Number of elements: %d\n", double_start.value);
    while (this_node->next)
    {
        this_node = this_node->next;
        printf("At %p: list[%d] = %d\n",this_node, i, this_node->value);
        i++;
    }
}


CIRCULAR_NODE* circular_add(int value, int pos)
{
    //Seek to pos-1
    CIRCULAR_NODE* this_node = &circular_start;
    while (this_node->next && pos>0)
    {
        pos--;
        this_node = this_node->next;
    }
    if (pos!=0) //pos out of list range
        return 0;

    //Make a node
    CIRCULAR_NODE* new_node = malloc(sizeof(CIRCULAR_NODE));
    new_node->value = value;
    //Link the node
    new_node->next = this_node->next;
    this_node->next = new_node;
    if (circular_start.value == 0)
        new_node->next = new_node;
    //Increase number of nodes
    circular_start.value++;

    //return new_node address
    return this_node;
}
int circular_remove(int pos)
{
    if (pos >= circular_start.value)
        return 0;
    if (pos == 0 && circular_start.value == 1)
    {
        circular_start.next = 0;
        circular_start.value--;
        return 1;
    }
    //Seek to pos-1
    CIRCULAR_NODE* this_node = &circular_start;
    while (this_node->next && pos>0)
    {
        pos--;
        this_node = this_node->next;
    }
    //Link the node
    this_node->next = this_node->next->next;
    //Decrease number of nodes
    circular_start.value--;
    return 1;
}
int circular_mod(int value, int pos)
{
    if (pos >= circular_start.value)
        return 0;
    //Seek to pos
    CIRCULAR_NODE* this_node = &circular_start;
    while (this_node->next && pos>0)
    {
        pos--;
        this_node = this_node->next;
    }
    this_node = this_node->next;

    //Modify value
    this_node->value = value;
    return 1;
}
void circular_print()
{
    CIRCULAR_NODE* this_node = &circular_start;
    int i=0;
    printf("\n---Circular List---\n");
    printf("Number of elements: %d\n", circular_start.value);
    while (i<circular_start.value)
    {
        this_node = this_node->next;
        printf("At %p: list[%d] = %d\n",this_node, i, this_node->value);
        i++;
    }
}

//--------------------------------------------------------//
//--------------------------Main--------------------------//
//--------------------------------------------------------//
int main()
{
    single_add(4,0);
    single_add(5,0);
    single_remove(2);
    single_mod(2,1);
    single_print();

    double_add(4,0);
    double_add(5,0);
    double_remove(2);
    double_mod(2,1);
    double_print();

    circular_add(4,0);
    circular_add(5,0);
    circular_remove(2);
    circular_mod(2,1);
    circular_print();

    getchar();
    return 0;
}
