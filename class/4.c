#include<stdio.h>
int main()
{
    unsigned short x, m, n, mask;
    printf("Please intput number:");
    scanf("%hd%hd%hd", &x, &m, &n);
    mask = ~0;
    mask = mask >> (16-n);
    mask = mask << m;
    x = x & mask;
    x = x << (16-m-n);

    printf ("%d", x);
}