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
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //顺序表（顺序结构）的定义
	ElemType * elem;
	int length;
	int listsize;
}SqList;
/*-----page 19 on textbook ---------*/
status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList&L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L,int i,ElemType& e);
status LocateElem(SqList L,ElemType e); //简化过
status PriorElem(SqList L,ElemType cur,ElemType& pre_e);
status NextElem(SqList L,ElemType cur,ElemType& next_e);
status ListInsert(SqList& L,int i,ElemType e);
status ListDelete(SqList& L,int i,ElemType& e);
status ListTrabverse(SqList L);  //简化过
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
	printf("          101.存储线性表    102.读取线性表\n");
	printf("请选择你的操作[0~12]:");
	scanf("%d",&op);
    switch(op){
		case 1:
			if(InitList(L)==OK) printf("线性表创建成功！\n");
				else printf("线性表创建失败！\n");
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
				if(flag==false) printf("表不为空\n");
				else printf("表为空\n");
			}     
			getchar();getchar();
			break;
		case 5:
			flag=ListLength(L);
			if(flag!=ERROR)
			printf("线性表的长度为%d\n",flag); 
			else printf("表为空\n");    
			getchar();getchar();
			break;
		case 6:
			printf("请输入位置值：\n");
			scanf("%d",&i); 
			flag=GetElem(L,i,e);
			if(flag==ERROR)
			printf("线性表为空\n");
			if(flag==OVERFLOW)
			printf("位置值不对哦,最大输入位置值为%d\n",L.length); 
			if(flag==OK)
			printf("该位置的元素为：%d\n",e);   
			getchar();getchar();
			break;
		case 7:
			printf("请输入要查找的元素：\n");
			scanf("%d",&e);
			i=LocateElem(L,e);
			if(i!=ERROR) printf("该元素在第%d位\n",i);   
			getchar();getchar();
			break;
		case 8:
			printf("请输入要查找的元素：\n");
			scanf("%d",&e); 
			flag=PriorElem(L,e,x);
			if(flag!=ERROR) printf("该元素前一个元素为：%d\n",x);  
			getchar();getchar();
			break;
		case 9:
			printf("请输入要查找的元素：\n");
			scanf("%d",&e); 
			flag=NextElem(L,e,x);
			if(flag!=ERROR) printf("该元素后一个元素为：%d\n",x); 
			getchar();getchar();
			break;
		case 10:
			printf("请输入要插入的元素：\n");
			scanf("%d",&e);
			printf("请输入要插入的位置：\n");
			scanf("%d",&i);
			flag=ListInsert(L,i,e);
			if (flag==OVERFLOW) printf("存储空间不够\n");
			else if(flag==OK) printf("插入成功\n"); 
			else if(flag==ERROR) printf("位置值不对哦,最大输入位置值为%d\n",L.length+1); 
			getchar();getchar();
			break;
		case 11:
			printf("请输入要删除的位置：\n");
			scanf("%d",&i);
			flag=ListDelete(L,i,e);
			if(flag==OK) printf("成功删除第%d位元素，其值为%d\n",i,e);
			else printf("删除失败\n");   
			getchar();getchar();
			break;
		case 12:
			flag=ListTrabverse(L);  
			if(flag==ERROR) printf("线性表是空表！\n");
			else printf("一共是%d个元素\n",flag);
			getchar();getchar();
			break;
		case 0:
			break;
		case 101:
			printf("请输入要存储的文件\n");
			scanf("%s",string);
			if((fp=fopen(string,"w"))==NULL){
				printf("打开文件失败\n");
				getchar();getchar();
				break;
			}
			for(i=0;i<L.length;i++) fprintf(fp," %d",L.elem[i]);
			printf("已经写入文件%s",string);
			fclose(fp);
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
			while(!feof(fp)){
				fscanf(fp,"%d",&x);
				ListInsert(L,L.length+1,x);	
			}
			fclose(fp);
			printf("文件元素已添加到线性表末尾");
			getchar();getchar();
			break;
	}//end of switch
  }//end of while
printf("欢迎下次再使用本系统！\n");
}//end of main()
/*--------page 23 on textbook --------------------*/
status InitList(SqList &L){
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L.elem) exit(OVERFLOW);
	L.length=0;
    L.listsize=LIST_INIT_SIZE;
	return OK;
}

status DestroyList(SqList& L){
	if (L.listsize!=0){
		char c;
		getchar();
		printf("确认删除？【y/n】\n");
		scanf("%c",&c);
		if(c=='y'){
			free(L.elem);
			L.listsize=0;
			L.length=0;
			printf("删除成功\n");
			return OK;
		}
		else {
			printf("停止删除\n");
			return STOP;
		}
	}
	else {
		printf("表为空，不用进行删除\n");
		return ERROR;
	}
}

status ClearList(SqList& L){
	if(L.length&&L.listsize){
		getchar();
		printf("确认清空线性表？【y/n】\n");
		char c;
		c=getchar();
		if(c=='y'){
			free(L.elem);
			L.listsize=LIST_INIT_SIZE;
			L.elem=(ElemType*)malloc(L.listsize*sizeof(ElemType));
			L.length=0;
			printf("表已清空\n");
			return OK;
		}
		else{
			printf("停止清空线性表\n");
			return STOP;
		}
	}
	else{
		if(ListEmpty(L)==TRUE) printf("表为空\n");
		return ERROR;
	}
}

status ListEmpty(SqList L){
	if(L.listsize!=0){
		if(!L.length) return TRUE;
		else return FALSE;
	}
	else{
		printf("线性表不存在，请先创建线性表\n");
		return ERROR;
	}
}

status ListLength(SqList L){
	int flag;
	flag=ListEmpty(L);
	if(flag==false) return L.length;
	else if (flag==true) return ERROR;
}

status GetElem(SqList L,int i,ElemType& e){
	if(L.length&&L.listsize){
		if(1<=i&&i<=L.length){
			e=L.elem[i-1];
			return OK;
		}
		else return OVERFLOW;
	}
	else if(ListEmpty(L)==TRUE) return ERROR;
}

status LocateElem(SqList L,ElemType e){
	int flag;
	flag=ListEmpty(L);
	if(flag!=ERROR){
		int i;
		for(i=1;i<=L.length;i++)
			if(L.elem[i-1]==e) return i;	
		printf("无法找到\n");
		if(flag==TRUE) printf("因为表为空\n");
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
			printf("该元素在表首，无前结点\n");
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
			printf("该元素在表尾，无后继结点\n");
			return ERROR;
		}
	}
	else return ERROR;
}

status ListInsert(SqList& L,int i,ElemType e){
	if(i<1||i>L.length+1) return ERROR;
	if(L.length+1>=L.listsize){
		ElemType *newbase;
		newbase=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase) exit(OVERFLOW);
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
		if (i<1||i>ListLength(L)) return ERROR;
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
	if(flag==TRUE||flag==ERROR) return ERROR;
	int i;
	printf("\n-----------all elements -----------------------\n");
	for(i=0;i<L.length;i++) printf("%d ",L.elem[i]);
	printf("\n------------------ end ------------------------\n");
	return L.length;
}
