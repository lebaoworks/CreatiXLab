//input day, month and year
//check if the date is valid
//if valid, check if it is a leap year
#include <stdio.h>
#include <stdlib.h>

void out()
{
    printf("Khong hop le.");
    exit(0);
}
int main()
{
    int c[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    int d, m, y;
	
    printf("Ngay: ");
    scanf("%d", &d);
    fflush(stdin);
    printf("Thang: ");
    scanf("%d", &m);
    fflush(stdin);
    printf("Nam: ");
    scanf("%d", &y);
    fflush(stdin);
	
    if (d<1 || m<1 || y<1) //day in range (1,31), month in range (1,12), year in range (1,++)
        out();
    if (m==2)
    {
        if (y%4==0) //is leap year
            if (d<30) //day in range (1,29)
                printf("Nam nhuan");
            else
                out();
        else //is not leap year
            if (d<29) //day in range (1,28)
                printf("Khong phai nam nhuan");
    }
    else
        if (d<=c[m])
            if (y%4==0) //is leap year
                printf("Nam nhuan");
            else
                printf("Khong phai nam nhuan");
        else
            out();
    getchar();

    return 0;
}
