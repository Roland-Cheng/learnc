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

typedef int ElemType; //定义结点存储的数据类型
typedef int status;  //定义函数返回值类型
typedef struct Node  //定义数据存储结点，其实可以加入更多数据，但是为了输入方便，存储整型
{
    ElemType e;
}Node;
typedef struct TreeNode  //定义树的基本结点，包含关键字，左右结点，数据指针
{
    int key=0;
    struct TreeNode *left=NULL,*right=NULL;
    Node* elem;  //指向数据结点
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

status check(int *tree,int n); //用于检查带空子树的先序遍历是否可以创建
status CreateBiTree(TreeNode* &T,int* tree,Node **treeelem,int n); //创建二叉树
status BiTreeTraverse(TreeNode* T); //层序遍历2.0,可以按结构输出树
status _BiTreeTraverse(TreeNode* T,int i,ElemType* kiss); //层序遍历中用到的递归函数
status DestroyBiTree(TreeNode* &T); //摧毁树
status ClearBiTree (TreeNode* &T); //清空树
status BiTreeEmpty(TreeNode* T); //判空
status BiTreeDepth(TreeNode* T); //树的深度
TreeNode* LocateNode(TreeNode* T,int e); //查找结点
status Assign(TreeNode* &T,int e,ElemType value); //更改结点存储的值
TreeNode* GetSibling(TreeNode* T,int e); //找到兄弟节点
status InsertNode(TreeNode* &T,int e,int LR,TreeNode* &c); //插入结点
status DeleteNode(TreeNode* &T,int e); //删除结点
TreeNode* GetParent(TreeNode* T,int e); //查找父节点,用在删除结点里面
status PreOrderTraverse(TreeNode* T);  //先序遍历
status InOrderTraverse(TreeNode* T); //中序遍历
status PostOrderTraverse(TreeNode* T); //后序遍历
status LevelOrderTraverse(TreeNode* T); //层序遍历1.0,只能返回每一层的函数,并不能体现关系
status _LevelOrderTraverse(TreeNode* T,int i); //层序遍历中用到的递归函数
status preprint(FILE *fp,TreeNode *T); //用在存储树到文件中的先序存储
int power(int i,int j); //用来计算i的j次方的函数

int main(){
int op=1; //操作数
int i,j=0,k; //j用来记录当前使用的树是数组中的哪一个
int n=0,e; //将结点个数归零,用来判断定义树是否有输入
int tree[100]={0},treein[50]={0},treepre[50]={0},treepost[50]={0}; //用来存储用户的树的输入
int chongfu[50]={0}; //用来判断结点的重复性
int stackj[50]={-1}; //伪栈,之后用来判断树是否可以创建
int* p,* q; //配合伪栈使用的指针
Node* treeelem[100]; //用来存储输入数据的结构指针数组
int flag; //判断数
ElemType x; //定义元素类型，用来进行之后部分的数据元素输出
char string[100];  //用于存储之后会使用的文件名称
FILE *fp;  //定义文件指针，之后进行文件操作
TreeNode* T=NULL; //定义主树
TreeNode* Ts[30]={NULL}; //用来存储树的指针数组
while(op){
    system("cls"); printf("\n\n");
    /*菜单的主要界面*/
    printf("      Menu for Bitree On Linked List \n");
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
    printf("      101.存储先序树        102.读取树\n");
    printf("请选择你的操作:");
	scanf("%d",&op);
    switch(op)
    {
    case 1: //定义树函数
    for(i=0;i<50;i++) chongfu[i]=0; //将数组归零
    for(i=0;i<100;i++) tree[i]=0;
    printf("请输入树的节点个数：\n");
    scanf("%d",&n); //读入树的结点树
    if(!n){ //如果输入0,就直接退出
        printf("退出\n");
        getchar();getchar();
        break;    
    }
    printf("请输入树的关键字和数据（0不能作为关键字，示例如下）：\n先输入关键字，空格分隔后输入元素（1 20）换行输入下一组\n");
    for(i=0,flag=0;i<n;i++){ //按照要求读入关键字和元素
        scanf("%d",&k);
        if(chongfu[k]==0) chongfu[k]++; //判断是否输入重复结点
        else flag++;
        treeelem[k-1]=(Node*)malloc(sizeof(Node)); //构建结点存储数据,treeelem的位置就是其关键字
        scanf("%d",&treeelem[k-1]->e);
    }
    if(chongfu[0]){ //该数组的位置就对应关键字出现的次数,如果输入了0,就会报错
        printf("不可以输入0为关键字\n");
        getchar();getchar();
        break;    
    }
    if(flag){ //flag用来判断结点是否已经创建
        printf("输入了重复的结点\n");
        getchar();getchar();
        break;    
    }
    printf("1.空子树的先序遍历\n2.先序加中序\n3.中序加后序\n请选择输入的方式:");//开始选择输入方式
    scanf("%d",&i);
    if(i<1||i>3) printf("输入正确的值\n"); //错误输入
    if(i==1){
        printf("请输入树的带空结点的先序遍历（0作为空子树）:\n");
        for(i=1,flag=0;i<2*(n+1);i++){ //将带空子树的遍历读入tree数组中存储
            scanf("%d",&tree[i]);
            if(tree[i]){
                if (chongfu[tree[i]]==2) flag=1;//判断是否输入重复结点
                else if (chongfu[tree[i]]==1) chongfu[tree[i]]++;
                else flag=2; //其他情况就是输入了不存在的关键字
            }
        }
        if(flag==1){ //错误输出
            printf("输入了重复的结点\n");
            getchar();getchar();
            break;
        }
        if(flag==2){
            printf("输入了不存在的结点\n");
            getchar();getchar();
            break;
        }
    }
    if(i==2){ //输入了先序加中序遍历,将其转化为带空子树的先序遍历
        flag=0;
        for(i=0;i<50;i++) treepre[i]=0; //清空数组
        for(i=0;i<50;i++) treein[i]=0;
        printf("请输入先序遍历:\n");
        for(i=1;i<=n;i++){
            scanf("%d",&treepre[i]);
            if(chongfu[treepre[i]]==0) flag=1; //重复性判断
            else if(chongfu[treepre[i]]==2) flag=2;
            else chongfu[treepre[i]]++;
        }
        printf("请输入中序遍历:\n");
        for(i=1;i<=n;i++){
            scanf("%d",&treein[i]);
            if(chongfu[treein[i]]==0) flag=1;
            else if(chongfu[treein[i]]==3) flag=2;
            else chongfu[treein[i]]++;
        }
        if(flag==2){
            printf("输入了重复的结点\n");
            getchar();getchar();
            break;
        }
        if(flag==1){
            printf("输入了不存在的结点\n");
            getchar();getchar();
            break;  
        }
        int* treep =tree+1; //创建指针,准备循环
        chongfu[0]=4; //保证1号节点旁边能够正常判定已经遍历过
        chongfu[n+1]=4; //保证n号节点旁边能够正常判定已经遍历过
        //for(i=0;i<=100;i++) tree[i]=0;
        for(i=1,flag=0;i<=n;i++){
            int abs=0;
            for(abs=1;;abs++){
                if(treepre[i]==treein[abs]){ //查找中序遍历数组中与treepre[i]相同的关键字
                    chongfu[treein[abs]]++; //将该关键字放入已经遍历的队伍中
                    *treep=treepre[i]; //将其存入tree中
                    treep++; //后指
                    if(chongfu[treein[abs+1]]==4) flag++; //如果该关键字中序后面的关键字已经遍历了,则flag++
                    if(chongfu[treein[abs-1]]==4) { //如果该关键字中序前的关键字遍历了
                        treep=treep+flag+1; //将指针后移flag+1位,用来表示该关键字后面跟了多少个空子树
                        flag=0;
                    }
                    break; //找先序中下一个关键字
                }
            }
        } //循环结束后将先序加中序加工为带空子树的先序遍历
    } 
    if(i==3){ //后序加中序类似上法
        flag=0;
        for(i=0;i<59;i++) treepre[i]=0;
        for(i=0;i<50;i++) treein[i]=0;
        for(i=0;i<50;i++) treepost[i]=0;
        printf("请输入中序遍历:\n");
        for(i=n;i>=1;i--){ //逆序读入中序遍历
            scanf("%d",&treein[i]);
            if(chongfu[treein[i]]==0) flag=1;
            else if(chongfu[treein[i]]==2) flag=2;
            else chongfu[treein[i]]++;
        }
        printf("请输入后序遍历:\n");
        for(i=n;i>=1;i--){ //逆序读入后序遍历,并作为先序遍历,转化为带空子树的先序
            scanf("%d",&treepost[i]);
            if(chongfu[treepost[i]]==0) flag=1;
            else if(chongfu[treepost[i]]==3) flag=2;
            else chongfu[treepost[i]]++;
        }
        if(flag==2){
            printf("输入了重复的结点\n");
            getchar();getchar();
            break;
        }
        if(flag==1){
            printf("输入了不存在的结点\n");
            getchar();getchar();
            break;
        }
        int* treep =tree+1;//后面的思想类似
        chongfu[0]=4;
        chongfu[n+1]=4;
        //for(i=0;i<=100;i++) tree[i]=0;
        for(i=1,flag=0;i<=n;i++){
            int abs=0;
            for(abs=1;;abs++){
                if(treepost[i]==treein[abs]){
                    chongfu[treein[abs]]++;
                    *treep=treepost[i];
                    treep++;
                    if(chongfu[treein[abs+1]]==4) flag++;
                    if(chongfu[treein[abs-1]]==4) {
                        treep=treep+flag+1;
                        flag=0;
                    }
                    break;
                }
            }
        }
        tree[0]=-1; //像这样转化出来的先序构建出来的树是镜像的,后面需要在creat里面进行判断,生成镜像树
    }
    if(check(tree,n)==OK) printf("树可以创建\n"); //判断树是否可以创建
    else printf("树不可以创建，请重新输入\n");    
    getchar();getchar();
    break;
    case 2:
    if(j) Ts[j-1]=T; //将当前使用的树存储到数组中
    printf("选择要切换的树：\n"); //通过循环的方式输出可以切换的树
    for(k=0;k<30;k++) 
    if(Ts[k]!=NULL) //如果指针非空,代表树可以切换
    printf("%d ",k+1);
    printf("\n");
    scanf("%d",&k);
    if(k<=0 || k>30) printf("请输入正确的值\n"); //输入值超过限制
    else if(Ts[k-1]!=NULL){
        T=Ts[k-1];
        printf("切换成功\n"); //从数组中将树的指针读到主树
        j=k;
    }
    else printf("切换的树不存在\n");
    getchar();getchar();
    break;
    case 3:
    if(j) Ts[j-1]=T;  //先将当前使用的主树进行储存
    printf("请输入要创建的树（1~30）:\n");
    for(k=0;k<30;k++) 
    if(Ts[k]==NULL)
    printf("%d ",k+1);  //使用for循环，输出当前尚可建立的树，也就是当前尚未存在的树
    printf("\n");
    scanf("%d",&k);
    if(0<k&&k<=30){
        if(Ts[k-1]!=NULL){
            printf("树已经创建\n"); //判断当前输入的值所对应的的树是否已经创建
            getchar();getchar();
            break;
        } 
        if(check(tree,n)==ERROR){ //再次检查是否可以创建树
            printf("请检查输入，无法创建树\n");
            getchar();getchar();
            break;
        }
        if(CreateBiTree(T,tree,treeelem,n)) printf("创建成功\n");j=k; //j代表当前使用的树是数组中的哪一棵树
        BiTreeTraverse(T->left); //创建完以后使用层序遍历将树打印到屏幕上
    }
    else printf("请输入正确的值\n");
    getchar();getchar();
    break;
    case 4:
    flag=BiTreeEmpty(T); //首先判断树是否为不存在的
    if(flag!=ERROR){
        getchar();
        printf("确认销毁树？（y/n）:\n"); //向用户确认是否删除树
        char c=getchar(); //读取用户的输入
        if(c=='y') {
            if(DestroyBiTree(T)==OK) printf("销毁成功\n"); //若返回值正常,则代表正常销毁
        }
        else printf("停止销毁\n"); //输入除了y以外的字符就会停止销毁
    }
    if(flag==ERROR) printf("树不存在\n");
    getchar();getchar();
    break;
    case 5:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        getchar();
        printf("确认清空树？（y/n）:\n"); //向用户确认清空树
        char c=getchar();
        if(c=='y') {
            if(ClearBiTree(T)==OK) printf("清空成功\n"); //清空树
        }
        else printf("停止清空\n");
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 6:
    flag=BiTreeEmpty(T); //判空函数
    if(flag==FALSE) printf("树不为空\n"); 
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 7:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        int n=BiTreeDepth(T->left); //由于带有头结点,所以不能直接输入头结点进去,要输入首结点
        printf("树的层数为:%d",n); //输出树的层数
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
            TreeNode* p=LocateNode(T->left,e);//查找结点
            if(p) //如果p不为空
            printf("该结点存储的元素是:%d\n",p->elem->e); //输出存储的元素和关键字
        else printf("搜索不到该结点\n"); //p为空证明找不到结点
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
        if(Assign(T->left,e,x)==OK)printf("更改成功\n"); //如果更改正常就证明成功了
        else printf("更改失败,搜索不到该结点\n"); //因为assign函数会使用LocateNode,如果找不到会返回ERROR
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
        if(LocateNode(T->left,e)){ //首先在调用函数前判断是否有该节点
            TreeNode* p=GetSibling(T->left,e); //调用函数查找兄弟节点
            if(p) //如果p非空,就有兄弟节点
            printf("该结点兄弟结点为：%d\n存储的元素是:%d\n",p->key,p->elem->e); //有兄弟节点就输出关键字和元素
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
        if(LocateNode(T->left,e)){
            int LR;
            int a;
            printf("请输入要插入的位置（左子树为0，右子树为1）:\n");
            scanf("%d",&LR); //判断左右子树
            printf("请输入要输入的结点关键字和元素：\n");
            scanf("%d%d",&a,&x);
            if(LocateNode(T->left,a)==NULL){  //判断刚刚输入的关键字是否重复
                TreeNode *c=(TreeNode*)calloc(sizeof(TreeNode),1); //如果没有重复就按照规则插入
                c->elem=(Node*)malloc(sizeof(Node));
                c->elem->e=x;
                c->key=a;
                InsertNode(T->left,e,LR,c);
                printf("插入成功\n"); //提示插入成功
                T->key++; //将头结点的结点个数加一
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
        if(LocateNode(T,e)==NULL) printf("搜索不到该结点\n");
        else if(DeleteNode(T,e)==OK){
            T->key--; //将元素个数减一
            printf("删除成功\n");
        }
        else printf("删除失败\n");
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 13:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        PreOrderTraverse(T->left); //先序遍历
        printf("\n一共%d个元素\n",T->key);
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 14:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        InOrderTraverse(T->left); //中序遍历
        printf("\n一共%d个元素\n",T->key);
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 15:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        PostOrderTraverse(T->left); //后序遍历
        printf("\n一共%d个元素\n",T->key);
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 16:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        BiTreeTraverse(T->left); //先使用层序遍历,后使用先序遍历输出关键字和元素之间的关系
        printf("\n");
        PreOrderTraverse(T->left);
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
        scanf("%s",string); //录入要查找的元素
        if((fp=fopen(string,"w"))==NULL){ //正确打开元素就不会报错
            printf("打开文件失败\n"); 
            getchar();getchar();
            break;
        }
        fprintf(fp,"%d\n",T->key); //调用函数将元素个数先录入
        preprint(fp,T->left); //然后先序遍历,加上带空子树的先序遍历
        fprintf(fp,"0"); //最后输入一个0,代表树已将创建完
        printf("已经写入文件%s",string); //输出成功写入
		fclose(fp);  //关闭打开的文件
    }
    if(flag==ERROR) printf("树不存在\n");
    if(flag==TRUE) printf("树为空\n");
    getchar();getchar();
    break;
    case 102:
        printf("请输入要读取的文件：\n");
        scanf("%s",string); //读入文件
        if((fp=fopen(string,"r"))==NULL){ //如果文件不存在就无法打开
            printf("请输入正确的文件，打开失败\n");
            getchar();getchar();
            break;
        }
        fscanf(fp,"%d",&n); //先读入元素个数
        for(i=0;i<n;i++){
            fscanf(fp,"%d",&k); //读入元素和关键字的关系
            treeelem[k-1]=(Node*)malloc(sizeof(Node)); //构造数据存储的结点
            fscanf(fp,"%d",&(treeelem[k-1]->e));  
        }
        for(i=1;i<=2*n+1;i++){
            fscanf(fp,"%d",&tree[i]); //读入带空子树的先序遍历
        }
        printf("树已经读入了definition，请创建树\n"); //提示成功读入
        fclose(fp); 
    getchar();getchar();
    break;
    case 0:
    getchar();
    break;
    default:
    printf("请输入正确的值\n");
    getchar();getchar();
    break;
    }
}
printf("欢迎下次再使用本系统！\n"); //输入0退出系统
system("pause");
}

status check(int *tree,int n){
    if(n==0) return ERROR; //如果没有进行定义,n就为0,判断当然出错
    int i;
    int* p,* q;
    int stackj[100]; //伪栈
    for(i=0,p=stackj,q=tree+1;i<2*(n+1)-1;i++){
        *p=*q; //将元素依次入栈
        p++;
        q++;
        for(;*(p-1)==0;){ //遇到栈顶为0,也就是读入了空子树
            if(p==stackj+1){ //栈空
                p--; //将p归零
                *p=-1;
                break; //退出循环
            }
            if(*(p-2)==0){
                p--; //如果栈顶的元素的上一位为空,且栈顶也为空,说明,该节点的两个子树均为空
                *p=-1; //出栈
                p--; //出栈
                *p=-1; 
                *(p-1)=0; //将该节点的位置替换为空子树
            }
            else break; //处理完连续两个零的话就可以退出循环
        }   
    }
    if(q==tree+2*(n+1)&&p==stackj) return OK; //如果栈内没有残留的元素,而且tree中所有的元素均遍历过一遍,证明树的每一个节点都是有子树的
    else return ERROR; //如果不是,那就是不可以创建树
}

status CreateBiTree(TreeNode* &T,int* tree,Node** treeelem,int n){
    STACK *c;
    c=createStack(50);
    makeEmpty (c);
    int i,flag=0;
    T=(TreeNode*)calloc(sizeof(TreeNode),1); //先创建头结点
    TreeNode* t=T;
    if(tree[0]==-1){ //如果判断为中序加后序输入的,就创建镜像树
        for(i=1;i<=2*n;i++){
            if(tree[i]!=0){
                if(flag==1){
                    t->left=(TreeNode*)calloc(sizeof(TreeNode),1);
                    t->left->key=tree[i];
                    t->left->elem=treeelem[tree[i]-1];
                    push(t->left,c);
                    t=t->left;
                    flag=0;
                }
                else{
                    t->right=(TreeNode*)calloc(sizeof(TreeNode),1);
                    t->right->key=tree[i];
                    t->right->elem=treeelem[tree[i]-1];
                    push(t->right,c);
                    t=t->right;
                }
            }
            else{
                t=topAndpop(c);
                flag=1;
            }
        }
        T->key=n;
        T->left=T->right;
        return OK;
    }
    for(i=1;i<=2*n;i++){ //循环2*n次,因为带空子树的结点必定有n个结点加n+1个空子树
        if(tree[i]!=0){ //不为空子树
            if(flag==1){ //说明该节点的左子树已将创建完成
                t->right=(TreeNode*)calloc(sizeof(TreeNode),1); //就创建该节点的右子树
                t->right->key=tree[i];
                t->right->elem=treeelem[tree[i]-1];
                push(t->right,c); //将右子树入栈
                t=t->right;
                flag=0;
            }
            else{
                t->left=(TreeNode*)calloc(sizeof(TreeNode),1); //创建左子树
                t->left->key=tree[i];
                t->left->elem=treeelem[tree[i]-1];
                push(t->left,c); //左子树入栈
                t=t->left;
            }
        }
        else{
            t=topAndpop(c); //如果遇到空子树,就出栈,并接下来准备构建其右子树
            flag=1; //告诉下一个循环该创建右子树了
        }
    }
    T->key=n; //头结点存储元素个数
    T->right=T->left; //头结点的左右子树合二为一
    return OK;
}

status BiTreeTraverse(TreeNode* T){  //按层遍历2.0
    int level=BiTreeDepth(T); //得到树的深度
    int i,j,k,s,l,m=2;
    for(i=1;i<level;i++) m=2*m+4; //先计算好输出的格子和总层数的关系
    TreeNode* t=T;
    ElemType kiss[50]={0}; //用于存储每一层的元素,如果该位置元素,就是0
    for(j=1;j<=level;j++){
        for(k=0;k<50;k++)kiss[k]=0; //每输出一层,就清空
        printf("第%d层:",j);//从第一层开始
        _BiTreeTraverse(T,j,kiss);
        for(k=0;k<3*(power(2,level-j)-1);k++) printf(" ");//现在输出之间调整空格输出
        for(l=0;l<power(2,j-1)-1;l++) {
            if(kiss[l])
            printf("%-4d",kiss[l]); //输出每一行元素
            else printf("    "); //为0证明没有元素,输出4个空格
            for(i=0;i<m;i++) printf(" ");   //调整每一个元素之间的位置
        }
        if(kiss[l])
            printf("%-4d\n",kiss[l]);
            else printf("    \n");
        m=(m-4)/2;//如果有三层,第一层元素之间的间隔为44,第二层为20,第三层为2
    }
}

status _BiTreeTraverse(TreeNode* T,int i,ElemType* kiss){
    if(T==NULL||i==0) return 0;
    ElemType *k=kiss;
    int j,s=1;
    for(j=1,s=1;j<i-1;j++)s*=2;
    if(i==1) *k=T->key; //将关键字录入相应的位置
    else{
        _BiTreeTraverse(T->left,i-1,k);
        _BiTreeTraverse(T->right,i-1,k+s);//每一次都能细分层,让每一个分支指向该指的位置
    }
    return OK;
}

status DestroyBiTree(TreeNode* &T){
    STACK *c;
    c=createStack(100);
    makeEmpty (c);
    TreeNode *t=T;
    for(push(t,c),t=t->left;isEmpty(c)==false;){ //依次入栈
        if(t){
            push(t,c); //如果不为空就如栈
            t=t->left;
        }
        else{
            t=top(c)->right; //处理右子树
            free(topAndpop(c)); //然后将结点清空
        }
    }
    free(T); //清空头结点
    T=NULL;
    return OK;
}

status ClearBiTree (TreeNode* &T){
    STACK *c;
    c=createStack(100);
    makeEmpty (c);
    TreeNode *t=T->left;
    for(push(t,c),t=t->left;!isEmpty(c);){ //和上一个函数类似
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
        if(T->key) return FALSE; //非空发返回FALSE
        else return TRUE; //空返回TRUE
    }
    else return ERROR; //树不存在返回ERROR
}

status BiTreeDepth(TreeNode* T){
    if(T==NULL) return 0;
    else {
        int a,b;
        a=BiTreeDepth(T->left); //左子树的深度
        b=BiTreeDepth(T->right); //右子树的深度
        if(a>b) return a+1;
        else return b+1; //比较大小后取大的加1
    }
}

TreeNode* LocateNode(TreeNode* T,int e){
    if(T==NULL) return NULL; //搜索不到
    if(T->key==e) return T;  //搜索到了就返回 
    TreeNode* p=LocateNode(T->left,e);  //搜索左子树
    if(p!=NULL) return p; 
    else p=LocateNode(T->right,e); //搜索右子树
    return p;
}

status Assign(TreeNode* &T,int e,ElemType value){
    TreeNode *p=LocateNode(T,e);//找
    if(p) p->elem->e=value;//该
    else return ERROR;//返回值
    return OK;
}

TreeNode* GetSibling(TreeNode* T,int e){ //找兄弟节点,和查找结点类似
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
    return NULL;
}

TreeNode* GetParent(TreeNode* T,int e){ //找父节点,和查找结点类似
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
    return NULL;
}

status InsertNode(TreeNode* &T,int e,int LR,TreeNode* &c){
    TreeNode *p=LocateNode(T,e); //找结点
    if(p==NULL) return ERROR; //找不到
    if(LR){ //之后按照规则插入
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
    TreeNode*p=GetParent(T,e); //首先找父节点
    if(p==NULL) return ERROR;
    if(p->left!=NULL&&p->left->key==e){ //该节点为左子树
        TreeNode* q=p->left;
        if(q->left){ //存在左子树
            TreeNode *s=q->left; 
            for(;s->right;s=s->right); //找到最右结点
            s->right=q->right;//将右子树接上
            p->left=q->left; //将父节点接上左子树
        }
        else p->left=q->right; //否则直接接上右子树
        free(q); //释放结点
    }
    if(p->right!=NULL&&p->right->key==e) { //为右子树
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
    return OK;
}

status PreOrderTraverse(TreeNode* T){
    TreeNode* t = T;
    STACK *c= createStack(50);    //创建并初始化堆栈c
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
    if(T==NULL) return 0;  //遍历到头返回
    InOrderTraverse(T->left); //遍历左子树
    printf("%d  %d\n",T->key,T->elem->e); //输出元素
    InOrderTraverse(T->right); //遍历右子树
}
 
status PostOrderTraverse(TreeNode* T){ //和中序遍历类似
    if(T==NULL) return 0;
    PostOrderTraverse(T->left);
    PostOrderTraverse(T->right);
    printf("%d  %d\n",T->key,T->elem->e);
}

/*status _LevelOrderTraverse(TreeNode* T,int i){
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
        printf("第%d层",j);
        _LevelOrderTraverse(T,j);
        printf("\n");
    }
    return OK;
}*/

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

int power(int i,int j){
    int k,s=1;
    for(k=0;k<j;k++) s*=i;
    return s;
}