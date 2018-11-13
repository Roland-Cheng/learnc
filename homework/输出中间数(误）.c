#include<stdio.h>
int main()
{
    int a, b, c;
    for (;;)
    {
        if(scanf("%d%d%d",&a,&b,&c) != EOF)
        {
        if(a>b && a>c) 
        {
            if (c >b) printf("C:%d",c);
            else printf ("B:%d",b);
        }
        else if (b>a && b>c)
        {
            if (c > a) printf("C:%d",c);
            else printf ("A:%d",a);
        }
        else if (a == b || a == c) printf ("A:%d",a);
        else if (b == c) printf ("B:%d",b);
        else 
        {
            if (b > a) printf("B:%d",b);
            else printf("A:%d",a);
        }
        printf("\n");
        }
        else break;
    }
}