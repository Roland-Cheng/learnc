#include<stdio.h>
int main()
{
    int x, n, i, d;
    unsigned long a, b;
    scanf ("%d%d",&x,&n);
    d = sizeof (int)*8;
    n = n%d;
    a = x>>n;
    b = x<<(d-n);
    x = a|b;
    printf ("%d\n",x);
    return 0;   
}