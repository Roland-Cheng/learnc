#include<stdio.h>
int main()
{
    int c;
    while ( scanf("%d", &c) == 1){
        if (c % 3 ==0 && c % 10 ==5)
        printf ("1\n");
        else 
        printf ("0\n");
    }
    return 0;
}
