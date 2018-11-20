#include "stdio.h"
long sum_fac(int n);
int main(void)
{
    int k, n;
    scanf("%d",&n);
    for(k=1;k<=n;k++)
         printf("k=%d\tthe sum is %ld\n",k,sum_fac(k));
}
long sum_fac(int n)
{
    long s=0;
    int i;
    long fac;
    //for(j = 1;j<=n;j++)
    //{
    for(i=1,fac=1;i<=n;i++)
        {fac*=i;
    s+=fac;
    }
    return s;
}
