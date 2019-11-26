#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
/*定义各类常量*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define STOP -2
#define OVERFLOW -3

typedef int ElemType;
typedef int status;
typedef struct Node
{
    ElemType e;
}Node;
typedef struct TreeNode
{
    int key=0;
    struct TreeNode *left=NULL,*right=NULL;
    Node* elem;
}TreeNode;

#define EmptyTOS    -1  //空栈
#define MinStackSize    5   //栈的最小值

typedef TreeNode* elementType;    //数据类型

typedef struct stackRecord
{
    int capacity;//容量
    int stackTop;//栈顶
    elementType *array; 
}STACK;

int isEmpty(STACK *s);  //判空
int isFull(STACK *s);   //判满
STACK *createStack(int maxElements);    //栈的创建
void disposeStack(STACK *s);        //栈的释放
void makeEmpty(STACK *s);       //创建空栈
void push(elementType element, STACK *s);//入栈
elementType top(STACK *s);      //返回栈顶元素
void pop(STACK *s);         //出栈
elementType topAndpop(STACK *s);    //出栈并返回栈顶元素

int isEmpty(STACK *s)
{
    return (s->stackTop == EmptyTOS);
}

int isFull(STACK *s)
{
    return (s->stackTop == s->capacity -1);
}

STACK *createStack(int maxElements)
{
    STACK *s;
    if(maxElements < MinStackSize) {
        printf("Stack size si too small\n");    
        return NULL;
    }
    s = (STACK *)malloc(sizeof(struct stackRecord));
    s->array = (elementType *)malloc(sizeof(elementType) * maxElements);
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

void push(elementType element, STACK *s)
{
    if(!isFull(s)) {
        s->stackTop++;
        s->array[s->stackTop] = element;
    } else {
        printf("full stack\n");
    }
}

elementType top(STACK *s)
{
    if(!isEmpty(s)) {
        return s->array[s->stackTop];   
    } else {
        printf("empty stack\n");
        return 0;
    }
}

void pop(STACK *s)
{
    if(!isEmpty(s))
        s->stackTop--;  
    else
        printf("empty stack\n");
}

elementType topAndpop(STACK *s)
{
    if(!isEmpty(s)) {
        return s->array[s->stackTop--];
    } else {
        printf("empty stack\n");    
        return 0;
    }
}

//栈定义完成

status jiancha(int treepre[],int treein[],int n);
status CreateBiTree(TreeNode* &T,int* treepre,int* treein,int n);
status DestroyBiTree(TreeNode* &T);
status ClearBiTree (TreeNode* &T);
status BiTreeEmpty(TreeNode* T);
status BiTreeDepth(TreeNode* T);
Node* LocateNode(TreeNode* T,ElemType e);

int main(){
int op=1;
int i,j=0,k;
int n=5;
int treepre[n],treein[n];
int chongfu[n];
Node* treeelem[n];
int flag;
ElemType e,x; //定义元素类型，用来进行之后部分的数据元素输出
char string[100];  //用于存储之后会使用的文件名称
FILE *fp;  //定义文件指针，之后进行文件操作
TreeNode* T=NULL;
TreeNode* Ts[30]={NULL};
while(op){
    
    system("cls"); printf("\n\n");
    printf("      Menu for Bitree On Sequence Structure \n");
	printf("-------------------------------------------------\n");
    printf("      1.DefineBiTree       2.Switch\n");
    printf("      3.CreateBiTree       4.DestroyBiTree\n");
    printf("      5.ClearBiTree        6.BiTreeEmpty\n");
    printf("      6.BiTreeDepth        7.LocateNode\n");
    printf("      8.Assign             9.GetSibling\n");
    printf("      10.InsertNode        11.DeleteNode\n");
    printf("      12.PreOrderTraverse  13.InOrderTraverse\n");
    printf("      14.PostOrderTraverse 15.LevelOrderTraverse\n");
    printf("-------------------------------------------------\n");
    printf("      101.存储链表          102.读取链表\n");
    printf("请选择你的操作[0~12]:");
	scanf("%d",&op);
    switch(op)
    {
    case 1:
    /*printf("请输入树的节点个数：\n");
    scanf("%d",&n);
    for(i=0;i<n;i++) chongfu[i]=0;
    printf("请输入树的关键字和数据（用空格分隔，换行进行区分）：\n");
    for(i=0;i<n;i++){
        scanf("%d",&j);
        if(chongfu[j-1]==0) chongfu[j-1]++;
        else{
            printf("出现重复关键字\n");
            scanf("%d",&j);
            goto tiaochu;
        }
        treeelem[j-1]=(Node*)malloc(sizeof(Node));
        scanf("%d",&treeelem[j-1]->e);
    }*/
    printf("请输入二叉树的先序遍历：\n");
    for(i=0;i<n;i++) scanf("%d",&treepre[i]);
    /*for(i=0;i<n;i++){
        if(chongfu[treepre[i]-1]==1) chongfu[treepre[i]-1]++;
        else if(chongfu[treepre[i]-1]==0){
            printf("输入了未出现的关键字\n");
            goto tiaochu;
            }
        else {
            printf("重复关键字\n");
            goto tiaochu;
        }
    }*/
    printf("请输入二叉树的中序遍历：\n");
    for(i=0;i<n;i++) scanf("%d",&treein[i]);
    /*for(i=0;i<n;i++){
        if(chongfu[treein[i]-1]==2) chongfu[treein[i]-1]++;
        else if(chongfu[treein[i]-1]==0){
            printf("输入了未出现的关键字\n");
            goto tiaochu;
        }
        else {
            printf("重复关键字\n");
            goto tiaochu;
        }
    }*/
    if(jiancha(treepre,treein,n)==OK) printf("可以创建树\n");
    else printf("无法创建树\n");
tiaochu:    getchar();getchar();
    break;
    case 2:
        break;
    }
}
}

status jiancha(int treepre[],int treein[],int n){
    int i;
    for(i=0;i<n;i++) printf("%d ",treepre[i]);
    for(i=0;i<n;i++) printf("%d ",treein[i]);
    if(n==0) return OK;
    if(n==2){
        if((treepre[0]==treein[0]&&treepre[1]==treein[1])||(treepre[0]==treein[1]&&treepre[1]==treein[0])) return OK;
        else return FALSE;
    }

    for(i=0;i<n;){
        if(treepre[0]!=treein[i]) i++;
    }
    if(i==n) return FALSE;
    return jiancha(treepre+1,treein,i)&&jiancha(treepre+1,treein+1+i,n-1-i);
}