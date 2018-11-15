#include<stdio.h>
int strelen(char *s);
int main()
{
    int n, i;
    char *s;
    scanf("%d",&n);
    getchar();
    for(i = 1;i <= n;i++)
    {
        //scanf("%[^\n]",s);
        //printf("%s",s);
        fgets(s,5000,stdin);
        printf("%d\n",strelen(s)-1);
    }
}
int strelen(char *s)
{
    int i;
    if (*s == '\0')
    return 0;
    else return(1 + strelen(++s));
}
