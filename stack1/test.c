#include<stdio.h>
#include"stack1.h"
int main()
{
    STACK *c = InitStack();
    int s[5],i,p;
    for (i = 0;i<= 5;i++)
    {scanf("%d",&s[i]);
    push(c,s[i]);}
    while(isEmpty(c) == 0) {
        pop(c,&p);
        printf("%d",p);
    }
    return 0;

}