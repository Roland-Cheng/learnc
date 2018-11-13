#include<stdio.h>
int main()
{
    int i, j = -1;
    double pi = 0.0;
    for (i = 1;i<=1e5+1;i+=2)
    {
        j = j*(-1);
        pi = pi + j*1.0/i;
    }
    pi = pi*4.0;
    printf("%.9f\n",pi);
    return 0;
}
