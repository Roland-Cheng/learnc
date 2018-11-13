#include<stdio.h>
int main()
{
    int n, way, i, j, num, k;
    scanf("%d",&n);
    int sum[n], times[n], sig[n];
    for (i = 0;i < n;i++)
    {
        scanf ("%d",&way);
        if (way == 1)
        {
            for (j = 0,k = 0;j<10;j++)
            {
                scanf("%d",&num);
                if (num > 0) 
                {
                    sum[i]+=num;
                    k++;
                }
            }
            sig[i] = 1;
        }
        else 
        {
            for (j = 0,k = 0;j<10;j++)
            {
                scanf("%d",&num);
                if (num <= 0)
                continue;
                sum[i] += num;
                k++;
            }
            sig[i] = 0;

        }
        times[i] = k;
    }
    for (i = 0;i<n;i++)
    {
    if (sig[i] == 0 && times[i] != 0)
    printf ("In \"continue\" way,numbers=%d,average=%.6f\n",times[i],(1.0*sum[i]/times[i]));
    if (sig[i] == 1 && times[i] != 0)
    printf("In \"no continue\" way,numbers=%d,average=%.6f\n",times[i],(1.0*sum[i]/times[i]));
    };
    return 0;

}