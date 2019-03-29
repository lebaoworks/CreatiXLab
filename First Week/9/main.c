#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,k;
    int n,m;
    int a[500][500];
    int b[500];
    int c[500];
    memset(c,0,500);

    printf("M=");
    scanf("%d",&m);
    printf("N=");
    scanf("%d",&n);
    printf("A:\n");
    for (i=0; i<m; i++)
        for (j=0; j<n; j++)
            scanf("%d",&a[i][j]);
    printf("X:\n");
    for (i=0; i<n; i++)
        scanf("%d",&b[i]);
    for (i=0; i<m; i++)
        for (j=0; j<n; j++)
            c[i] += a[i][j]*b[j];
    for (i=0; i<m; i++)
        printf("%d\n",c[i]);

    getchar();
    return 0;
}
