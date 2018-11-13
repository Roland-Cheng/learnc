#include<stdio.h>
int main()
{
    double x;
    for(;;)
    {
    scanf("%lf",&x);
    if (x == 0) break;
    else
    {
    switch ((int)(x/1000))
    {
        case 0 :printf ("0.000000");
            break;
        case 1 :printf ("%lf",0.05*(x-1000));
            break;
        case 2 :printf ("%lf",0.1*(x-2000)+50);
            break;
        case 3 :printf ("%lf",0.15*(x-3000)+150);
            break;
        case 4 :printf ("%lf",0.2*(x-4000)+300);
            break;
        default:printf ("%lf",0.25*(x-5000)+500);
            break;
    }printf("\n");
    }
    }
}