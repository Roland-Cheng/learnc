#include<stdio.h>
int main()
{
    int i, j, c, k;
    for (i = 0; i <= 9;i ++)
    {
        for (k = 0;k <=(20-2*i);k++)
        putchar(' ');
        printf ("   1");
        for (j = 1,c = 1;j <= i;j++)
        {
            
            c = (c*(i-j+1))/j; 
            printf ("%4d",c);   
        }
        printf("\n");
    }
}