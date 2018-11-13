#include<stdio.h>
int main()
{
    char s[100];
    char c;
    for (;;)
    {
    c = getchar();
    if (c != '0')
    {
    int i = 0;
    s[0] = c;
    for(;;)
    {
        c = getchar();
        if (c == '\n') break;
        else {
            i++;
            s[i] = c;
        }
    }
    for (;i >= 0;i--)
    putchar(s[i]);
    printf("\n");
    }
    else break;
}
}