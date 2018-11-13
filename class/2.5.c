#include<stdio.h>
int main()
{
    float x;
    scanf("%f",&x);
    if (x < 1000) printf("0");
    else if (1000 <= x && x < 2000) printf("%.2f",0.05*x);
    else if (2000 <= x && x < 3000) printf("%.2f",0.1*x);
    else if (3000 <= x && x < 4000) printf("%.2f",0.15*x);
    else if (4000 <= x && x < 5000) printf("%.2f",0.2*x);
    else printf("%.2f",0.25*x);
    return 0;
}
