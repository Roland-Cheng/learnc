#include<stdio.h>
int com(int a, int b);
int main()
{
    int a,b;
    for(;;)
    {
        scanf("%d%d",&a,&b);
        if (a == 0) break;
        else printf("%d\n",com(a,b));
    }
}
int com(int a,int b)
{
    if (a > b) a = a-b;
    else if (b > a) b = b-a;
    else return a;
    return com (a,b);
}