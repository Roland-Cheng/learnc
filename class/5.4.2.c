#include<stdio.h>

int main()
{
    const int m = 8*sizeof(int);
    int n, i;
    printf("Please input a number:\n");
    scanf("%d",&n);
    char num[m];
    for(i=m-1;i+1;i--)
    {
        num[i] = (n & 1) + '0';
        n>>=1;
    }
    for(i = 0;i<m;i++)
    printf("%c",num[i]);
    printf("\n");
}