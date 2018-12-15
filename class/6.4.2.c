#include<stdio.h>
#define scale 100

void chuli (char s[]);
int main()
{
    for (;;)
    {
        int n;
        scanf("%d",&n);
        getchar();
        if(n == 0) break;
        char s[n][scale], *p = s[0];
        for(;p<s[0]+n*scale;fgets(p,80,stdin),chuli(p),p+=scale);
        printf("\n");
    }
}

void chuli(char s[])
{
    int flag = 0,j=0;
    char *p = s;
    for(;*p!='\n';)
    {
        if (*p == ' ' && flag == 0) flag=1;
        else if (*p == ' ');
        else if (flag == 1) putchar(' '),putchar(*p),flag = 0,j++;
        else putchar(*p),j++;
        p++;
    }
    if (j)
    { 
        if (*(p-1) == ' ') putchar(' ');
        printf("\n");
    }    
}