/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define INFEASTABLE -2
#define OVERFLOW -3
#define STOP -4

typedef int status; 
typedef int ElemType; //数据元素类型定义

typedef struct LNode{  //顺序表（顺序结构）的定义
	ElemType elem;
	struct LNode *next=NULL;
}LNode, *LinkList;

status InitList(LinkList& head);
status DestroyList(LinkList& head);
status ClearList(LinkList& haed);
status ListEmpty(LinkList head);
status ListLength(LinkList head);
status GetElem(LinkList head,int i,ElemType& e);
int LocateElem(LinkList head,ElemType e);
status PriorElem(LinkList head,ElemType cur,ElemType& pre_e);
status NextElem(LinkList head,ElemType cur,ElemType& next_e);
status ListInsert(LinkList& head,int i,ElemType e);
status ListDelete(LinkList& head,int i,ElemType& e);
status ListTrabverse(LinkList head);

int main(void){
LinkList head=NULL; int op=1; LinkList L[30]={NULL}; int j=0,flag,i,k;
ElemType e,x; char string[100]; FILE *fp;
while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. InitList      7. LocateElem\n");
	printf("    	  2. DestroyList   8. PriorElem\n");
	printf("    	  3. ClearList     9. NextElem \n");
	printf("    	  4. ListEmpty     10. ListInsert\n");
	printf("    	  5. ListLength    11. ListDelete\n");
	printf("    	  6. GetElem       12. ListTrabverse\n");
	printf("    	  13.Switch        0. Exit\n");
	printf("-------------------------------------------------\n");
    printf("          101.存储链表      102.读取链表\n");
	printf("    请选择你的操作[0~12]:");
	scanf("%d",&op);
    switch(op){
        case 1:
            if(j) L[j-1]=head;
			printf("请输入要创建的表（1~30）:\n");
			for(k=0;k<30;k++) 
			if(L[k]==NULL)
			printf("%d ",k+1);
			printf("\n");
			scanf("%d",&k);
			if(0<k&&k<=30){
				if(L[k-1]==NULL){
					if(InitList(head)==OK) {
						printf("链表创建成功！\n");
						j=k;
					}
					else printf("链表创建失败！\n");
				}
				else printf("链表已经创建，请重试\n");
			}
			else printf("请输入正确的值\n");
			getchar();getchar();
			break;
        case 2:
            DestroyList(head);    
            getchar();getchar();
            break;
        case 3:
            ClearList(head);    
            getchar();getchar();
            break;
        case 4:
            flag=ListEmpty(head);
			if(flag!=ERROR){
				if(flag==false) printf("表不为空\n");  //使用函数的返回值进行判断并输出
				else printf("表为空\n");
			}     
			getchar();getchar();
			break;
        case 5:
            flag=ListLength(head);
			if(flag>0)
			printf("链表的长度为%d\n",flag);   
			else if(flag==FALSE) printf("表为空\n");    //若函数的输出为error，由listlength的返回值知表为空
			getchar();getchar();
			break;
        case 6:
            if(!head){
                printf("链表不存在\n");
                getchar();getchar();
                break;
            }
            if(head->elem)
			printf("请输入位置值：（输入范围为1~%d）\n",head->elem);
			else printf("请输入位置值：\n");
			scanf("%d",&i);
			flag=GetElem(head,i,e);
			if(flag==FALSE)
			printf("链表为空\n");
			if(flag==OVERFLOW)
			printf("位置值不对哦,最大输入位置值为%d\n",head->elem); 
			if(flag==OK)
			printf("该位置的元素为：%d\n",e);   
			getchar();getchar();
			break;
        case 7:
            printf("请输入要查找的元素：\n");
			scanf("%d",&e);
			i=LocateElem(head,e);
			if(i!=ERROR) printf("该元素在第%d位\n",i);   
			getchar();getchar();
			break;
        case 8:
            printf("请输入要查找的元素：\n");
			scanf("%d",&e); 
			flag=PriorElem(head,e,x);
			if(flag!=ERROR) printf("该元素前一个元素为：%d\n",x);  
			getchar();getchar();
			break;
        case 9:
            printf("请输入要查找的元素：\n");
			scanf("%d",&e); 
			flag=NextElem(head,e,x);
			if(flag!=ERROR) printf("该元素后一个元素为：%d\n",x); 
			getchar();getchar();
            break;
        case 10:
            printf("请输入要插入的元素：\n");
			scanf("%d",&e);
			if(head)
			printf("请输入要插入的位置：（输入范围为1~%d）\n",head->elem+1);
			else printf("请输入要插入的位置：\n");
			scanf("%d",&i);
			flag=ListInsert(head,i,e);
			if (flag==OVERFLOW) printf("存储空间不够\n");
			else if(flag==OK) printf("插入成功\n"); 
			else if(flag==FALSE) printf("位置值不对哦,最大输入位置值为%d\n",head->elem+1); 
			getchar();getchar();
			break;
        case 11:
            if(!head){
                printf("链表不存在\n");
                getchar();getchar();
                break;
            }
            if(head->elem)
			printf("请输入要删除的位置：（输入范围为1~%d）\n",head->elem);
			else printf("请输入要删除的位置：\n");
			scanf("%d",&i);
			flag=ListDelete(head,i,e);
			if(flag==OK) printf("成功删除第%d位元素，其值为%d\n",i,e);
			else if(flag==FALSE) printf("位置值不对哦,最大输入位置值为%d\n",head->elem);   
			getchar();getchar();
			break;
        case 12:
            flag=ListTrabverse(head);  
			if(flag==FALSE) printf("链表是空表！\n");
			else if(flag!=ERROR) printf("一共是%d个元素\n",flag);
			getchar();getchar();
			break;
        case 13:
			if(j) L[j-1]=head;
			printf("选择要切换的表：\n");
			for(k=0;k<30;k++) 
			if(L[k]!=NULL)
			printf("%d ",k+1);
			printf("\n");
			scanf("%d",&k);
			if(k<=0 || k>30) printf("请输入正确的值\n");
			else if(L[k-1]!=NULL){
				head=L[k-1];
				printf("切换成功\n");
				j=k;
			}
			else printf("切换的表不存在\n");
			getchar();getchar();
			break;
		case 0:
			break;
		case 101:
            if(!head){
                printf("链表不存在\n");
                getchar();getchar();
                break;
            }
			printf("请输入要存储的文件\n");
			scanf("%s",string);
			if((fp=fopen(string,"w"))==NULL){
				printf("打开文件失败\n");
				getchar();getchar();
				break;
			}
            LinkList p;
			for(p=head->next;p;p=p->next) fprintf(fp," %d",p->elem);
			printf("已经写入文件%s",string);
			fclose(fp);
			getchar();getchar();
			break;
		case 102:
            if(!head){
                printf("链表不存在\n");
                getchar();getchar();
                break;
            }
			printf("请输入要读取的文件：\n");
			scanf("%s",string);
			if((fp=fopen(string,"r"))==NULL){
				printf("请输入正确的文件，打开失败\n");
				getchar();getchar();
				break;
			}
			while(!feof(fp)){
				fscanf(fp,"%d",&x);
				ListInsert(head,head->elem+1,x);	
			}
			fclose(fp);
			printf("文件元素已添加到链表末尾\n");
			getchar();getchar();
			break;
	}//end of switch
  }//end of while
