#include<stdio.h>

int han(char s[],int k);
int main()
{
    int k;
    char s[1000];
    for(;;)
    {
        if(scanf("%s%d",s,&k) == EOF) break;
        else if(han(s,k) == -1) printf("-1\n");
        else printf("%c\n",han(s,k));
    }   
}
int han(char s[],int k)
{
    int i=0;
    while(s[++i]);
    if (k>i) return -1;
    return s[i-k];
}