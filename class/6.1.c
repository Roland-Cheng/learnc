#include "stdio.h"
void main(void)
{
    float *p;
    float a;
    p = &a;
    scanf("%f",p);
    printf("%f\n",*p);
}