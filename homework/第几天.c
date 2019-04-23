#include<stdio.h>

int isleap(int x);
int main()
{
    int i, n, y, d, m, sum, j;
    int s[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int l[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
    scanf ("%d",&n);
    for (i = 0;i < n;i++)
    {
        scanf ("%d%d%d",&y,&m,&d);
        if (isleap(y))
        {
            for (j = 0,sum = 0;j<m-1;j++)
            sum+=l[j];
            sum = sum +d;

        }
        else{
            for (j = 0,sum = 0;j<m-1;j++)
            sum+=s[j];
            sum = sum +d;

        }
        printf("该日期是当年的第%d天\n",sum);
    }
}

int isleap(int x)
{
    if ((x%4 == 0 && x%100 != 0)||x%400 == 0)
    return 1;
    else return 0;
}