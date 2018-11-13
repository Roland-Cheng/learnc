#include<stdio.h>
int main()
{
    int a, b, c;
    for(;;)
    {
    if (scanf("%d%d%d",&a,&b,&c) != EOF)
    {
        if ((a >= b && a <= c)||(a >= c && a <= b))
        printf("A:%d\n",a);
        else if ((b >= a && b <= c)||(b >= c && b <= a))
        printf("B:%d\n",b);
        else printf ("C:%d\n",c);
    }
    else break;
    }
}