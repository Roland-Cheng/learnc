#include <stdio.h>
int main()
{
    int n ,i;
    scanf ("%d", &n);
    short t[10];
    for(i=0;i<n;i++)
    scanf ("%hd",& t[i]);
    for (i = 0;i < n;i++)
    {
        unsigned short d, p;
        unsigned short a, s, f;
        d = t[i];
        a = d>>12;
        s = d<<4;
        s = s>>8;
        s = s<<4;
        f = d<<12;
        p = a|s|f;
        printf("%d\n",p);
    }
    
    return 0;
}