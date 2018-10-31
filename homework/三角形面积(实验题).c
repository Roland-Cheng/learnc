#include <stdio.h>
#include <math.h>
int main()
{
    int n, i;
    scanf("%d",&n);
    float p, a, b, c;
    float s[n];
    for (i = 0;i < n;i++)
    {
        scanf ("%f%f%f",&a,&b,&c);
        p = (a+b+c)/2.0;
        p = p*(p-a)*(p-b)*(p-c);
        s[i] = sqrt(p);
    }
    for (i = 0;i < n;i++)
    {
        printf("area=%.6f\n",s[i]);
    }


}