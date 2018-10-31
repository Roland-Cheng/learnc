#include<stdio.h>
#define PI 3.14159
int main()
{
   int f ;
   unsigned short p, k ;
   double c , r , s ;

/* for task 1 */
   printf("Input  Fahrenheit: ") ;
   scanf("%d", &f ) ;
   c = 5.0/9*(f-32) ;
   printf( " \n %d (F) = %.2f (C)\n\n ", f, c ) ;

/* for task 2 */
printf("input the radius r:");
scanf("%lf", &r);
s = PI * r;
s = s * r;
printf("\nThe acreage is %.2f\n\n",s);

/* for task 3 */
printf("input hex int k, p :");
scanf("%hx %hx", &k, &p );
unsigned int newint;
newint = (p&0xff00)^((k&0xff00)>>8);
printf("new int = %x\n\n",newint);

}
