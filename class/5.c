#include<stdio.h>
int main()
{
    int x;
    unsigned int a, b, c, d;
    scanf("%d",&x);
    a = x>>24;
    b = x<<8;
    b = b>>24;
    c = x<<16;
    c = c>>24;
    d = x<<24;
    d = d>>24;
    printf ("%d.%d.%d.%d",d,c,b,a);
}