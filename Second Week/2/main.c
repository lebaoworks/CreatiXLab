#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int* array, int n)
{
    //init buffer
    int buffer[n];
    memcpy(buffer,array,n*sizeof(int));

    int i,j,k;
    //sorting
    for (i=0; i<n-1; i++)
        for (j=0; j<n-i-1; j++)
            //arr[j] > arr[j+1] -> swap
            if (buffer[j]>buffer[j+1])
            {
                k = buffer[j];
                buffer[j] = buffer[j+1];
                buffer[j+1] = k;
            }

    printf("\nBubble Sort: ");
    for (i=0; i<n; i++)
        printf("%d ",buffer[i]);
}
void insertion_sort(int* array, int n)
{
    //init buffer
    int buffer[n];
    memcpy(buffer,array,n*sizeof(int));

    int i,j,l,r,h;
    //sorting
    for (i=0; i<n; i++)
    {
        //binary search
        l = 0;
        r = i;
        while (l!=r)
        {
            h = (l+r) >> 1;
            if (buffer[h]<buffer[i])
                l = h+1;
            else
                r = h;
        }
        //insert
        r = buffer[i]; //save value
        for (j=i; j>l; j--)
            buffer[j] = buffer[j-1];
        buffer[l] = r;
    }

    printf("\nInsertion Sort: ");
    for (j=0; j<n; j++)
        printf("%d ",buffer[j]);

}
void selection_sort(int* array, int n)
{
    //init buffer
    int buffer[n];
    memcpy(buffer,array,n*sizeof(int));

    int i,j,min,k;
    //sorting
    for (i=0; i<n; i++)
    {
        //select min
        min=i;
        for (j=i+1; j<n; j++)
            if (buffer[j]<buffer[min])
                min = j;
        //swap with min
        k = buffer[i];
        buffer[i] = buffer[min];
        buffer[min] = k;
    }

    printf("\nSelection Sort: ");
    for (i=0; i<n; i++)
        printf("%d ",buffer[i]);
}
int main()
{
    int n, i;
    int array[500];

    printf("Input N: ");
    scanf("%d",&n);
    for (i=0; i<n; i++)
        scanf("%d",array+i);

    bubble_sort(array,n);
    insertion_sort(array,n);
    selection_sort(array,n);

	getchar();
    return 0;
}
