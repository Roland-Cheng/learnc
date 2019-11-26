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

typedef TreeNode* StackElem;    //数据类型

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

StackElem top(STACK *s)
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

StackElem topAndpop(STACK *s)
{
    if(!isEmpty(s)) {
        return s->array[s->stackTop--];
    } else {
        printf("empty stack\n");    
        return 0;
    }
}

//栈定义完成

status check(int *tree,int n);
status CreateBiTree(TreeNode* &T,int* tree,Node **treeelem,int n);
status BiTreeTraverse(TreeNode* T);
status DestroyBiTree(TreeNode* &T);
status ClearBiTree (TreeNode* &T);
status BiTreeEmpty(TreeNode* T);
status BiTreeDepth(TreeNode* T);
TreeNode* LocateNode(TreeNode* T,int e);
status Assign(TreeNode* &T,int e,ElemType value);
TreeNode* GetSibling(TreeNode* T,int e);
status InsertNode(TreeNode* &T,int e,int LR,TreeNode* &c);
status DeleteNode(TreeNode* &T,int e);
TreeNode* GetParent(TreeNode* T,int e);
status PreOrderTraverse(TreeNode* T); 
status InOrderTraverse(TreeNode* T);
status PostOrderTraverse(TreeNode* T);
status LevelOrderTraverse(TreeNode* T);
status _LevelOrderTraverse(TreeNode* T,int i);
status preprint(FILE *fp,TreeNode *T);

