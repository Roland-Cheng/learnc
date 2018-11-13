#include<stdio.h>
int main()
{
    float x1,x0,c,d;
    for (x0 = 0,x1 = 1;;)
    {
        c  = (x1-x0);
        if (c >= 1e-6 || c + 1e-6 <= 0)
        {
            d = x0 - (3*x0*x0*x0 - 4*x0*x0 - 5*x0 + 13)/(9*x0*x0 - 8*x0 - 5);
            x1 = x0;
            x0 = d;
        }
        else break;
    }
    printf ("%f",x0);
}