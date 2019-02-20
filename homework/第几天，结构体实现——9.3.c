#include<stdio.h>

int isleap(int x);
int main()
{
    int i, n, sum, j;
    int s[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int l[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
    scanf ("%d",&n);
    struct day {
        int year,month,date;
    } day[n];
    for (i = 0;i < n;i++)
    {
        scanf ("%d%d%d",&day[i].year,&day[i].month,&day[i].date);
        if (isleap(day[i].year))
        {
            for (j = 0,sum = 0;j<day[i].month-1;j++)
            sum+=l[j];
            sum = sum +day[i].date;

        }
        else{
            for (j = 0,sum = 0;j<day[i].month-1;j++)
            sum+=s[j];
            sum = sum +day[i].date;

        }
        printf("%d\n",sum);
    }
}

int isleap(int x)
{
    if ((x%4 == 0 && x%100 != 0)||x%400 == 0)
    return 1;
    else return 0;
}