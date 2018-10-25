#include<stdio.h>
enum month {jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};
int main()
{
     int n ,i;
    scanf ("%d", &n);
    char t [30];
    for(i=0;i<n;i++)
        scanf("%hhd",&t[i]);
        for(i=0;i<n;i++){
            int year;
            year = t[i];
            (year%4 == 0 && year%100 != 0 || year % 400 == 0)? 
            printf("January,31;February,29;March,31;April,30;May,31;June,30;July,31;August,31;September,30;October,31;November,30;December,31;\n")
            :printf("January,31;February,28;March,31;April,30;May,31;June,30;July,31;August,31;September,30;October,31;November,30;December,31;\n");
        }
    return 0;
}
