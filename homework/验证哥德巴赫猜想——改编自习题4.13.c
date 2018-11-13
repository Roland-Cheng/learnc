#include<stdio.h>
#include<math.h>
int iszhi(int x);
int iszhi(int x)
{
    int i;
    if (x == 1) return 0;
    else if (x == 2) return 1;
    else if (x == 3) return 1;
    else
    {
        for (i = 2;i<=sqrt(x);i++)
        {
            if (x%i != 0) continue;
            else {
                return 0;
                break;
            } 
        }
        return 1;
    }
    
}
int main()
{
    int i, n, x, j;
    scanf("%d",&n);
    for (i = 1;i <=n;i++)
    {
        scanf ("%d",&x);
        for (j = 2;j<=x/2;j++)
        {
            if (iszhi(j) && iszhi(x-j)){
            printf("%d=%d+%d\n",x,j,x-j);
            break;}
            else continue;
        }
    }
    return 0;
}
