#include<stdio.h>
void main( )
{
   int a, b;
   printf("Input two integers:");
   scanf("%d %d",&a,&b);
   a = a+b;
   b = a-b;
   a = a-b;
   printf("\na=%d,b=%d",a,b);
}