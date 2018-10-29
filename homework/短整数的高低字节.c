#include<stdio.h>
int main()
{
    int n ,i;
    scanf ("%d", &n);
    short t [30];
    for(i=0;i<n;i++)
        scanf("%hd",&t[i]);
        for(i=0;i<n;i++)
        {
            short h, l, x;
            x = t[i];
            h = x>>8;
            l = x<<8;
            l = l>>8;
            printf ("%c,%c\n",h,l);
        }
}