#include<stdio.h>
#include<math.h>
#define s(a,b,c) ((a+b+c)/2.0)
#define area(s,a,b,c) (sqrt(s*(s-a)*(s-b)*(s-c)))

int main()
{
    int a, b, c;
    float s, area;
    for(;scanf("%d%d%d",&a,&b,&c) != EOF;)
    {
    s = s(a,b,c);
    printf("%.f %f\n",s,area(s,a,b,c));
    }
}