printf("欢迎下次再使用本系统！\n");
}//end of main()

status InitList(LinkList& head){
    head=(LinkList)malloc(sizeof(LNode));
    if(head==NULL) return ERROR;
    head->elem=0;
    head->next=NULL;
    return OK;
}

status DestroyList(LinkList& head){
    LinkList p,q;
    if(ListEmpty(head)==ERROR) return ERROR;
    char c;
    getchar();
    printf("是否摧毁表？【y/n】\n");
    c=getchar();
    if(c!='y') return STOP;
    for(p=head;p;){
        q=p;
        p=p->next;
        free(q);
    }
    head=NULL;
    printf("摧毁成功\n");
    return OK;
}

status ClearList(LinkList& head){
    int flag=ListEmpty(head);
    if(flag==ERROR) return ERROR;
    if(flag==TRUE) printf("表已为空，无法清空\n");
    else{
        char c;int i;LinkList p,q;
        getchar();
        printf("是否清空表？【y/n】\n");
        c=getchar();
        if(c!='y'){
            printf("停止清空链表\n");
            return STOP;
        }
        for(p=head->next;p;){
            q=p;
            p=q->next;
            free(q);
        }
        head->next=NULL;
        head->elem=0;
        printf("成功清空链表\n");
        return OK;
    }
}

