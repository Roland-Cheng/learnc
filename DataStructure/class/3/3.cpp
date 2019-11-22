#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
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
    char key='@';
    struct TreeNode *left=NULL,*right=NULL;
    Node* elem;
}TreeNode;

status check(int* treepre,int* treein,int n);
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
ElemType e,x; //����Ԫ�����ͣ���������֮�󲿷ֵ�����Ԫ�����
char string[100];  //���ڴ洢֮���ʹ�õ��ļ�����
FILE *fp;  //�����ļ�ָ�룬֮������ļ�����
TreeNode* T=NULL;
TreeNode* Ts[30]={NULL};
while(op){
    
    system("cls"); printf("\n\n");
    printf("      Menu for Bitree On Sequence Structure \n");
	printf("-------------------------------------------------\n");
    printf("      1.DefineBiTree       2.\n");
    printf("      3.CreateBiTree       4.DestroyBiTree\n");
    printf("      5.ClearBiTree        6.BiTreeEmpty\n");
    printf("      6.BiTreeDepth        7.LocateNode\n");
    printf("      8.Assign             9.GetSibling\n");
    printf("      10.InsertNode        11.DeleteNode\n");
    printf("      12.PreOrderTraverse  13.InOrderTraverse\n");
    printf("      14.PostOrderTraverse 15.LevelOrderTraverse\n");
    printf("-------------------------------------------------\n");
    printf("      101.�洢����          102.��ȡ����\n");
    printf("��ѡ����Ĳ���[0~12]:");
	scanf("%d",&op);
    switch(op)
    {
    case 1:
    /*printf("���������Ľڵ������\n");
    scanf("%d",&n);
    for(i=0;i<n;i++) chongfu[i]=0;
    printf("���������Ĺؼ��ֺ����ݣ��ÿո�ָ������н������֣���\n");
    for(i=0;i<n;i++){
        scanf("%d",&j);
        if(chongfu[j-1]==0) chongfu[j-1]++;
        else{
            printf("�����ظ��ؼ���\n");
            scanf("%d",&j);
            goto tiaochu;
        }
        treeelem[j-1]=(Node*)malloc(sizeof(Node));
        scanf("%d",&treeelem[j-1]->e);
    }*/
    printf("����������������������\n");
    for(i=0;i<n;i++) scanf("%d",&treepre[i]);
    /*for(i=0;i<n;i++){
        if(chongfu[treepre[i]-1]==1) chongfu[treepre[i]-1]++;
        else if(chongfu[treepre[i]-1]==0){
            printf("������δ���ֵĹؼ���\n");
            goto tiaochu;
            }
        else {
            printf("�ظ��ؼ���\n");
            goto tiaochu;
        }
    }*/
    printf("����������������������\n");
    for(i=0;i<n;i++) scanf("%d",&treein[i]);
    /*for(i=0;i<n;i++){
        if(chongfu[treein[i]-1]==2) chongfu[treein[i]-1]++;
        else if(chongfu[treein[i]-1]==0){
            printf("������δ���ֵĹؼ���\n");
            goto tiaochu;
        }
        else {
            printf("�ظ��ؼ���\n");
            goto tiaochu;
        }
    }*/
    if(check(treepre,treein,n)) printf("���Դ�����\n");
    else printf("�޷�������\n");
tiaochu:    getchar();getchar();
    break;
    case 2:
        break;
    }
}
}

status check(int* treepre,int* treein,int n){
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
    return check(treepre+1,treein,i)&&check(treepre+1,treein+1+i,n-1-i);
}