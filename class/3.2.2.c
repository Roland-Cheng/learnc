#include "stdio.h"
double sum_fac(int n);
int main(void)
{
    int k, n;
    scanf("%d",&n);
    for(k=1;k<=n;k++)
         printf("k=%d\tthe sum is %lf\n",k,sum_fac(k));
}
double sum_fac(int n)
{
    int i;
    double fac;
    if(n == 1) return 1;
    for(i=1,fac=1;i<=n;i++)
        fac*=i;
    fac = 1/fac;
    fac+=sum_fac(n-1);
    return fac;
}
