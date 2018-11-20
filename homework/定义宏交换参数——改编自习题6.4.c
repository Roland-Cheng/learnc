#include<stdio.h>
#define swap(x,y) y,x
int main()
{
    int a,b,i;
    for(i=1;;i++)
    {
        if (scanf("%d%d",&a,&b) == EOF) break;
        printf("Case %d:\n",i);
        printf("Before Swap:a=%d b=%d\nAfter Swap:a=%d b=%d\n\n",a,b,swap(a,b));
    }
    return 0;
}