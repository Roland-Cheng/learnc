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
    for (i =0;i<=30;i++)
    {
        scanf ("%ls",&s[i]);
        push(s[i],c);
    }


}