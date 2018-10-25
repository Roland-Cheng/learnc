#include<stdio.h>
#include"hotel.h"
int main(void)
{
    int nights;
    double rate;
    char code;

    while((code = menu())!= QUIT)
    {
        switch (code)
        {
            case 1: rate = hotel1;
            break;
            case 2: rate = hotel2;
            break;
            case 3: rate = hotel3;
            break;

        }
        nights = getnights();
        showprice(rate, nights);

    }
    printf("Thankyou and Goodbye.\n");

    return 0;
}
