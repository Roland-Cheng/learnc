#include<stdio.h>
#define M 10
#define N 3

int main()
{
    int s[M] = {0};
    int k, c;
    for (k = -1;;)
    {
        
        if (0<=k && k<M && !s[k])
        {
            s[k] = 1;
            printf("%d\t",k+1);  
        }
        k+=N;
        if (k>=M) k=k-M;
        for (;s[k] == 1;k++);
        if (k == M) k = 0;
        for (;s[k] == 1;k++);
        if (k == M) break;
    }
    printf("\n");
}