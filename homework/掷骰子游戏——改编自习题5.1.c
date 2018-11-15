#include <stdio.h>
int sum(int a);
int mat(int a);
int main()
{
    int n, i;
    scanf("%d",&n);
    for (i = 0;i < n;i++)
    {
        int a, b, x, y;
        scanf("%d%d",&a,&b);
        x = mat(sum(a))+mat(sum(b));
        if (x == 7||x == 11) printf("success!\n");
        else if (x == 2||x == 3||x == 12) printf("fail!\n");
        else
        {
            for (;;)
            {
                a++;
                b++;
                y = mat(sum(a))+mat(sum(b));
                if (y == 7)
                {
                    printf("fail!\n");
                    break;
                }
                else if (y == x)
                {
                    printf("success!\n");
                    break;
                }

            }
        }
    
    }
}
int sum(int a)
{
    int i, sum =0;
    for(i = 0;i <= 5;i++)
    {
        sum+=(a%10);
        a/=10;
    }
    return sum;
}
int mat(int a)
{
    return (1+a%6);
}
