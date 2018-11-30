#include<stdio.h>
int strlen(char s[])
{
    if (s[0] == '\0') return 0;
    int i;
    for (i =0 ;s[i];i++) s[i]=s[i+1];
    return strlen(s)+1;
}

int main()
{
    int n, i;
    char s[100][1000]={0};
    scanf("%d",&n);
    getchar();
    for(i = 0;i<n;i++)
    {    
        scanf("%[^\n]",s[i]);
        getchar();
        printf("%d\n",strlen(s[i]));
    }
}