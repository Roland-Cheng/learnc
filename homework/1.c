#include<stdio.h>
int main()
{
    int n, way, i, j, num, k, summ;
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
                    summ += num;
                    k++;
                }
            }
            sig[i] = 1;
            sum[i] = summ;
        }
        else 
        {
            for (j = 0,k = 0;j<10;j++)
            {
                scanf("%d",&num);
                if (num <= 0)
                continue;
                summ += num;
                k++;
            }
            sig[i] = 0;
            sum[i] = summ;
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