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

typedef int ElemType; //������洢����������
typedef int status;  //���庯������ֵ����
typedef struct Node  //�������ݴ洢��㣬��ʵ���Լ���������ݣ�����Ϊ�����뷽�㣬�洢����
{
    ElemType e;
}Node;
typedef struct TreeNode  //�������Ļ�����㣬�����ؼ��֣����ҽ�㣬����ָ��
{
    int key=0;
    struct TreeNode *left=NULL,*right=NULL;
    Node* elem;  //ָ�����ݽ��
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
/*ջ�Ĺ���������ʵ���ϵ���󣬾ʹ˲�����ϸע����*/
int isEmpty(STACK *s)
{
    return (s->stackTop == EmptyTOS);
}

int isFull(STACK *s)
{
    return (s->stackTop == s->capacity -1);
}

STACK *createStack(int maxElements) //����������ջ
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

StackElem top(STACK *s) //����ջ��Ԫ��
{
    if(!isEmpty(s)) {
        return s->array[s->stackTop];   
    } else {
        printf("empty stack\n");
        return 0;
    }
}

void pop(STACK *s) //��ջ���ǲ����᷶������ֵ
{
    if(!isEmpty(s))
        s->stackTop--;  
    else
        printf("empty stack\n");
}

StackElem topAndpop(STACK *s) //��ջ������ջ��Ԫ��
{
    if(!isEmpty(s)) {
        return s->array[s->stackTop--];
    } else {
        printf("empty stack\n");    
        return 0;
    }
}

//ջ�������

status check(int *tree,int n); //���ڼ�������������������Ƿ���Դ���
status CreateBiTree(TreeNode* &T,int* tree,Node **treeelem,int n); //����������
status BiTreeTraverse(TreeNode* T); //�������2.0,���԰��ṹ�����
status _BiTreeTraverse(TreeNode* T,int i,ElemType* kiss); //����������õ��ĵݹ麯��
status DestroyBiTree(TreeNode* &T); //�ݻ���
status ClearBiTree (TreeNode* &T); //�����
status BiTreeEmpty(TreeNode* T); //�п�
status BiTreeDepth(TreeNode* T); //�������
TreeNode* LocateNode(TreeNode* T,int e); //���ҽ��
status Assign(TreeNode* &T,int e,ElemType value); //���Ľ��洢��ֵ
TreeNode* GetSibling(TreeNode* T,int e); //�ҵ��ֵܽڵ�
status InsertNode(TreeNode* &T,int e,int LR,TreeNode* &c); //������
status DeleteNode(TreeNode* &T,int e); //ɾ�����
TreeNode* GetParent(TreeNode* T,int e); //���Ҹ��ڵ�,����ɾ���������
status PreOrderTraverse(TreeNode* T);  //�������
status InOrderTraverse(TreeNode* T); //�������
status PostOrderTraverse(TreeNode* T); //�������
status LevelOrderTraverse(TreeNode* T); //�������1.0,ֻ�ܷ���ÿһ��ĺ���,���������ֹ�ϵ
status _LevelOrderTraverse(TreeNode* T,int i); //����������õ��ĵݹ麯��
status preprint(FILE *fp,TreeNode *T); //���ڴ洢�����ļ��е�����洢
int power(int i,int j); //��������i��j�η��ĺ���

int main(){
int op=1; //������
int i,j=0,k; //j������¼��ǰʹ�õ����������е���һ��
int n=0,e; //������������,�����ж϶������Ƿ�������
int tree[100]={0},treein[50]={0},treepre[50]={0},treepost[50]={0}; //�����洢�û�����������
int chongfu[50]={0}; //�����жϽ����ظ���
int stackj[50]={-1}; //αջ,֮�������ж����Ƿ���Դ���
int* p,* q; //���αջʹ�õ�ָ��
Node* treeelem[100]; //�����洢�������ݵĽṹָ������
int flag; //�ж���
ElemType x; //����Ԫ�����ͣ���������֮�󲿷ֵ�����Ԫ�����
char string[100];  //���ڴ洢֮���ʹ�õ��ļ�����
FILE *fp;  //�����ļ�ָ�룬֮������ļ�����
TreeNode* T=NULL; //��������
TreeNode* Ts[30]={NULL}; //�����洢����ָ������
while(op){
    system("cls"); printf("\n\n");
    /*�˵�����Ҫ����*/
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
    printf("      101.�洢������        102.��ȡ��\n");
    printf("��ѡ����Ĳ���:");
	scanf("%d",&op);
    switch(op)
    {
    case 1: //����������
    for(i=0;i<50;i++) chongfu[i]=0; //���������
    for(i=0;i<100;i++) tree[i]=0;
    printf("���������Ľڵ������\n");
    scanf("%d",&n); //�������Ľ����
    if(!n){ //�������0,��ֱ���˳�
        printf("�˳�\n");
        getchar();getchar();
        break;    
    }
    printf("���������Ĺؼ��ֺ����ݣ�0������Ϊ�ؼ��֣�ʾ�����£���\n������ؼ��֣��ո�ָ�������Ԫ�أ�1 20������������һ��\n");
    for(i=0,flag=0;i<n;i++){ //����Ҫ�����ؼ��ֺ�Ԫ��
        scanf("%d",&k);
        if(chongfu[k]==0) chongfu[k]++; //�ж��Ƿ������ظ����
        else flag++;
        treeelem[k-1]=(Node*)malloc(sizeof(Node)); //�������洢����,treeelem��λ�þ�����ؼ���
        scanf("%d",&treeelem[k-1]->e);
    }
    if(chongfu[0]){ //�������λ�þͶ�Ӧ�ؼ��ֳ��ֵĴ���,���������0,�ͻᱨ��
        printf("����������0Ϊ�ؼ���\n");
        getchar();getchar();
        break;    
    }
    if(flag){ //flag�����жϽ���Ƿ��Ѿ�����
        printf("�������ظ��Ľ��\n");
        getchar();getchar();
        break;    
    }
    printf("1.���������������\n2.���������\n3.����Ӻ���\n��ѡ������ķ�ʽ:");//��ʼѡ�����뷽ʽ
    scanf("%d",&i);
    if(i<1||i>3) printf("������ȷ��ֵ\n"); //��������
    if(i==1){
        printf("���������Ĵ��ս������������0��Ϊ��������:\n");
        for(i=1,flag=0;i<2*(n+1);i++){ //�����������ı�������tree�����д洢
            scanf("%d",&tree[i]);
            if(tree[i]){
                if (chongfu[tree[i]]==2) flag=1;//�ж��Ƿ������ظ����
                else if (chongfu[tree[i]]==1) chongfu[tree[i]]++;
                else flag=2; //����������������˲����ڵĹؼ���
            }
        }
        if(flag==1){ //�������
            printf("�������ظ��Ľ��\n");
            getchar();getchar();
            break;
        }
        if(flag==2){
            printf("�����˲����ڵĽ��\n");
            getchar();getchar();
            break;
        }
    }
    if(i==2){ //������������������,����ת��Ϊ�����������������
        flag=0;
        for(i=0;i<50;i++) treepre[i]=0; //�������
        for(i=0;i<50;i++) treein[i]=0;
        printf("�������������:\n");
        for(i=1;i<=n;i++){
            scanf("%d",&treepre[i]);
            if(chongfu[treepre[i]]==0) flag=1; //�ظ����ж�
            else if(chongfu[treepre[i]]==2) flag=2;
            else chongfu[treepre[i]]++;
        }
        printf("�������������:\n");
        for(i=1;i<=n;i++){
            scanf("%d",&treein[i]);
            if(chongfu[treein[i]]==0) flag=1;
            else if(chongfu[treein[i]]==3) flag=2;
            else chongfu[treein[i]]++;
        }
        if(flag==2){
            printf("�������ظ��Ľ��\n");
            getchar();getchar();
            break;
        }
        if(flag==1){
            printf("�����˲����ڵĽ��\n");
            getchar();getchar();
            break;  
        }
        int* treep =tree+1; //����ָ��,׼��ѭ��
        chongfu[0]=4; //��֤1�Žڵ��Ա��ܹ������ж��Ѿ�������
        chongfu[n+1]=4; //��֤n�Žڵ��Ա��ܹ������ж��Ѿ�������
        //for(i=0;i<=100;i++) tree[i]=0;
        for(i=1,flag=0;i<=n;i++){
            int abs=0;
            for(abs=1;;abs++){
                if(treepre[i]==treein[abs]){ //�������������������treepre[i]��ͬ�Ĺؼ���
                    chongfu[treein[abs]]++; //���ùؼ��ַ����Ѿ������Ķ�����
                    *treep=treepre[i]; //�������tree��
                    treep++; //��ָ
                    if(chongfu[treein[abs+1]]==4) flag++; //����ùؼ����������Ĺؼ����Ѿ�������,��flag++
                    if(chongfu[treein[abs-1]]==4) { //����ùؼ�������ǰ�Ĺؼ��ֱ�����
                        treep=treep+flag+1; //��ָ�����flag+1λ,������ʾ�ùؼ��ֺ�����˶��ٸ�������
                        flag=0;
                    }
                    break; //����������һ���ؼ���
                }
            }
        } //ѭ�����������������ӹ�Ϊ�����������������
    } 
    if(i==3){ //��������������Ϸ�
        flag=0;
        for(i=0;i<59;i++) treepre[i]=0;
        for(i=0;i<50;i++) treein[i]=0;
        for(i=0;i<50;i++) treepost[i]=0;
        printf("�������������:\n");
        for(i=n;i>=1;i--){ //��������������
            scanf("%d",&treein[i]);
            if(chongfu[treein[i]]==0) flag=1;
            else if(chongfu[treein[i]]==2) flag=2;
            else chongfu[treein[i]]++;
        }
        printf("������������:\n");
        for(i=n;i>=1;i--){ //�������������,����Ϊ�������,ת��Ϊ��������������
            scanf("%d",&treepost[i]);
            if(chongfu[treepost[i]]==0) flag=1;
            else if(chongfu[treepost[i]]==3) flag=2;
            else chongfu[treepost[i]]++;
        }
        if(flag==2){
            printf("�������ظ��Ľ��\n");
            getchar();getchar();
            break;
        }
        if(flag==1){
            printf("�����˲����ڵĽ��\n");
            getchar();getchar();
            break;
        }
        int* treep =tree+1;//�����˼������
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
        tree[0]=-1; //������ת�����������򹹽����������Ǿ����,������Ҫ��creat��������ж�,���ɾ�����
    }
    if(check(tree,n)==OK) printf("�����Դ���\n"); //�ж����Ƿ���Դ���
    else printf("�������Դ���������������\n");    
    getchar();getchar();
    break;
    case 2:
    if(j) Ts[j-1]=T; //����ǰʹ�õ����洢��������
    printf("ѡ��Ҫ�л�������\n"); //ͨ��ѭ���ķ�ʽ��������л�����
    for(k=0;k<30;k++) 
    if(Ts[k]!=NULL) //���ָ��ǿ�,�����������л�
    printf("%d ",k+1);
    printf("\n");
    scanf("%d",&k);
    if(k<=0 || k>30) printf("��������ȷ��ֵ\n"); //����ֵ��������
    else if(Ts[k-1]!=NULL){
        T=Ts[k-1];
        printf("�л��ɹ�\n"); //�������н�����ָ���������
        j=k;
    }
    else printf("�л�����������\n");
    getchar();getchar();
    break;
    case 3:
    if(j) Ts[j-1]=T;  //�Ƚ���ǰʹ�õ��������д���
    printf("������Ҫ����������1~30��:\n");
    for(k=0;k<30;k++) 
    if(Ts[k]==NULL)
    printf("%d ",k+1);  //ʹ��forѭ���������ǰ�пɽ���������Ҳ���ǵ�ǰ��δ���ڵ���
    printf("\n");
    scanf("%d",&k);
    if(0<k&&k<=30){
        if(Ts[k-1]!=NULL){
            printf("���Ѿ�����\n"); //�жϵ�ǰ�����ֵ����Ӧ�ĵ����Ƿ��Ѿ�����
            getchar();getchar();
            break;
        } 
        if(check(tree,n)==ERROR){ //�ٴμ���Ƿ���Դ�����
            printf("�������룬�޷�������\n");
            getchar();getchar();
            break;
        }
        if(CreateBiTree(T,tree,treeelem,n)) printf("�����ɹ�\n");j=k; //j����ǰʹ�õ����������е���һ����
        BiTreeTraverse(T->left); //�������Ժ�ʹ�ò������������ӡ����Ļ��
    }
    else printf("��������ȷ��ֵ\n");
    getchar();getchar();
    break;
    case 4:
    flag=BiTreeEmpty(T); //�����ж����Ƿ�Ϊ�����ڵ�
    if(flag!=ERROR){
        getchar();
        printf("ȷ������������y/n��:\n"); //���û�ȷ���Ƿ�ɾ����
        char c=getchar(); //��ȡ�û�������
        if(c=='y') {
            if(DestroyBiTree(T)==OK) printf("���ٳɹ�\n"); //������ֵ����,�������������
        }
        else printf("ֹͣ����\n"); //�������y������ַ��ͻ�ֹͣ����
    }
    if(flag==ERROR) printf("��������\n");
    getchar();getchar();
    break;
    case 5:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        getchar();
        printf("ȷ�����������y/n��:\n"); //���û�ȷ�������
        char c=getchar();
        if(c=='y') {
            if(ClearBiTree(T)==OK) printf("��ճɹ�\n"); //�����
        }
        else printf("ֹͣ���\n");
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 6:
    flag=BiTreeEmpty(T); //�пպ���
    if(flag==FALSE) printf("����Ϊ��\n"); 
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 7:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        int n=BiTreeDepth(T->left); //���ڴ���ͷ���,���Բ���ֱ������ͷ����ȥ,Ҫ�����׽��
        printf("���Ĳ���Ϊ:%d",n); //������Ĳ���
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
            TreeNode* p=LocateNode(T->left,e);//���ҽ��
            if(p) //���p��Ϊ��
            printf("�ý��洢��Ԫ����:%d\n",p->elem->e); //����洢��Ԫ�غ͹ؼ���
        else printf("���������ý��\n"); //pΪ��֤���Ҳ������
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
        if(Assign(T->left,e,x)==OK)printf("���ĳɹ�\n"); //�������������֤���ɹ���
        else printf("����ʧ��,���������ý��\n"); //��Ϊassign������ʹ��LocateNode,����Ҳ����᷵��ERROR
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
        if(LocateNode(T->left,e)){ //�����ڵ��ú���ǰ�ж��Ƿ��иýڵ�
            TreeNode* p=GetSibling(T->left,e); //���ú��������ֵܽڵ�
            if(p) //���p�ǿ�,�����ֵܽڵ�
            printf("�ý���ֵܽ��Ϊ��%d\n�洢��Ԫ����:%d\n",p->key,p->elem->e); //���ֵܽڵ������ؼ��ֺ�Ԫ��
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
        if(LocateNode(T->left,e)){
            int LR;
            int a;
            printf("������Ҫ�����λ�ã�������Ϊ0��������Ϊ1��:\n");
            scanf("%d",&LR); //�ж���������
            printf("������Ҫ����Ľ��ؼ��ֺ�Ԫ�أ�\n");
            scanf("%d%d",&a,&x);
            if(LocateNode(T->left,a)==NULL){  //�жϸո�����Ĺؼ����Ƿ��ظ�
                TreeNode *c=(TreeNode*)calloc(sizeof(TreeNode),1); //���û���ظ��Ͱ��չ������
                c->elem=(Node*)malloc(sizeof(Node));
                c->elem->e=x;
                c->key=a;
                InsertNode(T->left,e,LR,c);
                printf("����ɹ�\n"); //��ʾ����ɹ�
                T->key++; //��ͷ���Ľ�������һ
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
        if(LocateNode(T,e)==NULL) printf("���������ý��\n");
        else if(DeleteNode(T,e)==OK){
            T->key--; //��Ԫ�ظ�����һ
            printf("ɾ���ɹ�\n");
        }
        else printf("ɾ��ʧ��\n");
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 13:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        PreOrderTraverse(T->left); //�������
        printf("\nһ��%d��Ԫ��\n",T->key);
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 14:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        InOrderTraverse(T->left); //�������
        printf("\nһ��%d��Ԫ��\n",T->key);
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 15:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        PostOrderTraverse(T->left); //�������
        printf("\nһ��%d��Ԫ��\n",T->key);
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 16:
    flag=BiTreeEmpty(T);
    if(flag==FALSE){
        BiTreeTraverse(T->left); //��ʹ�ò������,��ʹ�������������ؼ��ֺ�Ԫ��֮��Ĺ�ϵ
        printf("\n");
        PreOrderTraverse(T->left);
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
        scanf("%s",string); //¼��Ҫ���ҵ�Ԫ��
        if((fp=fopen(string,"w"))==NULL){ //��ȷ��Ԫ�ؾͲ��ᱨ��
            printf("���ļ�ʧ��\n"); 
            getchar();getchar();
            break;
        }
        fprintf(fp,"%d\n",T->key); //���ú�����Ԫ�ظ�����¼��
        preprint(fp,T->left); //Ȼ���������,���ϴ����������������
        fprintf(fp,"0"); //�������һ��0,�������ѽ�������
        printf("�Ѿ�д���ļ�%s",string); //����ɹ�д��
		fclose(fp);  //�رմ򿪵��ļ�
    }
    if(flag==ERROR) printf("��������\n");
    if(flag==TRUE) printf("��Ϊ��\n");
    getchar();getchar();
    break;
    case 102:
        printf("������Ҫ��ȡ���ļ���\n");
        scanf("%s",string); //�����ļ�
        if((fp=fopen(string,"r"))==NULL){ //����ļ������ھ��޷���
            printf("��������ȷ���ļ�����ʧ��\n");
            getchar();getchar();
            break;
        }
        fscanf(fp,"%d",&n); //�ȶ���Ԫ�ظ���
        for(i=0;i<n;i++){
            fscanf(fp,"%d",&k); //����Ԫ�غ͹ؼ��ֵĹ�ϵ
            treeelem[k-1]=(Node*)malloc(sizeof(Node)); //�������ݴ洢�Ľ��
            fscanf(fp,"%d",&(treeelem[k-1]->e));  
        }
        for(i=1;i<=2*n+1;i++){
            fscanf(fp,"%d",&tree[i]); //��������������������
        }
        printf("���Ѿ�������definition���봴����\n"); //��ʾ�ɹ�����
        fclose(fp); 
    getchar();getchar();
    break;
    case 0:
    getchar();
    break;
    default:
    printf("��������ȷ��ֵ\n");
    getchar();getchar();
    break;
    }
}
printf("��ӭ�´���ʹ�ñ�ϵͳ��\n"); //����0�˳�ϵͳ
system("pause");
}

status check(int *tree,int n){
    if(n==0) return ERROR; //���û�н��ж���,n��Ϊ0,�жϵ�Ȼ����
    int i;
    int* p,* q;
    int stackj[100]; //αջ
    for(i=0,p=stackj,q=tree+1;i<2*(n+1)-1;i++){
        *p=*q; //��Ԫ��������ջ
        p++;
        q++;
        for(;*(p-1)==0;){ //����ջ��Ϊ0,Ҳ���Ƕ����˿�����
            if(p==stackj+1){ //ջ��
                p--; //��p����
                *p=-1;
                break; //�˳�ѭ��
            }
            if(*(p-2)==0){
                p--; //���ջ����Ԫ�ص���һλΪ��,��ջ��ҲΪ��,˵��,�ýڵ������������Ϊ��
                *p=-1; //��ջ
                p--; //��ջ
                *p=-1; 
                *(p-1)=0; //���ýڵ��λ���滻Ϊ������
            }
            else break; //����������������Ļ��Ϳ����˳�ѭ��
        }   
    }
    if(q==tree+2*(n+1)&&p==stackj) return OK; //���ջ��û�в�����Ԫ��,����tree�����е�Ԫ�ؾ�������һ��,֤������ÿһ���ڵ㶼����������
    else return ERROR; //�������,�Ǿ��ǲ����Դ�����
}

status CreateBiTree(TreeNode* &T,int* tree,Node** treeelem,int n){
    STACK *c;
    c=createStack(50);
    makeEmpty (c);
    int i,flag=0;
    T=(TreeNode*)calloc(sizeof(TreeNode),1); //�ȴ���ͷ���
    TreeNode* t=T;
    if(tree[0]==-1){ //����ж�Ϊ����Ӻ��������,�ʹ���������
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
    for(i=1;i<=2*n;i++){ //ѭ��2*n��,��Ϊ���������Ľ��ض���n������n+1��������
        if(tree[i]!=0){ //��Ϊ������
            if(flag==1){ //˵���ýڵ���������ѽ��������
                t->right=(TreeNode*)calloc(sizeof(TreeNode),1); //�ʹ����ýڵ��������
                t->right->key=tree[i];
                t->right->elem=treeelem[tree[i]-1];
                push(t->right,c); //����������ջ
                t=t->right;
                flag=0;
            }
            else{
                t->left=(TreeNode*)calloc(sizeof(TreeNode),1); //����������
                t->left->key=tree[i];
                t->left->elem=treeelem[tree[i]-1];
                push(t->left,c); //��������ջ
                t=t->left;
            }
        }
        else{
            t=topAndpop(c); //�������������,�ͳ�ջ,��������׼��������������
            flag=1; //������һ��ѭ���ô�����������
        }
    }
    T->key=n; //ͷ���洢Ԫ�ظ���
    T->right=T->left; //ͷ�������������϶�Ϊһ
    return OK;
}

status BiTreeTraverse(TreeNode* T){  //�������2.0
    int level=BiTreeDepth(T); //�õ��������
    int i,j,k,s,l,m=2;
    for(i=1;i<level;i++) m=2*m+4; //�ȼ��������ĸ��Ӻ��ܲ����Ĺ�ϵ
    TreeNode* t=T;
    ElemType kiss[50]={0}; //���ڴ洢ÿһ���Ԫ��,�����λ��Ԫ��,����0
    for(j=1;j<=level;j++){
        for(k=0;k<50;k++)kiss[k]=0; //ÿ���һ��,�����
        printf("��%d��:",j);//�ӵ�һ�㿪ʼ
        _BiTreeTraverse(T,j,kiss);
        for(k=0;k<3*(power(2,level-j)-1);k++) printf(" ");//�������֮������ո����
        for(l=0;l<power(2,j-1)-1;l++) {
            if(kiss[l])
            printf("%-4d",kiss[l]); //���ÿһ��Ԫ��
            else printf("    "); //Ϊ0֤��û��Ԫ��,���4���ո�
            for(i=0;i<m;i++) printf(" ");   //����ÿһ��Ԫ��֮���λ��
        }
        if(kiss[l])
            printf("%-4d\n",kiss[l]);
            else printf("    \n");
        m=(m-4)/2;//���������,��һ��Ԫ��֮��ļ��Ϊ44,�ڶ���Ϊ20,������Ϊ2
    }
}

status _BiTreeTraverse(TreeNode* T,int i,ElemType* kiss){
    if(T==NULL||i==0) return 0;
    ElemType *k=kiss;
    int j,s=1;
    for(j=1,s=1;j<i-1;j++)s*=2;
    if(i==1) *k=T->key; //���ؼ���¼����Ӧ��λ��
    else{
        _BiTreeTraverse(T->left,i-1,k);
        _BiTreeTraverse(T->right,i-1,k+s);//ÿһ�ζ���ϸ�ֲ�,��ÿһ����ָ֧���ָ��λ��
    }
    return OK;
}

status DestroyBiTree(TreeNode* &T){
    STACK *c;
    c=createStack(100);
    makeEmpty (c);
    TreeNode *t=T;
    for(push(t,c),t=t->left;isEmpty(c)==false;){ //������ջ
        if(t){
            push(t,c); //�����Ϊ�վ���ջ
            t=t->left;
        }
        else{
            t=top(c)->right; //����������
            free(topAndpop(c)); //Ȼ�󽫽�����
        }
    }
    free(T); //���ͷ���
    T=NULL;
    return OK;
}

status ClearBiTree (TreeNode* &T){
    STACK *c;
    c=createStack(100);
    makeEmpty (c);
    TreeNode *t=T->left;
    for(push(t,c),t=t->left;!isEmpty(c);){ //����һ����������
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
        if(T->key) return FALSE; //�ǿշ�����FALSE
        else return TRUE; //�շ���TRUE
    }
    else return ERROR; //�������ڷ���ERROR
}

status BiTreeDepth(TreeNode* T){
    if(T==NULL) return 0;
    else {
        int a,b;
        a=BiTreeDepth(T->left); //�����������
        b=BiTreeDepth(T->right); //�����������
        if(a>b) return a+1;
        else return b+1; //�Ƚϴ�С��ȡ��ļ�1
    }
}

TreeNode* LocateNode(TreeNode* T,int e){
    if(T==NULL) return NULL; //��������
    if(T->key==e) return T;  //�������˾ͷ��� 
    TreeNode* p=LocateNode(T->left,e);  //����������
    if(p!=NULL) return p; 
    else p=LocateNode(T->right,e); //����������
    return p;
}

status Assign(TreeNode* &T,int e,ElemType value){
    TreeNode *p=LocateNode(T,e);//��
    if(p) p->elem->e=value;//��
    else return ERROR;//����ֵ
    return OK;
}

TreeNode* GetSibling(TreeNode* T,int e){ //���ֵܽڵ�,�Ͳ��ҽ������
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

TreeNode* GetParent(TreeNode* T,int e){ //�Ҹ��ڵ�,�Ͳ��ҽ������
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
    TreeNode *p=LocateNode(T,e); //�ҽ��
    if(p==NULL) return ERROR; //�Ҳ���
    if(LR){ //֮���չ������
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
    TreeNode*p=GetParent(T,e); //�����Ҹ��ڵ�
    if(p==NULL) return ERROR;
    if(p->left!=NULL&&p->left->key==e){ //�ýڵ�Ϊ������
        TreeNode* q=p->left;
        if(q->left){ //����������
            TreeNode *s=q->left; 
            for(;s->right;s=s->right); //�ҵ����ҽ��
            s->right=q->right;//������������
            p->left=q->left; //�����ڵ����������
        }
        else p->left=q->right; //����ֱ�ӽ���������
        free(q); //�ͷŽ��
    }
    if(p->right!=NULL&&p->right->key==e) { //Ϊ������
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
    STACK *c= createStack(50);    //��������ʼ����ջc
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
    if(T==NULL) return 0;  //������ͷ����
    InOrderTraverse(T->left); //����������
    printf("%d  %d\n",T->key,T->elem->e); //���Ԫ��
    InOrderTraverse(T->right); //����������
}
 
status PostOrderTraverse(TreeNode* T){ //�������������
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
        printf("��%d��",j);
        _LevelOrderTraverse(T,j);
        printf("\n");
    }
    return OK;
}*/

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

int power(int i,int j){
    int k,s=1;
    for(k=0;k<j;k++) s*=i;
    return s;
}