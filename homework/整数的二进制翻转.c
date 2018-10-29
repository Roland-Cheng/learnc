#include<stdio.h>
#include<limits.h>
void printbit(int x);
int main ()
{
    int x, p, n;
    unsigned s, a, d;
    scanf ("%d%d%d",&x,&p,&n);
    if (n+p !=32){
    a = ~x;
    a = a << p;
    a = a >> (32-n);
    a = a << (32-p-n);//取出出中间位
    if (p != 0)
    {s = x >> (32-p);
    s = s << (32-p);}//取出前面位
    else s = 0;
    d = x << (p+n);
    d = d >> (p+n);//取出后面位
    printbit(x);
    printf ("\n");
    x = s|a|d;
    printbit(x);
    printf ("\n");}
    else {
        if (p == 0){
            printbit (x);
            printf ("\n");
            printbit (~x);
            printf ("\n");
        }
        else 
        {
            a = ~x;
            a = a << p;
            a = a >> p;
            s = x >> (32-p);
            s = s << (32-p);
            printbit (x);
            printf ("\n");
            printbit (s|a);
            printf ("\n");


        }
    }
    
    return 0;
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