int main(){
int op=1;
int i,j=0,k;
int n,e;
int tree[100]={0};
int chongfu[50]={0},chongfus[50];
int stackj[50]={-1};
int* p,* q;
Node* treeelem[100]={NULL};
int flag;
ElemType x; //定义元素类型，用来进行之后部分的数据元素输出
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
    printf("      7.BiTreeDepth        8.LocateNode\n");
    printf("      9.Assign             10.GetSibling\n");
    printf("      11.InsertNode        12.DeleteNode\n");
    printf("      13.PreOrderTraverse  14.InOrderTraverse\n");
    printf("      15.PostOrderTraverse 16.LevelOrderTraverse\n");
    printf("-------------------------------------------------\n");
    printf("      101.存储链表          102.读取链表\n");
    printf("请选择你的操作:");
	scanf("%d",&op);
    switch(op)
    {
    case 1:
    for(i=0;i<50;i++) chongfus[i]=0;
    //for(i=0;i<50;i++) chongfu[i]=0;
    printf("请输入树的节点个数：\n");
    scanf("%d",&n);
    printf("请输入树的关键字和数据（用空格分隔，换行进行区分）：\n");
    for(i=0,flag=0;i<n;i++){
        scanf("%d",&k);
        if(chongfus[k-1]==0) chongfus[k-1]++;
        else flag++;
        if(!flag){
            treeelem[k-1]=(Node*)malloc(sizeof(Node));
            scanf("%d",&treeelem[k-1]->e);
        }
    }
    if(flag){
        printf("输入了重复的结点\n");
        getchar();getchar();
        break;    
    }
    printf("请选择输入标准：\n1.带空子树的先序遍历\n2.先序加中序\n3.中序加后序\n");
    scanf("%d",&flag);
    if(flag<1||flag>3) {
        printf("请输入正确的值\n");
        getchar();getchar();
        break;
    }
    if(flag==1){
        printf("请输入树的带空结点的先序遍历:\n");
        for(i=1,flag=0;i<2*(n+1);i++){
            scanf("%d",&tree[i]);
            if(tree[i]){
                if (chongfus[tree[i]-1]==2) flag=1;
                else if (chongfus[tree[i]-1]==1) chongfus[tree[i]-1]++;
                else flag=2;
            }
        }
        if(flag==1){
            printf("输入了重复的结点\n");
            getchar();getchar();
            break;
        }
        if(flag==2){
            printf("输入了不存在的结点\n");
            getchar();getchar();
            break;
        }
        if(check(tree,n)==OK){
            printf("树可以创建\n");
            for(i=0;i<n;i++) chongfu[i]=chongfus[i];
        }
        else printf("树不可以创建，请重新输入\n");    
    }
    if(flag==2){
        int treepre[100]={0},treein[100]={0};
        printf("请输入先序和中序遍历:\n");
        for(i=0;i<n;i++){
        }
    }
    getchar();getchar();
    break;
    case 2:
    if(j) Ts[j-1]=T;
    printf("选择要切换的树：\n");
    for(k=0;k<30;k++) 
    if(Ts[k]!=NULL)
    printf("%d ",k+1);
    printf("\n");
    scanf("%d",&k);
    if(k<=0 || k>30) printf("请输入正确的值\n");
    else if(Ts[k-1]!=NULL){
        T=Ts[k-1];
        printf("切换成功\n");
        j=k;
    }
    else printf("切换的树不存在\n");
    getchar();getchar();
    break;
    case 3:
    if(j) Ts[j-1]=T;  //先将当前使用的主树进行储存
    for(i=0;i<n;i++)printf("%d ",treeelem[i]->e);
    for(i=1;i<=2*n+1;i++)printf("%d ",tree[i]);
    printf("%d",n);
    printf("请输入要创建的表（1~30）:\n");
    for(k=0;k<30;k++) 
    if(Ts[k]==NULL)
    printf("%d ",k+1);  //使用for循环，输出当前尚可建立的树，也就是当前尚未存在的树
    printf("\n");
    scanf("%d",&k);
    if(0<k&&k<=30){
        if(Ts[k-1]!=NULL){
            printf("树已经创建\n");
            getchar();getchar();
            break;
        } 
        if(check(tree,n)==ERROR){
            printf("请检查输入，无法创建树\n");
            getchar();getchar();
            break;
        }
        if(CreateBiTree(T,tree,treeelem,n)) printf("创建成功\n");j=k;
        //BiTreeTraverse(T);
    }
    else printf("请输入正确的值\n");
    getchar();getchar();
    break;
    case 4:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        printf("确认销毁树？（y/n）:\n");
        char c=getchar();
        if(c=='y') if(DestroyBiTree(T)) printf("销毁成功\n");
        else printf("停止销毁\n");
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 5:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        printf("确认清空树？（y/n）:\n");
        char c=getchar();
        if(c=='y') if(DestroyBiTree(T)) printf("清空成功\n");
        else printf("停止清空\n");
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 6:
    flag=BiTreeEmpty(T);
    if(flag==FALSE) printf("树不为空\n");
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 7:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        int n=BiTreeDepth(T->left);
        printf("树的层数为:%d",n);
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 8:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        printf("请输入要查找的关键字:\n");
        scanf("%d",&e);
        if(chongfu[e-1]){
            TreeNode* p=LocateNode(T->left,e);
            printf("该结点存储的元素是:%d\n",p->elem->e);
        }
        else printf("搜索不到该结点\n");
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 9:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        printf("请输入要查找的关键字:\n");
        scanf("%d",&e);
        printf("请输入要录入的元素:\n");
        scanf("%d",&x);
        if(chongfu[e-1]){
            if(Assign(T->left,e,x))printf("更改成功\n");
            else printf("更改失败\n");
        }
        else printf("搜索不到该结点\n");
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 10:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        printf("请输入要查找的关键字:\n");
        scanf("%d",&e);
        if(chongfu[e-1]){
            TreeNode* p=GetSibling(T->left,e);
            if(p)
            printf("该结点兄弟结点为：%d\n存储的元素是:%d\n",p->key,p->elem->e);
            else printf("该结点没有兄弟结点\n");
        }
        else printf("搜索不到该结点\n");
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 11:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        printf("请输入你要插入位置的结点:\n");
        scanf("%d",&e);
        if(chongfu[e-1]){
            int LR;
            int a;
            printf("请输入要插入的位置（左子树为0，右子树为1）:\n");
            scanf("%d",&LR);
            printf("请输入要输入的结点关键字和元素：\n");
            scanf("%d%d",&a,&x);
            if(chongfu[a-1]==0){
                TreeNode *c=(TreeNode*)malloc(sizeof(TreeNode));
                c->elem=(Node*)malloc(sizeof(Node));
                c->elem->e=x;
                c->key=a;
                InsertNode(T->left,e,LR,c);
                printf("插入成功\n");
                T->key++;
                chongfu[a-1]=2;
            }
            else printf("结点重复\n");
        }
        else printf("搜索不到该结点\n");
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 12:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        printf("请输入要删除结点的关键字：\n");
        scanf("%d",&e);
        if(chongfu[e-1]) {
            DeleteNode(T,e);
            chongfu[e-1]=0;
            T->key--;
            printf("删除成功\n");
        }
        else printf("搜索不到该结点\n");
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 13:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        PreOrderTraverse(T->left);
        printf("\n一共%d个元素\n",T->key);
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 14:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        InOrderTraverse(T->left);
        printf("\n一共%d个元素\n",T->key);
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 15:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        PostOrderTraverse(T->left);
        printf("\n一共%d个元素\n",T->key);
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 16:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        LevelOrderTraverse(T->left);
        printf("\n一共%d个元素\n",T->key);
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 101:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        printf("请输入要存储的文件：\n");
        scanf("%s",string);
        if((fp=fopen(string,"w"))==NULL){
            printf("打开文件失败\n");
            getchar();getchar();
            break;
        }
        fprintf(fp,"%d\n",T->key);
        preprint(fp,T->left);
        printf("已经写入文件%s",string);
		fclose(fp);
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 102:
        printf("请输入要读取的文件：\n");
        scanf("%s",string);
        if((fp=fopen(string,"r"))==NULL){
            printf("请输入正确的文件，打开失败\n");
            getchar();getchar();
            break;
        }
        for(i=0;i<100;i++) tree[i]=0;
        for(i=0;i<50;i++) chongfus[i]=0;
        fscanf(fp,"%d",&n);
        for(i=0;i<n;i++){
            fscanf(fp,"%d",&k);
            chongfus[k-1]++;
            treeelem[k-1]=(Node*)malloc(sizeof(Node));
            fscanf(fp,"%d",&(treeelem[k-1]->e));  
        }
        for(i=1;i<2*n;i++){
            fscanf(fp,"%d",&tree[i]);
        }
        printf("树已经读入了definition，请创建树\n");
        fclose(fp);
        CreateBiTree(T,tree,treeelem,n);
        for(i=0;i<n;i++) chongfu[i]=chongfus[i];
        for(i=0;i<n;i++)printf("%d ",treeelem[i]->e);
    for(i=1;i<=2*n+1;i++)printf("%d ",tree[i]);
    getchar();getchar();
    break;
    case 0:
    getchar();getchar();
    break;
    default:
    printf("请输入正确的值\n");
    getchar();getchar();
    break;
    }
}
}

