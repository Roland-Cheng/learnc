#include<stdio.h>
#define CHANGE 1

int main()
{
    printf("Please input a string:\n");
    char s[250];
    scanf("%[^\n]",s);
    #if CHANGE == 0
    printf("%s\n",s);
    #else
    int i = 0;
    for (;s[i]!='\0';i++)
    {
        if ('a'<=s[i] && s[i]<='z') s[i] = s[i] - 32;
        else if ('A'<=s[i] && s[i]<='Z') s[i] = s[i] + 32;
        printf("%c",s[i]);
    }
    printf("\n");
    #endif
}