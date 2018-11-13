#include<stdio.h>
int main()
{
    int n, i;
    char c;
    scanf ("%d", &n);
    char s[n];
    for (i = 0;i < n;)
        {
            char v;
            scanf("%c",&v);
            if (v == '\n');
            else 
            {
                s[i] = v;
                i++;
            }
        }
    for (i = 0;i < n;i++)
    {
        if (s[i]<= '9' && s[i]>= '0')
        printf("%c\n",s[i]);
        else if (s[i]<= 'f' && s[i]>= 'a')
        printf("%d\n",s[i]-87);
        else if (s[i]<= 'F' && s[i]>= 'A')
        printf("%d\n",s[i]-55);
        else printf("%d\n",s[i]);
    }
}