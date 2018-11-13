#include<stdio.h>
int main()
{
    char c;
    for(;;)
    {
        c = getchar();
        if (c == '\n' || c == EOF ) break;
        else 
        {
            if (c == ' ')
            {
                putchar(' ');
                for(;;)
                {
                    char s;
                    s = getchar();
                    if (s == ' ')  continue;
                    else {putchar(s);
                    break;}
                }

            }
            else putchar(c);
        }
        
    }
    return 0;
}
