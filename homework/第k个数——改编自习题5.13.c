#include<stdio.h>
int hanshu(double x,int n);
int main()
{
    double x;
    int n;
    for(;;)
    {
     if(scanf("%lf%d",&x,&n) != EOF)
    printf("%d\n",hanshu(x,n));
    else break;
}
}
int hanshu(double x,int n)
{
    int i, c;
    for (i = 2;i <= n;i++)
    {
        x = x/10;
    }
    c = (int)x%10;
    if (x >= 1) return(c);
    else return -1;
}