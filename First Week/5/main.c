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
    if (d<1 || m<1 || y<1)
        out();
    if (m==2)
    {
        if (y%4==0)
            if (d<30)
                printf("Nam nhuan");
            else
                out();
        else
            if (d<29)
                printf("Khong phai nam nhuan");
    }
    else
        if (d<=c[m])
            if (y%4==0)
                printf("Nam nhuan");
            else
                printf("Khong phai nam nhuan");
        else
            out();
    getchar();

    return 0;
}
