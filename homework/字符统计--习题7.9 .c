#include<stdio.h>
int main()
{
    char c;
    int i, o = 0, j, f[10]={0},l[26]={0};
    for (;;)
    {
        c = getchar();
        if (c == EOF) break;
        for (i = '0';i<'9';i++)
        if (c == i) f[i-'0']++;
        for (i = 'a',j = 'A';i<='z'||j<='Z';i++,j++)
        if (c == i || c == j) l[i-'a']++;
        if (!(('0'<=c && c<='9')||('a'<=c && c<='z')||('A'<=c && c<='Z'))) o++;
    }
    printf("0:%d",f[0]);
    for(i = 1;i <= 9;i++) printf(" %d:%d",i,f[i]);
    printf("\n");
    printf("a:%d",l[0]);
    for(i = 1;i <= 25;i++) printf(" %c:%d",i+'a',l[i]);
    printf("\n");
    printf("other:%d\n",o);
}