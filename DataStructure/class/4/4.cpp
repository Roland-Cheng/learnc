#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <iostream>
/*定义各类常量*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define STOP -2
#define OVERFLOW -3
#define MAX_VERTEX_NUM 21

typedef int ElemType; //定义结点存储的数据类型
typedef int status;  //定义函数返回值类型
typedef struct ArcNode  
{
    int adjvex;
    struct ArcNode *next;
}ArcNode;
typedef struct VNode  
{
    int key=0;
    ElemType data;
    ArcNode *first;
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct 
{
    AdjList vertices;
    int vernum,arcnum;
    char name[30];
}ALGraph;


#define EmptyTOS    -1  //空栈
#define MinStackSize    5   //栈的最小值

typedef ArcNode* StackElem;    //数据类型

typedef struct stackRecord
{
    int capacity;//容量
    int stackTop;//栈顶
    StackElem *array; 
}STACK;

int isEmpty(STACK *s);  //判空
int isFull(STACK *s);   //判满
STACK *createStack(int maxElements);    //栈的创建
void disposeStack(STACK *s);        //栈的释放
void makeEmpty(STACK *s);       //创建空栈
void push(StackElem element, STACK *s);//入栈
StackElem top(STACK *s);      //返回栈顶元素
void pop(STACK *s);         //出栈
StackElem topAndpop(STACK *s);    //出栈并返回栈顶元素
/*栈的构造由于与实验关系不大，就此不做详细注释了*/
int isEmpty(STACK *s)
{
    return (s->stackTop == EmptyTOS);
}

int isFull(STACK *s)
{
    return (s->stackTop == s->capacity -1);
}

STACK *createStack(int maxElements) //创建定长的栈
{
    STACK *s;
    if(maxElements < MinStackSize) {
        printf("Stack size si too small\n");    
        return NULL;
    }
    s = (STACK *)malloc(sizeof(struct stackRecord));
    s->array = (StackElem *)malloc(sizeof(StackElem) * maxElements);
    s->capacity = maxElements;
    makeEmpty(s);

    return s;

}
void disposeStack(STACK *s)
{
    if(s != NULL) {
        free(s->array); 
        free(s);
    }
}

void makeEmpty(STACK *s)
{
    if(s != NULL) {
        s->stackTop = EmptyTOS; 
    }
}

void push(StackElem element, STACK *s)
{
    if(!isFull(s)) {
        s->stackTop++;
        s->array[s->stackTop] = element;
    } else {
        printf("full stack\n");
    }
}

StackElem top(STACK *s) //返回栈顶元素
{
    if(!isEmpty(s)) {
        return s->array[s->stackTop];   
    } else {
        printf("empty stack\n");
        return 0;
    }
}

void pop(STACK *s) //出栈但是并不会范湖函数值
{
    if(!isEmpty(s))
        s->stackTop--;  
    else
        printf("empty stack\n");
}

StackElem topAndpop(STACK *s) //出栈并返回栈顶元素
{
    if(!isEmpty(s)) {
        return s->array[s->stackTop--];
    } else {
        printf("empty stack\n");    
        return 0;
    }
}

//栈定义完成

status CreateCraph(ALGraph &G);
status DestroyGraph(ALGraph &G);
status LocateVex(ALGraph G,int u);
status PutVex(ALGraph G,int u,ElemType value);
status FirstAdjVex(ALGraph G,int u);
status NextAdjVex(ALGraph G,int v,int w);
status InsertVex(ALGraph &G,int u);
status DeleteVex(ALGraph &G,int v);
status InsertArc(ALGraph &G,int v,int w);
status DeleteArc(ALGraph &G,int v,int w);
status DFSTraverse(ALGraph G);
status BFSTraverse(ALGraph G);

int main(){
int op=1;
int flag;
int i,j,k;
char string[100];
int u,v;
ElemType value;
FILE *fp;
ALGraph G;
ALGraph Gs[30];
    while(op){
        system("cls"); printf("\n\n");
        /*菜单的主要界面*/
        printf("      Menu for Graph On Linked List \n");
        printf("-------------------------------------------------\n");
        printf("      1.CreateCraph        2.Switch\n");
        printf("      3.DestroyGraph       4.LocateVex\n");
        printf("      5.PutVex             6.FirstAdjVex\n");
        printf("      7.NextAdjVex         8.InsertVex\n");
        printf("      9.DeleteVex          10.InsertArc\n");
        printf("      11.DeleteArc         12.DFSTraverse\n");
        printf("      13.BFSTraverse\n");
        printf("-------------------------------------------------\n");
        printf("      101.存储图        102.读取图\n");
        printf("请选择你的操作:");
        scanf("%d",&op);
        switch(op)
        {
            case 1:
            getchar();getchar();
            break;
            case 2:
            getchar();getchar();
            break;
            case 3:
            getchar();getchar();
            break;
            case 4:
            getchar();getchar();
            break;
            case 5:
            getchar();getchar();
            break;
            case 6:
            getchar();getchar();
            break;
            case 7:
            getchar();getchar();
            break;
            case 8:
            getchar();getchar();
            break;
            case 9:
            getchar();getchar();
            break;
            case 10:
            getchar();getchar();
            break;
            case 11:
            getchar();getchar();
            break;
            case 12:
            getchar();getchar();
            break;  
        }
    }
}

status CreateCraph(ALGraph &G){
    int flag,n,i,falg=0;
    int chongfu[100]={0};
    printf("输入有向图还是无向图(0为无向图，1为有向图)：");
    scanf("%d",&flag);
    printf("\n输入结点个数：");
    printf("\n输入结点的关键字(0不为关键字)\n");
    for(i=1;i<=n;i++) {
        scanf("%d",&G.vertices[i].key);
        G.vertices[i].first=NULL;
        if(chongfu[G.vertices[i].key]==0) chongfu[G.vertices[i].key]++;
        else falg=1;
    }
    if(falg) {
        printf("输入了重复的关键字\n");
        return ERROR;
    }
    printf("输入弧的对应关系,输入0停止\n");
    if(flag==0){
        int p=1,q;
        for(;p!=0;){
            scanf("%d%d",&p,&q);
            if(chongfu[p]==0||chongfu[q]==0) falg=1;
            int k;
            for(k=1;G.vertices[k].key!=p;k++);
            ArcNode *p=G.vertices[k].first;
            for(;p-》;p=p->next)
        }
        if(falg){
            printf("输入了不存在的结点\n");
        }
    }

}