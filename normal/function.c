#include<stdio.h>
int min();
int main()
{
    int x;
    x = min(5,9);
    printf("%d",x);
    return 0;
}
int min (int x,int y)
{
    int star;
    star = (x<=y)? x:y;
    return star;
}