#include<stdio.h>
void change (int *u,int k,int n);
int main()
{
    for(;;)
    {
    int n, i, k;
    if (scanf("%d%d",&n,&k) == EOF) break;
    int u[n];
    for (i = 0;i < n;i++) scanf("%d",&u[i]);
    change (u,k,n);
    }
}

void change (int *u,int k,int n)
{
    int x, i, j = 0;
    for (i = 0;i < n;i++)
    {
        if (i < (n-k))
        printf ("%d",u[i+k]);
        else 
        {
            printf ("%d",u[j]);
            j++;
        }
        if (i != (n-1)) printf(" ");
    }
    printf("\n");
}