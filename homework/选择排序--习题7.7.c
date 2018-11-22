#include<stdio.h>
int main()
{
    int n, i;
    scanf("%d",&n);
    int s[n];
    for(i = 0;i < n;i++) scanf("%d",&s[i]);
    for(i = 0;i < n;i++)
    {
        int k, x;
        for (k = 0;k < (n-i);k++)
        {
            if (s[k] > s[k+1]) 
            {
                x = s[k];
                s[k] = s[k+1];
                s[k+1] = x;
            }
        }
    }
    for(i = 0;i < n;i++) 
    {
        printf("%d",s[i]);
        if (i != (n-1)) printf(" ");
    }
    printf("\n");
}