#include<stdio.h>
#include<math.h>
#define s(a,b,c) ((a+b+c)/2.0)
#define area(s,a,b,c) (sqrt(s*(s-a)*(s-b)*(s-c)))

int main()
{
    int a, b, c;
    float s, area;
    printf("Please input the length of three siders:\n");
    scanf("%d%d%d",&a,&b,&c);
    s = s(a,b,c);
    if (s<=a || s<=b || s<=c) printf("error\n");
    else
    printf("The area of these triangle is %.3f\n",area(s,a,b,c));
}