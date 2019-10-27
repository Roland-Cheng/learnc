/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define OVERFLOW -2
#define STOP -3
#define INFEASTABLE -4

typedef int status; 
typedef int ElemType; //����Ԫ�����Ͷ���

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //˳���˳��ṹ���Ķ���
	ElemType * elem=NULL;
	int length=0;
	int listsize=0;
}SqList;
/*-----page 19 on textbook ---------*/
status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList&L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L,int i,ElemType& e);
status LocateElem(SqList L,ElemType e); //�򻯹�
status PriorElem(SqList L,ElemType cur,ElemType& pre_e);
status NextElem(SqList L,ElemType cur,ElemType& next_e);
status ListInsert(SqList& L,int i,ElemType e);
status ListDelete(SqList& L,int i,ElemType& e);
status ListTrabverse(SqList L);  //�򻯹�
/*--------------------------------------------*/
int main(void){
SqList L;  int op=1; ElemType e,x; int i;
FILE *fp; char string[100]; int flag;
while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. InitList       7. LocateElem\n");
	printf("    	  2. DestroyList    8. PriorElem\n");
	printf("    	  3. ClearList      9. NextElem \n");
	printf("    	  4. ListEmpty      10. ListInsert\n");
	printf("    	  5. ListLength     11. ListDelete\n");
	printf("    	  6. GetElem        12. ListTrabverse\n");
	printf("    	  0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("          101.�洢���Ա�    102.��ȡ���Ա�\n");
	printf("��ѡ����Ĳ���[0~12]:");
	scanf("%d",&op);
    switch(op){
		case 1:
			if(InitList(L)==OK) printf("���Ա����ɹ���\n");
				else printf("���Ա���ʧ�ܣ�\n");
			getchar();getchar();
			break;
		case 2:
			DestroyList(L);
			getchar();getchar();
			break;
		case 3: 
			ClearList(L);
			getchar();getchar();
			break;
		case 4:
			flag=ListEmpty(L);
			if(flag!=ERROR){
				if(flag==false) printf("��Ϊ��\n");  //ʹ�ú����ķ���ֵ�����жϲ����
				else printf("��Ϊ��\n");
			}     
			getchar();getchar();
			break;
		case 5:
			flag=ListLength(L);
			if(flag>0)
			printf("���Ա�ĳ���Ϊ%d\n",flag);   
			else if(flag==FALSE) printf("��Ϊ��\n");    //�����������Ϊerror����listlength�ķ���ֵ֪��Ϊ��
			getchar();getchar();
			break;
		case 6:
		    if(L.length)
			printf("������λ��ֵ�������뷶ΧΪ1~%d��\n",L.length);
			else printf("������λ��ֵ��\n");
			scanf("%d",&i);
			flag=GetElem(L,i,e);
			if(flag==FALSE)
			printf("���Ա�Ϊ��\n");
			if(flag==OVERFLOW)
			printf("λ��ֵ����Ŷ,�������λ��ֵΪ%d\n",L.length); 
			if(flag==OK)
			printf("��λ�õ�Ԫ��Ϊ��%d\n",e);   
			getchar();getchar();
			break;
		case 7:
			printf("������Ҫ���ҵ�Ԫ�أ�\n");
			scanf("%d",&e);
			i=LocateElem(L,e);
			if(i!=ERROR) printf("��Ԫ���ڵ�%dλ\n",i);   
			getchar();getchar();
			break;
		case 8:
			printf("������Ҫ���ҵ�Ԫ�أ�\n");
			scanf("%d",&e); 
			flag=PriorElem(L,e,x);
			if(flag!=ERROR) printf("��Ԫ��ǰһ��Ԫ��Ϊ��%d\n",x);  
			getchar();getchar();
			break;
		case 9:
			printf("������Ҫ���ҵ�Ԫ�أ�\n");
			scanf("%d",&e); 
			flag=NextElem(L,e,x);
			if(flag!=ERROR) printf("��Ԫ�غ�һ��Ԫ��Ϊ��%d\n",x); 
			getchar();getchar();
			break;
		case 10:
			printf("������Ҫ�����Ԫ�أ�\n");
			scanf("%d",&e);
			if(L.elem)
			printf("������Ҫ�����λ�ã������뷶ΧΪ1~%d��\n",L.length+1);
			else printf("������Ҫ�����λ�ã�\n");
			scanf("%d",&i);
			flag=ListInsert(L,i,e);
			if (flag==OVERFLOW) printf("�洢�ռ䲻��\n");
			else if(flag==OK) printf("����ɹ�\n"); 
			else if(flag==FALSE) printf("λ��ֵ����Ŷ,�������λ��ֵΪ%d\n",L.length+1); 
			getchar();getchar();
			break;
		case 11:
			printf("������Ҫɾ����λ�ã�\n");
			scanf("%d",&i);
			flag=ListDelete(L,i,e);
			if(flag==OK) printf("�ɹ�ɾ����%dλԪ�أ���ֵΪ%d\n",i,e);
			else if(flag==FALSE) printf("ɾ��ʧ��\n");   
			getchar();getchar();
			break;
		case 12:
			flag=ListTrabverse(L);  
			if(flag==FALSE) printf("���Ա��ǿձ�\n");
			else if(flag!=ERROR) printf("һ����%d��Ԫ��\n",flag);
			getchar();getchar();
			break;
		case 0:
			break;
		case 101:
			printf("������Ҫ�洢���ļ�\n");
			scanf("%s",string);
			if((fp=fopen(string,"w"))==NULL){
				printf("���ļ�ʧ��\n");
				getchar();getchar();
				break;
			}
			for(i=0;i<L.length;i++) fprintf(fp," %d",L.elem[i]);
			printf("�Ѿ�д���ļ�%s",string);
			fclose(fp);
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
			while(!feof(fp)){
				fscanf(fp,"%d",&x);
				ListInsert(L,L.length+1,x);	
			}
			fclose(fp);
			printf("�ļ�Ԫ������ӵ����Ա�ĩβ");
			getchar();getchar();
			break;
	}//end of switch
  }//end of while
printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
system("pause");
}//end of main()
/*--------page 23 on textbook --------------------*/
status InitList(SqList &L){
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L.elem) exit(OVERFLOW);
	L.length=0;
    L.listsize=LIST_INIT_SIZE;
	return OK;
}  //����һ��˳������޷���������overflow

