#include<stdio.h>
int main()
{
    float x, s;
    scanf("%f",&x);
    s = (int)(x/1000);
    switch ((int)(x/1000))
    {
        case 0 :printf ("0");
            break;
        case 1 :printf ("%.2f",0.05*x);
            break;
        case 2 :printf ("%.2f",0.1*x);
            break;
        case 3 :printf ("%.2f",0.15*x);
            break;
        case 4 :printf ("%.2f",0.2*x);
            break;
        default:printf ("%.2f",0.25*x);
            break;
    }
}