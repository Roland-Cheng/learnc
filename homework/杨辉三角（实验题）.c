#include<stdio.h>
int main()
{
    int i, j, c, k, n;
    for(;;)
    {
        scanf("%d",&n);
        if (n == 0) break;
        else{
    for (i = 0; i <= n-1;i ++)
    {
        for (k = 0;k <=(2*n-2*i-3);k++)
        putchar(' ');
        printf ("   1");
        for (j = 1,c = 1;j <= i;j++)
        {
            
            c = (c*(i-j+1))/j; 
            printf ("%4d",c);   
        }
        printf("\n");
    }
    printf("\n");
        }
}
}