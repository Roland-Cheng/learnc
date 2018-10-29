#include <stdio.h>
#include <stdlib.h>
 
#define N 100
typedef char SDataType;
 
typedef struct stack {
    SDataType  data[N];
    int top ;/*存放栈顶元素的下标*/
}STACK;
 
STACK *InitStack() {
    STACK *ps = (STACK *)malloc(sizeof(STACK));
    if(ps == NULL) {
        printf("空间申请失败。\n");
        exit(1);
    }
    ps->top = -1;
    return ps;
}
 
int isFull(STACK *s) { // 判断栈是否是"满"的
    return (s->top >= N);
}
 
int push(STACK *s,SDataType x) { // 将x压入栈
    if(isFull(s)) return 0;
    s->top++;
    s->data[s->top] = x;
    return 1;
}
 
int isEmpty(STACK *s) { // 判断栈是否是"空"的
    return (s->top == -1);
}
  
int pop(STACK *s, SDataType *x) {
    if(isEmpty(s))  return 0;
    *x = s->data[s->top];
    s->top--;  /*修改栈顶指针*/
    return 1;
}