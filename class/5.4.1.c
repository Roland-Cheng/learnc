#include<stdio.h>

int main()
{
    int s[3][4] ={0};
    int k, n;
    for(k = 0;k<3;k++)
    {
        for(n = 0;n<4;n++) scanf("%d",&s[k][n]);
        getchar();
    }
    for(k = 0;k<3;k++)
    {
        for(n = 0;n<4;n++) printf("%5d",s[k][n]);
        printf ("\n");
    }
    printf("\n");
    int a[4][3]={0};
    for(k = 0;k<3;k++)
    for(n = 0;n<4;n++) a[n][k] = s[k][n];
    for(k = 0;k<4;k++)
    {
        for(n = 0;n<3;n++) printf("%5d",a[k][n]);
        printf("\n");
    }
}