#include<stdio.h>

int zhi(int x)
{
    int i;
    if (x == 1) return 0;
    else if (x == 2) return 1;
    else if (x == 3) return 1;
    else
    {
        for (i = 2;i<=x/2;i++)
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
    int x, y;
    for(;scanf("%d%d",&x,&y);)
    {
        if(x%2) x = x+1;
        int i;
        for(i=x;i<=y;i+=2)
        {
            int k;
            for(k = 2;;k++) if(zhi(k)&&zhi(i-k)) 
            {
                printf("%d=%d+%d\n",i,k,i-k);
                break;
            }
        }
        printf("\n");
    }
}