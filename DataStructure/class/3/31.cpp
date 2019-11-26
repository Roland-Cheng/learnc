#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <iostream>
/*������ೣ��*/
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

#define EmptyTOS    -1  //��ջ
#define MinStackSize    5   //ջ����Сֵ

typedef TreeNode* StackElem;    //��������

typedef struct stackRecord
{
    int capacity;//����
    int stackTop;//ջ��
    StackElem *array; 
}STACK;

int isEmpty(STACK *s);  //�п�
int isFull(STACK *s);   //����
STACK *createStack(int maxElements);    //ջ�Ĵ���
void disposeStack(STACK *s);        //ջ���ͷ�
void makeEmpty(STACK *s);       //������ջ
void push(StackElem element, STACK *s);//��ջ
StackElem top(STACK *s);      //����ջ��Ԫ��
void pop(STACK *s);         //��ջ
StackElem topAndpop(STACK *s);    //��ջ������ջ��Ԫ��

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

//ջ�������

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
Node* treeelem[100];
int flag;
ElemType x; //����Ԫ�����ͣ���������֮�󲿷ֵ�����Ԫ�����
char string[100];  //���ڴ洢֮���ʹ�õ��ļ�����
FILE *fp;  //�����ļ�ָ�룬֮������ļ�����
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
    printf("      101.�洢����          102.��ȡ����\n");
    printf("��ѡ����Ĳ���:");
	scanf("%d",&op);
    switch(op)
    {
    case 1:
    for(i=0;i<50;i++) chongfus[i]=0;
    //for(i=0;i<50;i++) chongfu[i]=0;
    printf("���������Ľڵ������\n");
    scanf("%d",&n);
    printf("���������Ĺؼ��ֺ����ݣ��ÿո�ָ������н������֣���\n");
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
        printf("�������ظ��Ľ��\n");
        getchar();getchar();
        break;    
    }
        printf("���������Ĵ��ս����������:\n");
        for(i=1,flag=0;i<2*(n+1);i++){
            scanf("%d",&tree[i]);
            if(tree[i]){
                if (chongfus[tree[i]-1]==2) flag=1;
                else if (chongfus[tree[i]-1]==1) chongfus[tree[i]-1]++;
                else flag=2;
            }
        }
        if(flag==1){
            printf("�������ظ��Ľ��\n");
            getchar();getchar();
            break;
        }
        if(flag==2){
            printf("�����˲����ڵĽ��\n");
            getchar();getchar();
            break;
        }
        if(check(tree,n)==OK){
            printf("�����Դ���\n");
            for(i=0;i<n;i++) chongfu[i]=chongfus[i];
        }
        else printf("�������Դ���������������\n");    
    getchar();getchar();
    break;
    case 2:
    if(j) Ts[j-1]=T;
    printf("ѡ��Ҫ�л�������\n");
    for(k=0;k<30;k++) 
    if(Ts[k]!=NULL)
    printf("%d ",k+1);
    printf("\n");
    scanf("%d",&k);
    if(k<=0 || k>30) printf("��������ȷ��ֵ\n");
    else if(Ts[k-1]!=NULL){
        T=Ts[k-1];
        printf("�л��ɹ�\n");
        j=k;
    }
    else printf("�л�����������\n");
    getchar();getchar();
    break;
    case 3:
    if(j) Ts[j-1]=T;  //�Ƚ���ǰʹ�õ��������д���
    printf("������Ҫ�����ı�1~30��:\n");
    for(k=0;k<30;k++) 
    if(Ts[k]==NULL)
    printf("%d ",k+1);  //ʹ��forѭ���������ǰ�пɽ���������Ҳ���ǵ�ǰ��δ���ڵ���
    printf("\n");
    scanf("%d",&k);
    if(0<k&&k<=30){
        if(Ts[k-1]!=NULL){
            printf("���Ѿ�����\n");
            getchar();getchar();
            break;
        } 
        if(check(tree,n)==ERROR){
            printf("�������룬�޷�������\n");
            getchar();getchar();
            break;
        }
        if(CreateBiTree(T,tree,treeelem,n)) printf("�����ɹ�\n");j=k;
        //BiTreeTraverse(T);
    }
    else printf("��������ȷ��ֵ\n");
    getchar();getchar();
    break;
    case 4:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        getchar();
        printf("ȷ������������y/n��:\n");
        char c=getchar();
        if(c=='y') {
            if(DestroyBiTree(T)) printf("���ٳɹ�\n");
        }
        else printf("ֹͣ����\n");
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 5:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        getchar();
        printf("ȷ�����������y/n��:\n");
        char c=getchar();
        if(c=='y') {
            if(ClearBiTree(T)) printf("��ճɹ�\n");
        }
        else printf("ֹͣ���\n");
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 6:
    flag=BiTreeEmpty(T);
    if(flag==FALSE) printf("����Ϊ��\n");
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 7:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        int n=BiTreeDepth(T->left);
        printf("���Ĳ���Ϊ:%d",n);
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 8:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        printf("������Ҫ���ҵĹؼ���:\n");
        scanf("%d",&e);
            TreeNode* p=LocateNode(T->left,e);
            if(p)
            printf("�ý��洢��Ԫ����:%d\n",p->elem->e);
        else printf("���������ý��\n");
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 9:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        printf("������Ҫ���ҵĹؼ���:\n");
        scanf("%d",&e);
        printf("������Ҫ¼���Ԫ��:\n");
        scanf("%d",&x);
        //if(chongfu[e-1]){
            if(Assign(T->left,e,x))printf("���ĳɹ�\n");
            else printf("����ʧ��,���������ý��\n");
        //}
        //else printf("\n");
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 10:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        printf("������Ҫ���ҵĹؼ���:\n");
        scanf("%d",&e);
        if(chongfu[e-1]){
            TreeNode* p=GetSibling(T->left,e);
            if(p)
            printf("�ý���ֵܽ��Ϊ��%d\n�洢��Ԫ����:%d\n",p->key,p->elem->e);
            else printf("�ý��û���ֵܽ��\n");
        }
        else printf("���������ý��\n");
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 11:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        printf("��������Ҫ����λ�õĽ��:\n");
        scanf("%d",&e);
        if(chongfu[e-1]){
            int LR;
            int a;
            printf("������Ҫ�����λ�ã�������Ϊ0��������Ϊ1��:\n");
            scanf("%d",&LR);
            printf("������Ҫ����Ľ��ؼ��ֺ�Ԫ�أ�\n");
            scanf("%d%d",&a,&x);
            if(chongfu[a-1]==0){
                TreeNode *c=(TreeNode*)malloc(sizeof(TreeNode));
                c->elem=(Node*)malloc(sizeof(Node));
                c->elem->e=x;
                c->key=a;
                InsertNode(T->left,e,LR,c);
                printf("����ɹ�\n");
                T->key++;
                chongfu[a-1]=2;
            }
            else printf("����ظ�\n");
        }
        else printf("���������ý��\n");
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 12:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        printf("������Ҫɾ�����Ĺؼ��֣�\n");
        scanf("%d",&e);
        if(chongfu[e-1]) {
            DeleteNode(T,e);
            chongfu[e-1]=0;
            T->key--;
            printf("ɾ���ɹ�\n");
        }
        else printf("���������ý��\n");
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 13:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        PreOrderTraverse(T->left);
        printf("\nһ��%d��Ԫ��\n",T->key);
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 14:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        InOrderTraverse(T->left);
        printf("\nһ��%d��Ԫ��\n",T->key);
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 15:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        PostOrderTraverse(T->left);
        printf("\nһ��%d��Ԫ��\n",T->key);
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 16:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        LevelOrderTraverse(T->left);
        printf("\nһ��%d��Ԫ��\n",T->key);
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 101:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        printf("������Ҫ�洢���ļ���\n");
        scanf("%s",string);
        if((fp=fopen(string,"w"))==NULL){
            printf("���ļ�ʧ��\n");
            getchar();getchar();
            break;
        }
        fprintf(fp,"%d\n",T->key);
        preprint(fp,T->left);
        printf("�Ѿ�д���ļ�%s",string);
		fclose(fp);
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 102:
        printf("������Ҫ��ȡ���ļ���\n");
        scanf("%s",string);
        if((fp=fopen(string,"r"))==NULL){
            printf("��������ȷ���ļ�����ʧ��\n");
            getchar();getchar();
            break;
        }
        fscanf(fp,"%d",&n);
        for(i=0;i<n;i++){
            fscanf(fp,"%d",&k);
            treeelem[k-1]=(Node*)malloc(sizeof(Node));
            fscanf(fp,"%d",&(treeelem[k-1]->e));  
        }
        for(i=1;i<2*n;i++){
            fscanf(fp,"%d",&tree[i]);
        }
        printf("���Ѿ�������definition���봴����\n");
        fclose(fp);
    getchar();getchar();
    break;
    case 0:
    getchar();getchar();
    break;
    default:
    printf("��������ȷ��ֵ\n");
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
            printf("�����Դ���\n");
            break;
        }
        if(p==stackj&&(q!=tree+1&&tree!=tree+2*(n+1))){
            printf("�������Դ���\n");
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
            if(flag==1){ 
                t->right=(TreeNode*)malloc(sizeof(TreeNode));
                t->right->left=NULL;
                t->right->right=NULL;
                t->right->key=tree[i];
                t->right->elem=treeelem[tree[i]-1];
                push(t->right,c);
                t=t->right;
                flag=0;
            }
            else{
                t->left=(TreeNode*)malloc(sizeof(TreeNode));
                t->left->left=NULL;
                t->left->right=NULL;
                t->left->key=tree[i];
                t->left->elem=treeelem[tree[i]-1];
                push(t->left,c);
                t=t->left;
            }
        }
        else{
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
    STACK *c= createStack(50);    //��������ʼ����ջS
    while(t || !isEmpty(c)){
        while(t){        //һֱ���󲢽���;�ڵ���ʣ���ӡ����ѹ���ջ 
            printf("%d  %d\n", t->key,t->elem->e);
            push(t, c);
            t = t->left;
        }
        if (!isEmpty(c)){
            t = topAndpop(c);    //�ڵ㵯����ջ
            t = t->right;  //ת��������
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
        printf("��%d�㣺",j);
        _LevelOrderTraverse(T,j);
        printf("\n");
    }
    return OK;
}

status preprint(FILE *fp,TreeNode* T){
    TreeNode* t = T;
    STACK *c= createStack(50);    //��������ʼ����ջS
    while(t || !isEmpty(c)){
        while(t){        //һֱ���󲢽���;�ڵ���ʣ���ӡ����ѹ���ջ 
            fprintf(fp,"%d  %d\n", t->key,t->elem->e);
            push(t, c);
            t = t->left;
        }
        if (!isEmpty(c)){
            t = topAndpop(c);    //�ڵ㵯����ջ
            t = t->right;  //ת��������
        }
    }
    t = T;
    while(t || !isEmpty(c)){
        while(t){        //һֱ���󲢽���;�ڵ���ʣ���ӡ����ѹ���ջ 
            fprintf(fp,"%d ",t->key);
            push(t, c);
            t = t->left;
        }
        if (!isEmpty(c)){
            fprintf(fp,"0 ");
            t = topAndpop(c);    //�ڵ㵯����ջ
            t = t->right;  //ת��������
        }
    }
}