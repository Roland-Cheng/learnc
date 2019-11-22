/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
/*������ೣ��*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define INFEASTABLE -2
#define OVERFLOW -3
#define STOP -4

typedef int status; 
typedef int ElemType; //����Ԫ�����Ͷ���

typedef struct LNode{  //����˳��ṹ�����Ķ���
	ElemType elem;
	struct LNode *next=NULL;
}LNode, *LinkList;

/*���к�����������֮����������֮�����й����*/
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
LinkList head=NULL; 
LinkList L[30]={NULL}; //��������head�����ڴ洢��ָ���ָ������L
int op=1;  //���������
int j=0,flag,i,k;  //����i���ڻ�����ѭ��������j����ָʾ��ǰ�ı�Ϊ�ڼ��ţ�����k��������j
ElemType e,x; //����Ԫ�����ͣ���������֮�󲿷ֵ�����Ԫ�����
char string[100];  //���ڴ洢֮���ʹ�õ��ļ�����
FILE *fp;  //�����ļ�ָ�룬֮������ļ�����
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
    printf("          101.�洢����      102.��ȡ����\n");
	printf("��ѡ����Ĳ���[0~12]:");
	scanf("%d",&op);
    switch(op){
        case 1:
            if(j) L[j-1]=head;  //�Ƚ���ǰʹ�õ�������д���
			printf("������Ҫ�����ı�1~30��:\n");
			for(k=0;k<30;k++) 
			if(L[k]==NULL)
			printf("%d ",k+1);  //ʹ��forѭ���������ǰ�пɽ��������Ա�Ҳ���ǵ�ǰ��δ���ڵı�
			printf("\n");
			scanf("%d",&k);
			if(0<k&&k<=30){
				if(L[k-1]==NULL){
					if(InitList(head)==OK) {
						printf("�������ɹ���\n");
						j=k;
					}
					else printf("������ʧ�ܣ�\n");
				}
				else printf("�����Ѿ�������������\n");
			}
			else printf("��������ȷ��ֵ\n");
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
				if(flag==false) printf("��Ϊ��\n");  //ʹ�ú����ķ���ֵ�����жϲ����
				else printf("��Ϊ��\n");
			}     
			getchar();getchar();
			break;
        case 5:
            flag=ListLength(head);
			if(flag>0)
			printf("����ĳ���Ϊ%d\n",flag);   
			else if(flag==FALSE) printf("��Ϊ��\n");    //�����������Ϊerror����listlength�ķ���ֵ֪��Ϊ��
			getchar();getchar();
			break;
        case 6:
            if(!head){
                printf("��������\n");
                getchar();getchar();
                break;
            }
            if(head->elem)
			printf("������λ��ֵ�������뷶ΧΪ1~%d��\n",head->elem);
			else printf("������λ��ֵ��\n");
			scanf("%d",&i);
			flag=GetElem(head,i,e);
			if(flag==FALSE)
			printf("����Ϊ��\n");
			if(flag==OVERFLOW)
			printf("λ��ֵ����Ŷ,�������λ��ֵΪ%d\n",head->elem); 
			if(flag==OK)
			printf("��λ�õ�Ԫ��Ϊ��%d\n",e);   
			getchar();getchar();
			break;
        case 7:
            printf("������Ҫ���ҵ�Ԫ�أ�\n");
			scanf("%d",&e);
			i=LocateElem(head,e);
			if(i!=ERROR) printf("��Ԫ���ڵ�%dλ\n",i);   
			getchar();getchar();
			break;
        case 8:
            printf("������Ҫ���ҵ�Ԫ�أ�\n");
			scanf("%d",&e); 
			flag=PriorElem(head,e,x);
			if(flag!=ERROR) printf("��Ԫ��ǰһ��Ԫ��Ϊ��%d\n",x);  
			getchar();getchar();
			break;
        case 9:
            printf("������Ҫ���ҵ�Ԫ�أ�\n");
			scanf("%d",&e); 
			flag=NextElem(head,e,x);
			if(flag!=ERROR) printf("��Ԫ�غ�һ��Ԫ��Ϊ��%d\n",x); 
			getchar();getchar();
            break;
        case 10:
            printf("������Ҫ�����Ԫ�أ�\n");
			scanf("%d",&e);
			if(head)
			printf("������Ҫ�����λ�ã������뷶ΧΪ1~%d��\n",head->elem+1);
			else printf("������Ҫ�����λ�ã�\n");
			scanf("%d",&i);
			flag=ListInsert(head,i,e);
			if (flag==OVERFLOW) printf("�洢�ռ䲻��\n");
			else if(flag==OK) printf("����ɹ�\n"); 
			else if(flag==FALSE) printf("λ��ֵ����Ŷ,�������λ��ֵΪ%d\n",head->elem+1); 
			getchar();getchar();
			break;
        case 11:
            if(!head){
                printf("��������\n");
                getchar();getchar();
                break;
            }
            if(head->elem)
			printf("������Ҫɾ����λ�ã������뷶ΧΪ1~%d��\n",head->elem);
			else {
				printf("��Ϊ�գ��޷�ɾ��\n");
				getchar();getchar();
				break;
			}
			scanf("%d",&i);
			flag=ListDelete(head,i,e);
			if(flag==OK) printf("�ɹ�ɾ����%dλԪ�أ���ֵΪ%d\n",i,e);
			else if(flag==FALSE) printf("λ��ֵ����Ŷ,�������λ��ֵΪ%d\n",head->elem);   
			getchar();getchar();
			break;
        case 12:
            flag=ListTrabverse(head);  
			if(flag==FALSE) printf("�����ǿձ�\n");
			else if(flag!=ERROR) printf("һ����%d��Ԫ��\n",flag);
			getchar();getchar();
			break;
        case 13:
			if(j) L[j-1]=head;
			printf("ѡ��Ҫ�л��ı�\n");
			for(k=0;k<30;k++) 
			if(L[k]!=NULL)
			printf("%d ",k+1);
			printf("\n");
			scanf("%d",&k);
			if(k<=0 || k>30) printf("��������ȷ��ֵ\n");
			else if(L[k-1]!=NULL){
				head=L[k-1];
				printf("�л��ɹ�\n");
				j=k;
			}
			else printf("�л��ı�����\n");
			getchar();getchar();
			break;
		case 0:
			break;
		case 101:
            if(!head){
                printf("��������\n");
                getchar();getchar();
                break;
            }
			printf("������Ҫ�洢���ļ�\n");
			scanf("%s",string);
			if((fp=fopen(string,"w"))==NULL){
				printf("���ļ�ʧ��\n");
				getchar();getchar();
				break;
			}
            LinkList p;
			for(p=head->next;p;p=p->next) fprintf(fp," %d",p->elem);
			printf("�Ѿ�д���ļ�%s",string);
			fclose(fp);
			getchar();getchar();
			break;
		case 102:
            if(!head){
                printf("��������\n");
                getchar();getchar();
                break;
            }
			printf("������Ҫ��ȡ���ļ���\n");
			scanf("%s",string);
			if((fp=fopen(string,"r"))==NULL){
				printf("��������ȷ���ļ�����ʧ��\n");
				getchar();getchar();
				break;
			}
			while(!feof(fp)){
				fscanf(fp,"%d",&x);
				ListInsert(head,head->elem+1,x);	
			}
			fclose(fp);
			printf("�ļ�Ԫ������ӵ�����ĩβ\n");
			getchar();getchar();
			break;
	}//end of switch
  }//end of while
printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
system("pause");
}//end of main()

status InitList(LinkList& head){
    head=(LinkList)malloc(sizeof(LNode));
    if(head==NULL) return ERROR;
    head->elem=0;
    head->next=NULL;
    return OK;
}  //����һ��˳������޷���������overflow

status DestroyList(LinkList& head){
    LinkList p,q;
    if(ListEmpty(head)==ERROR) return ERROR;  //�����ж��Ƿ񴴽��˱�
    char c;
    getchar();
    printf("�Ƿ�ݻٱ���y/n��\n");
    c=getchar();
    if(c!='y') {  //��ֹͣɾ�����򷵻�stop
		printf("ֹͣ�ݻ�\n");
		return STOP;
	}
    for(p=head;p;){  //��ȷ��ɾ�����������ͷű�����ڴ�
        q=p;
        p=p->next;
        free(q);
    }
    head=NULL;  //ʹָ��ָ��
    printf("�ݻٳɹ�\n");
    return OK;
}  //��ȷɾ�����Ա��򷵻�ok����ֹͣɾ�����򷵻�stop������Ϊ�����ڣ��򷵻�error

status ClearList(LinkList& head){
    int flag=ListEmpty(head);
    if(flag==ERROR) return ERROR;
    if(flag==TRUE) printf("����Ϊ�գ��޷����\n");
    else{
        char c;int i;LinkList p,q;
        getchar();
        printf("�Ƿ���ձ���y/n��\n"); //����ȷ���Ƿ�ɾ�������������
        c=getchar();
        if(c!='y'){
            printf("ֹͣ�������\n");
            return STOP;
        }
        for(p=head->next;p;){  //�����ͷű��㣬�������ͷ��㣬��Ȼ����ͷ������
            q=p;
            p=q->next;
            free(q);
        }
        head->next=NULL;
        head->elem=0;
        printf("�ɹ��������\n");
        return OK;
    }
}  //����ȷ��գ��򷵻�ok����ֹͣ���򷵻�stop������Ϊ�գ��򷵻�error

