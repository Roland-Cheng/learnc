#include<stdio.h>
#define CHANGE (c%2)

int main()
{
    int i, n;
    scanf("%d",&n);
    getchar();
    for (i = 0;i < n;i++)
    {
        char c;
        c = getchar();
        if (CHANGE)
        for(;;)
        {
            if (c == '\n') break;
            else if ('a'<=c && c<='z') c = c - 32;
            else if ('A'<=c && c<='Z') c = c + 32;
            putchar(c);
            c = getchar();
        }
        else 
        for(;;)
        {
            putchar(c);
            c = getchar();
            if (c == '\n') break;
        }
        printf ("\n");
    }
}