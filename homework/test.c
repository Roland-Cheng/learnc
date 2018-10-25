#include<stdio.h>
int main ()
{
    unsigned short x,n,y;
    int i;
    scanf ("%s%s", x, n);
    for (i=n ;i>= 0;i--){
    y = x<<15 | x>>1;
    printf("%d",x);
    }
    return 0;
}