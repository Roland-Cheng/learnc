#include<stdio.h>
int jud (char *s);
int main()
{
    int i, n;
    char s[250];
    scanf ("%d",&n);
    getchar();
    for (i = 0;i < n;i++)
    {
        scanf("%[^\n]",s);
        getchar();
        if (jud(s)) printf ("Yes!\n");
        else printf("No!\n");
    }
}

int jud (char *s)
{
    int i;
    for (i = 0;s[i] != '\0';i++);
    if (s[0] != s[i-1]) return 0;
    for (i = 0;s[i] != '\0';i++)
        s[i] = s[i+1];
    s[i-2] = '\0';
    if (s[0] == '\0' || s[1] == '\0') return 1;
    else return jud(s);
}