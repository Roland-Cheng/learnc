#include<stdio.h>

void putout (long x);
int main()
{
    int n, i;
    scanf ("%d",&n);
    long num[n];
    for (i = 0;i<n;scanf("%ld",&num[i]),putout(num[i++]));
}

void putout (long x)
{
    unsigned long y = 0xf0000000;
    int j;
    for (j=0;j<8;j++)
    {
        printf("%lX",(x&(y>>j*4))>>(28-j*4));
        if (j != 7) putchar(' ');
    }
    printf("\n");
}