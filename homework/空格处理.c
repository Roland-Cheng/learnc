#include<stdio.h>
int main()
{
    char c;
    int n, i;
    scanf("%d",&n);
    getchar();
    for (i = 1;i <= n;i++)
    {
    for(;;)
    {
        c = getchar();
        if (c == '\n') break;
        else 
        {
            if (c == ' ')
            {
                putchar(c);
                for(;;)
                {
                    char s;
                    s = getchar();
                    if (s == ' ')  continue;
                    else 
                    {
                        if (s == '\n') goto inx;
                        else
                        {
                            putchar(s);
                            break;
                        }
                    }
                }

            }
            else putchar(c);
        }
        
    }
inx:    printf("\n");
    }
    return 0;
}
