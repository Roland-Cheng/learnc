#include<stdio.h>
int main()
{
    unsigned short x, m, n;
    printf("Please intput number:");
    scanf("%hd%hd%hd", &x, &m, &n);
    x = x >> m;
    x = x << (16-n);

    printf ("%d", x);
} 