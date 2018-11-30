#include<stdio.h>
void printbit (int x)
{
    int i;
    int n = sizeof(int)*__CHAR_BIT__;
    int mask = 1 << (n-1);
    for (i = 1;i <= n;i++)
    {
        putchar ( ! ( x & mask ) ? '0':'1');
        x = x << 1;
        /*if ( ! (i % __CHAR_BIT__) && i<n)
        putchar (' ');*/

    }
}

int main()
{
    int x, i, n, k;
    scanf("%d",&n);
    for(k=0;k<n;k++)
    {/*
        int s[8*sizeof(int)] = {0};
    
    if (x<0) {x = -x,s[8*sizeof(int)-1] = 1;}
    for(i = 0;x;i++)
    {
        s[i] = x%2;
        x = x/2;
    }
    for(i = 8*sizeof(int)-1;i+1;i--)
    printf("%d",s[i]);*/
    scanf("%d",&x);
    printbit (x);
    printf("\n");
    }
}