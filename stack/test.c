#include"stack.h"
#include<stdio.h>
#include"stack.c"
int main()
{
    STACK *c;
    c = createStack(30);
    makeEmpty (c);
    int i,m;
    int s[30];
    for (i =0;i<5;i++)
    {
        scanf ("%d",&s[i]);
        push(s[i],c);
    }
    for (i =0;i<5;i++){
        printf("%d\n",topAndTop(c));
    }


}