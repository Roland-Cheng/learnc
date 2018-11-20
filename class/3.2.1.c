#include<stdio.h>
long sum(int n);
int main()
{
    int n, i;
    scanf("%d",&n);
    for (i = 1;i <= n;i++)
    printf("k=%d\tthe sum is %ld\n",i,sum(i));
}

long sum(int n)
{
    static long s,fac = 1;
    fac*=n;
    s+=fac;
    return s;
}