status DestroyList(SqList& L){
	int flag=ListEmpty(L);
	if (flag!=ERROR){  //�����ж��Ƿ񴴽��˱�
		char c;
		getchar();
		printf("ȷ��ɾ������y/n��\n");  //����ȷ���Ƿ�ɾ��
		scanf("%c",&c);
		if(c=='y'){
			free(L.elem);
			L.elem=NULL;
			L.listsize=0;
			L.length=0;
			printf("ɾ���ɹ�\n");
			return OK;
		}
		else {
			printf("ֹͣɾ��\n");
			return STOP;  //��ֹͣɾ�����򷵻�stop
		}
	}
	else return ERROR;
}  //��ȷɾ�����Ա��򷵻�ok����ֹͣɾ�����򷵻�stop������Ϊ�����ڣ��򷵻�error

status ClearList(SqList& L){
	int flag=ListEmpty(L);
	if(flag==FALSE){
		getchar();
		printf("ȷ��������Ա���y/n��\n");
		char c;
		c=getchar();
		if(c=='y'){
			free(L.elem);
			L.listsize=LIST_INIT_SIZE;
			L.elem=(ElemType*)malloc(L.listsize*sizeof(ElemType));
			L.length=0;
			printf("�������\n");
			return OK;
		}
		else{
			printf("ֹͣ������Ա�\n");
			return STOP;
		}
	}
	else{
		if(flag==TRUE) printf("��Ϊ��,�������\n");
		return ERROR;
	}
}  //����ȷ��գ��򷵻�ok����ֹͣ���򷵻�stop������Ϊ�գ��򷵻�error

