#include<stdio.h>
int main()
{
    int a,s,d,f,g,h,j,k,l,p,n,i;
    scanf ("%d",&n);
    int sum[n];
    for (i = 0;i < n;i++)
    {
        scanf("%d%d%d%d%d%d%d%d%d%d",&a,&s,&d,&f,&g,&h,&j,&k,&l,&p);
        sum[i]= a+s+d+f+g+h+j+k+l+p;
    }
    for (i = 0;i < n;i++)
    printf("sum=%d\n",sum[i]);
}