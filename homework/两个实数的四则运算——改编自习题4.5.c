#include<stdio.h>
double cal(double a,double b,char x);
int main()
{
    double a, b, c;
    char d;
    for (;;)
    {
        if (scanf("%lf%lf%lf %c",&a,&b,&c,&d) == EOF)
        break;
        else 
        {
            b = cal(b,c,d);
            switch((int)(a))
            {
                case 0:printf("After if-else processing,the result is : %.2f\n\n",b);
                break;
                case 1:printf("After switch processing,the result is : %.2f\n\n",b);
                break;
                case 2:printf("After if-else processing,the result is : %.2f\nAfter switch processing,the result is : %.2f\n\n",b,b);
                break;
            }
        }
    }

}
double cal(double a,double b,char x)
{
    switch((int)(x))
    {
        case '+' :a = a + b;
        break;
        case '-' :a = a - b;
        break;
        case '*' :a = a * b;
        break;
        case '/' :a = a / b;
        break;
    }
    return a;
}