status ListEmpty(SqList L){
	if(L.elem){
		if(!L.length) return TRUE;
		else return FALSE;
	}
	else{
		printf("���Ա����ڣ����ȴ������Ա�\n");  //����������һ����ϣ����Լ��ж������������Ż�
		return ERROR;                           //���������������н���ʡ����仰
	}
}

status ListLength(SqList L){
	int flag;
	flag=ListEmpty(L);  //���ú��������жϣ������淵��ֵ��flag����
	if(flag==false) return L.length;
	else if (flag==true) return FALSE;
	return ERROR;
}

status GetElem(SqList L,int i,ElemType& e){
	int flag=ListEmpty(L);
	if(flag==FALSE){
		if(1<=i&&i<=L.length){
			e=L.elem[i-1];
			return OK;
		}
		else return OVERFLOW;
	}
	else if(flag==TRUE) return FALSE;
}

status LocateElem(SqList L,ElemType e){
	int flag;
	flag=ListEmpty(L);
	if(flag!=ERROR){
		int i;
		for(i=1;i<=L.length;i++)
			if(L.elem[i-1]==e) return i;	
		printf("�޷��ҵ�\n");
		if(flag==TRUE) printf("��Ϊ��Ϊ��\n");
		return ERROR;
	}
	else return ERROR;
}	


status PriorElem(SqList L,ElemType cur,ElemType& pre_e){
	int i;
	i=LocateElem(L,cur);
	if(i!=ERROR){
		if(i>1){
			pre_e=L.elem[i-2];
			return OK;
		}
		else if(i==1){
			printf("��Ԫ���ڱ��ף���ǰ���\n");  //�����������жϺ���ʾ
			return ERROR;
		}	
	}
	else return ERROR;
}

status NextElem(SqList L,ElemType cur,ElemType& next_e){
	int i;
	i=LocateElem(L,cur);
	if(i!=ERROR){
		if(i!=L.length){
			next_e=L.elem[i];
			return OK;
		}
		else if(i==L.length){
			printf("��Ԫ���ڱ�β���޺�̽��\n");  //�����������ж�����ʾ
			return ERROR;
		}
	}
	else return ERROR;
}

status ListInsert(SqList& L,int i,ElemType e){
	if(ListEmpty(L)==ERROR) return ERROR;
	if(i<1||i>L.length+1) return FALSE;
	if(L.length+1>=L.listsize){
		ElemType *newbase;
		newbase=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase) exit(OVERFLOW);  //�����ݲ��ɹ����㷵��overflow
		L.elem=newbase;
		L.listsize+=LISTINCREMENT;
	}
	int j;
	for(j=L.length;j>=i;j--) L.elem[j]=L.elem[j-1];
	L.elem[i-1]=e;
	L.length++;
	return OK;
}

status ListDelete(SqList& L,int i,ElemType& e){
	if(ListEmpty(L)!=ERROR){
		if (i<1||i>ListLength(L)) return FALSE;
		int j;
		e=L.elem[i-1];
		for(j=i;j<=L.length;j++) L.elem[j-1]=L.elem[j];
		L.length--;
		return OK;
	}
	else return ERROR;
}

status ListTrabverse(SqList L){
	int flag;
	flag=ListEmpty(L);
	if(flag==TRUE) return FALSE;
	else if(flag==ERROR) return ERROR;
	int i;
	printf("\n-----------all elements -----------------------\n");
	for(i=0;i<L.length;i++) printf("%d ",L.elem[i]);   //ʹ�ü���ָ������Ԫ��
	printf("\n------------------ end ------------------------\n");
	return L.length;
}
