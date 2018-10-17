#include<stdio.h>
#include"lower.c"
char s[30];
int main ()
{
    scanf ("%s", s );
    lower (s);
    printf("%s", s );
    return 0;
}