status ListEmpty(LinkList head){
    if(head==NULL){
        printf("链表不存在\n");
        return ERROR;
    }
    else if(!head->elem) return TRUE;
    else return FALSE;
}

status ListLength(LinkList head){
    int flag=ListEmpty(head);
    if(flag==ERROR) return ERROR;
    if(flag==TRUE) return FALSE;
    else return head->elem;
}

status GetElem(LinkList head,int i,ElemType& e){
    int flag=ListEmpty(head);
    if(flag==ERROR) return ERROR;
    if(flag==TRUE) return FALSE;
    else{
        if(i<=0||i>head->elem) return OVERFLOW;
        LinkList p;
        for(p=head;i;i--) p=p->next;
        e=p->elem;
    }
    return OK;
}

int LocateElem(LinkList head,ElemType e){
    int flag;
	flag=ListEmpty(head);
	if(flag!=ERROR){
		LinkList p;
        int i;
		for(p=head->next,i=1;p;p=p->next,i++)
			if(p->elem==e) return i;	
		printf("无法找到\n");
		if(flag==TRUE) printf("因为表为空\n");
		return ERROR;
	}
	else return ERROR;
}	

status PriorElem(LinkList head,ElemType cur,ElemType& pre_e){
    int i;
    i=LocateElem(head,cur);
    if(i!=ERROR){
        if(i>1){
            GetElem(head,i-1,pre_e);
            return OK;
        }
        else if(i==1) printf("该元素为首结点，没有前驱结点\n");
    }
    return ERROR;
}

status NextElem(LinkList head,ElemType cur,ElemType& next_e){
    int i;
    i=LocateElem(head,cur);
    if(i!=ERROR){
        if(i!=head->elem){
            GetElem(head,i+1,next_e);
            return OK;
        }
        else if(i==head->elem) printf("该元素为尾结点，没有后继结点\n");
    }
    return ERROR;
}

status ListInsert(LinkList& head,int i,ElemType e){
    if(ListEmpty(head)==ERROR) return ERROR;
	if(i<1||i>head->elem+1) return FALSE;
	LinkList p,q;
    for(p=head;i-1;i--) p=p->next;
    q=p;
    p=p->next;
    q->next=(LinkList)malloc(sizeof(LNode));
    if(!q) return OVERFLOW;
    q->next->elem=e;
    q->next->next=p;
    head->elem++;
    return OK;
}

status ListDelete(LinkList& head,int i,ElemType& e){
    if(ListEmpty(head)!=ERROR){
		if (i<1||i>ListLength(head)) return FALSE;
		LinkList p,q;
        for(p=head;i-1;i--) p=p->next;
        e=p->next->elem;
        q=p;
        p=p->next;
        q->next=p->next;
        free(p);
        head->elem--;
		return OK;
	}
	else return ERROR;
}

status ListTrabverse(LinkList head){
    int flag;
	flag=ListEmpty(head);
	if(flag==TRUE) return FALSE;
	else if(flag==ERROR) return ERROR;
    int i;
    LinkList p=head->next;
	printf("\n-----------all elements -----------------------\n");
	for(i=0;i<head->elem;i++,p=p->next) printf("%d ",p->elem);   //使用间隔分割输出的元素
	printf("\n------------------ end ------------------------\n");
	return head->elem;
}