#include<stdio.h>
int main()
{
    char s[500];
    char c;
    int i = 0;
    for(;;)
    {
        c = getchar();
        if (c == '\n') break;
        else {
            s[i] = c;
            i++;
        }
    }
    for (;i >= 0;i--)
    putchar(s[i]);
}