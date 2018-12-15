#include<stdio.h>
#include"hotel.h"
int menu(void)
{
    int code, status;
    printf("\n%s%s\n", STARS, STARS);
    printf("1)hotel1        2)hotel2\n");
    printf("3)hotel3        4)QUIT\n");
    printf("%s%s\n",STARS, STARS);
    while((status = scanf("%d",&code)) != 1 || (code <1 || code > 5))
        printf("please enter number 1 to 5.\n");
    return code;
}
int getnights(void)
{
    int nights;
    printf("How many nights do you need?\n");
    while(scanf("%d", &nights) != 1)
    printf ("please enter number\n");
    return nights;
}
void showprice(double rate, int nights)
{
    int n;
    double totle = 0.0;
    double zhekou = 1.0;
    for (n = 1; n <= nights; zhekou *= discount)
    totle += zhekou*rate;
    printf ("The totle cost will be %f", totle);

}