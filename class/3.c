#include<stdio.h>
int main()
{
    int c;
    scanf ("%lc",&c);
    if ('A' <= c && c <= 'Z')
    printf ("%c",(c+32));
    else printf("%c",c);

}