status ListEmpty(LinkList head){
    if(head==NULL){
        printf("��������\n");   //����������һ����ϣ����Լ��ж������������Ż�
        return ERROR;             //���������������н���ʡ����仰
    }
    else if(!head->elem) return TRUE;
    else return FALSE;
}

status ListLength(LinkList head){
    int flag=ListEmpty(head);  //���ú��������жϣ������淵��ֵ��flag����
    if(flag==ERROR) return ERROR;
    if(flag==TRUE) return FALSE;
    else return head->elem;
}

status GetElem(LinkList head,int i,ElemType& e){
    int flag=ListEmpty(head);
    if(flag==ERROR) return ERROR;
    if(flag==TRUE) return FALSE;  //����Ϊ�գ�����false
    else{
        if(i<=0||i>head->elem) return OVERFLOW; //������ֵ�������ƣ��򷵻�overflow
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
		printf("�޷��ҵ�\n");
		if(flag==TRUE) printf("��Ϊ��Ϊ��\n");
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
        else if(i==1) printf("��Ԫ��Ϊ�׽�㣬û��ǰ�����\n");  //�����������жϺ���ʾ
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
        else if(i==head->elem) printf("��Ԫ��Ϊβ��㣬û�к�̽��\n");    //�����������ж�����ʾ
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
    if(!q) return OVERFLOW;   //�����ݲ��ɹ����㷵��overflow
    q->next->elem=e;
    q->next->next=p;
    head->elem++;
    return OK;  //���ɹ����򷵻�OK
}

status ListDelete(LinkList& head,int i,ElemType& e){
    if(ListEmpty(head)!=ERROR){
		if (i<1||i>ListLength(head)) return FALSE; 
		LinkList p,q;
        for(p=head;i-1;i--) p=p->next; //����λ�õĽ��ɾ��������ָ�����¹滮
        e=p->next->elem;
        q=p;
        p=p->next;
        q->next=p->next;
        free(p);
        head->elem--;
		return OK;  //�ɹ�ɾ������OK�����󷵻�error
	}
	else return ERROR;  //������������ֵ������򷵻�error
}

status ListTrabverse(LinkList head){
    int flag;
	flag=ListEmpty(head);
	if(flag==TRUE) return FALSE;
	else if(flag==ERROR) return ERROR;
    int i;
    LinkList p=head->next;
	printf("\n-----------all elements -----------------------\n");
	for(i=0;i<head->elem;i++,p=p->next) printf("%d ",p->elem);   //ʹ�ü���ָ������Ԫ��
	printf("\n------------------ end ------------------------\n");
	return head->elem;
}  //�����������ÿһ�����洢��Ԫ��