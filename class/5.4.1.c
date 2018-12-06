#include<stdio.h>
#define p 3
#define q 4

int main()
{
    int s[p][q] ={0};
    int k, n;
    for(k = 0;k<p;k++)
    {
        for(n = 0;n<q;n++) scanf("%d",&s[k][n]);
        getchar();
    }
    for(k = 0;k<p;k++)
    {
        for(n = 0;n<q;n++) printf("%5d",s[k][n]);
        printf ("\n");
    }
    printf("\n");
    int a[q][p]={0};
    for(k = 0;k<p;k++)
    for(n = 0;n<q;n++) a[n][k] = s[k][n];
    for(k = 0;k<q;k++)
    {
        for(n = 0;n<p;n++) printf("%5d",a[k][n]);
        printf("\n");
    }
}