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
    int i, n, x, j, a, b;
    for(;;)
    {
        scanf("%d%d",&a,&b);
        if (a == 0) break;
        else{
            if (a%2) a = a+1;
            if (b%2) b = b-1;
    for (i = a;i <=b;i+=2)
    {
        for (j = 2;j<=i/2;j++)
        {
            if (iszhi(j) && iszhi(i-j)){
            printf("%d=%d+%d\n",i,j,i-j);
            break;}
            else continue;
        }
    }
    printf("\n");
    }
    }
    return 0;
}
