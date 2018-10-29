#include<stdio.h>
#include"stack1.h"
int main() {
    char s[N],ch,i = 0;
    STACK *ms = InitStack();
    printf("请输入字符串:\n ");
    gets(s);
    while(s[i] && isFull(ms) == 0) {
        push(ms,s[i]);
        ++i;
    }
    while(isEmpty(ms) == 0) {
        pop(ms,&ch);
        printf("%c",ch);
    }
    printf("\n");
    free(ms);
    return 0;
}