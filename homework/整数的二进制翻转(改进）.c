#include<stdio.h>
#include<limits.h>
void printbit(int x);
int main ()
{
    unsigned int x, p, n, a,k,l;
	scanf("%d%d%d",&x,&p,&n);
	k=((~0)<<(32-p-n));
	l=k>>(32-n);
	l=l<<p;
	l=l^x;

    printbit(x);
    printf("\n");
    printbit(l);
    printf("\n");
}


void printbit (int x)
{
    int i;
    int n = sizeof(int)*__CHAR_BIT__;
    int mask = 1 << (n-1);
    for (i = 1;i <= n;i++)
    {
        putchar ( ! ( x & mask ) ? '0':'1');
        x = x << 1;
        if ( ! (i % __CHAR_BIT__) && i<n)
        putchar (' ');

    }
}