status check(int *tree,int n){
    int i;
    int* p,* q;
    int stackj[100];
    for(i=0,p=stackj,q=tree+1;i<2*(n+1)-1;i++){
        /*if(p==stackj&&(q==tree+1||tree==tree+2*(n+1))){
            printf("树可以创建\n");
            break;
        }
        if(p==stackj&&(q!=tree+1&&tree!=tree+2*(n+1))){
            printf("树不可以创建\n");
            break;
        }*/
        *p=*q;
        p++;
        q++;
        for(;*(p-1)==0;){
            if(p==stackj+1){
                p--;
                *p=-1;
                break;
            }
            if(*(p-2)==0){
                p--;
                *p=-1;
                p--;
                *p=-1;
                *(p-1)=0;
            }
            else break;
        }   
    }
    if(q==tree+2*(n+1)&&p==stackj) return OK;
    else return ERROR;
}

status CreateBiTree(TreeNode* &T,int* tree,Node** treeelem,int n){
    STACK *c;
    c=createStack(50);
    makeEmpty (c);
    int i,flag=0;
    T=(TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* t=T;
    for(i=1;i<=2*n;i++){
        if(tree[i]!=0){
            if(flag){
                t->right=(TreeNode*)malloc(sizeof(TreeNode));
                t->right->key=tree[i];
                t->right->elem=treeelem[tree[i]-1];
                push(t->right,c);
                t=t->right;
                flag=0;
            }
            else{
                t->left=(TreeNode*)malloc(sizeof(TreeNode));
                t->left->key=tree[i];
                t->left->elem=treeelem[tree[i]-1];
                push(t->left,c);
                t=t->left;
            }
        }
        if(tree[i]==0){
            t=topAndpop(c);
            flag=1;
        }
    }
    T->key=n;
    T->right=T->left;
    return OK;
}

/*status BiTreeTraverse(TreeNode* T){
    int level=BiTreeDepth(T);
    int i,j,k,s;
    TreeNode* t=T;
    for(s=1;s<level;s++) printf("\t");
    printf("%4d\n",t->elem->e);
    for(i=2,j=2;i<=level;i++,j*=2){
        for(k=0;k<j/2;k++){
            for(s=0;s<level-i+1;s++)
        }
    }
}*/

status DestroyBiTree(TreeNode* &T){
    STACK *c;
    c=createStack(100);
    makeEmpty (c);
    TreeNode *t=T->left;
    for(push(t,c),t=t->left;!isEmpty(c);){
        if(t){
            push(t,c);
            t=t->left;
        }
        else{
            t=top(c)->right;
            free(topAndpop(c));
        }
    }
    free(T);
    T=NULL;
    return OK;
}

status ClearBiTree (TreeNode* &T){
    STACK *c;
    c=createStack(100);
    makeEmpty (c);
    TreeNode *t=T->left;
    for(push(t,c),t=t->left;!isEmpty(c);){
        if(t){
            push(t,c);
            t=t->left;
        }
        else{
            t=top(c)->right;
            free(topAndpop(c));
        }
    }
    T->left=T->right=NULL;
    T->key=0;
    return OK;
}

status BiTreeEmpty(TreeNode* T){
    if(T){
        if(T->key) return FALSE;
        else return TRUE;
    }
    else return ERROR;
}

status BiTreeDepth(TreeNode* T){
    if(T==NULL) return 0;
    else {
        int a,b;
        a=BiTreeDepth(T->left);
        b=BiTreeDepth(T->right);
        if(a>b) return a+1;
        else return b+1;
    }
}

TreeNode* LocateNode(TreeNode* T,int e){
    if(T==NULL) return NULL;
    if(T->key==e) return T;
    TreeNode* p=LocateNode(T->left,e);
    if(p!=NULL) return p;
    else p=LocateNode(T->right,e);
    return p;
}

status Assign(TreeNode* &T,int e,ElemType value){
    TreeNode *p=LocateNode(T,e);
    if(p) p->elem->e=value;
    else return ERROR;
    return OK;
}

TreeNode* GetSibling(TreeNode* T,int e){
    if(T==NULL) return NULL;
    if(T->left==NULL&&T->right==NULL) return NULL;
    TreeNode*p;
    if(T->left){
        if(T->left->key==e) return T->right;
        p=GetSibling(T->left,e);
        if(p!=NULL) return p;
    }
    if(T->right){
        if(T->right->key==e) return T->left;
        p=GetSibling(T->right,e);
        return p;
    }
}

TreeNode* GetParent(TreeNode* T,int e){
    if(T==NULL) return NULL;
    if(T->left==NULL&&T->right==NULL) return NULL;
    TreeNode*p;
    if(T->left){
        if(T->left->key==e) return T;
        p=GetParent(T->left,e);
        if(p!=NULL) return p;
    }
    if(T->right){
        if(T->right->key==e) return T;
        p=GetParent(T->right,e);
        return p;
    }
}

status InsertNode(TreeNode* &T,int e,int LR,TreeNode* &c){
    TreeNode *p=LocateNode(T,e);
    if(p==NULL) return ERROR;
    if(LR){
        if(p->right)
        c->right=p->right;
        p->right=c;
    }
    else {
        if(p->left)
        c->right=p->left;
        p->left=c;
    }
    return OK;
}

status DeleteNode(TreeNode* &T,int e){
    /*TreeNode* t=T;
    STACK *c;
    c=createStack(100);
    makeEmpty (c);
    int flag=0;
    for(push(t,c),t=t->left;!isEmpty(c);){
        if(t){
            push(t,c);
            t=t->left;
        }
        else for(;top(c)==NULL;){
            pop(c);
            TreeNode*p=topAndpop(c);
            if(p->key==e) flag++;
            if(flag==1){
                t=p;
                break;
            }
            else t=p->right;
        }
    }*/
    TreeNode*p=GetParent(T,e);
    if(!p) return ERROR;
    if(p->left!=NULL) {if(p->left->key==e){
        TreeNode* q=p->left;
        if(q->left){
            TreeNode *s=q->left;
            for(;s->right;s=s->right);
            s->right=q->right;
            p->left=q->left;
        }
        else p->left=q->right;
        free(q);
    }
    }
    else if(p->right!=NULL) {if(p->right->key==e){
        TreeNode* q=p->right;
        if(q->left){
            TreeNode *s=q->left;
            for(;s->right;s=s->right);
            s->right=q->right;
            p->right=q->left;
        }
        else p->right=q->right;
        free(q);
    }
    }
    return OK;
}

status PreOrderTraverse(TreeNode* T){
    TreeNode* t = T;
    STACK *c= createStack(50);    //创建并初始化堆栈S
    while(t || !isEmpty(c)){
        while(t){        //一直向左并将沿途节点访问（打印）后压入堆栈 
            printf("%d  %d\n", t->key,t->elem->e);
            push(t, c);
            t = t->left;
        }
        if (!isEmpty(c)){
            t = topAndpop(c);    //节点弹出堆栈
            t = t->right;  //转向右子树
        }
    }
}

status InOrderTraverse(TreeNode* T){
    if(T==NULL) return 0;
    InOrderTraverse(T->left);
    printf("%d  %d\n",T->key,T->elem->e);
    InOrderTraverse(T->right);
}

status PostOrderTraverse(TreeNode* T){
    if(T==NULL) return 0;
    PostOrderTraverse(T->left);
    PostOrderTraverse(T->right);
    printf("%d  %d\n",T->key,T->elem->e);
}

status _LevelOrderTraverse(TreeNode* T,int i){
    if(T==NULL||i==0) return 0;
    if(i==1) printf("%4d%4d  ",T->key,T->elem->e);
    else{
        _LevelOrderTraverse(T->left,i-1);
        _LevelOrderTraverse(T->right,i-1);
    }
}

status LevelOrderTraverse(TreeNode* T){
    int i=BiTreeDepth(T);
    int j;
    for(j=1;j<=i;j++){
        printf("第%d层：",j);
        _LevelOrderTraverse(T,j);
        printf("\n");
    }
    return OK;
}

status preprint(FILE *fp,TreeNode* T){
    TreeNode* t = T;
    STACK *c= createStack(50);    //创建并初始化堆栈S
    while(t || !isEmpty(c)){
        while(t){        //一直向左并将沿途节点访问（打印）后压入堆栈 
            fprintf(fp,"%d  %d\n", t->key,t->elem->e);
            push(t, c);
            t = t->left;
        }
        if (!isEmpty(c)){
            t = topAndpop(c);    //节点弹出堆栈
            t = t->right;  //转向右子树
        }
    }
    t = T;
    while(t || !isEmpty(c)){
        while(t){        //一直向左并将沿途节点访问（打印）后压入堆栈 
            fprintf(fp,"%d ",t->key);
            push(t, c);
            t = t->left;
        }
        if (!isEmpty(c)){
            fprintf(fp,"0 ");
            t = topAndpop(c);    //节点弹出堆栈
            t = t->right;  //转向右子树
        }
    }
}