#include <stdio.h>
int main()
{
    int n ,i;
    scanf ("%d", &n);
    char t [30];
    for(i=0;i<n;i++)
        scanf("%hhd",&t[i]);
        for(i=0;i<n;i++){
            int j,s;
            for (j=s=0;j<= t[i];j++)
            s = j + s;
            printf ("%d\n", s);
        }

   
    return 0;
}
