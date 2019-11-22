#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
/*定义各类常量*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define OVERFLOW -2
#define STOP -3
#define INFEASTABLE -4

typedef int status; 
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //顺序表（顺序结构）的定义
	ElemType * elem=NULL; //存储空间基地址
	int length=0;  //定义表长，并初始定义为0
	int listsize=0;  //定义表的最大长度，若表不存在，则定义为0
}SqList;

/*进行函数的声明，之后在主函数之后会进行构造的*/
status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList&L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L,int i,ElemType& e);
status LocateElem(SqList L,ElemType e); 
status PriorElem(SqList L,ElemType cur,ElemType& pre_e);
status NextElem(SqList L,ElemType cur,ElemType& next_e);
status ListInsert(SqList& L,int i,ElemType e);
status ListDelete(SqList& L,int i,ElemType& e);
status ListTrabverse(SqList L);  

int main(void){
SqList L,Q[30];  //定义主表L和用于存储表的线性表数组Q
SqList *p=NULL;  //定义结构指针，并将其悬挂
int op=1;  //输入操作数
ElemType e,x;  //定义元素类型，用来进行之后部分的数据元素输出
int i,j=0,k;  //定义i用于基本的循环，定义j用于指示当前的表为第几号，定义k用来保护j
FILE *fp;  //定义文件指针，之后进行文件操作
char string[100];  //用于存储之后会使用的文件名称
int flag;  //用于存储各类函数的返回值，用于判断
while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");  //系统的主要功能展示界面
	printf("-------------------------------------------------\n");
	printf("    	  1. InitList       7. LocateElem\n");
	printf("    	  2. DestroyList    8. PriorElem\n");
	printf("    	  3. ClearList      9. NextElem \n");
	printf("    	  4. ListEmpty      10. ListInsert\n");
	printf("    	  5. ListLength     11. ListDelete\n");
	printf("    	  6. GetElem        12. ListTrabverse\n");
	printf("    	  13.switch         0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("          101.存储线性表    102.读取线性表\n");
	printf("请选择你的操作[0~13]:");
	scanf("%d",&op);
    switch(op){
		case 1:
			if(j) Q[j-1]=L;  //先将当前使用的主表进行储存
			printf("请输入要创建的表（1~30）:\n");
			for(k=0;k<30;k++)
			if(Q[k].elem==NULL)
			printf("%d ",k+1);  //使用for循环，输出当前尚可建立的线性表，也就是当前尚未存在的表
			printf("\n");
			scanf("%d",&k);
			if(0<k&&k<=30){
				if(Q[k-1].elem==NULL){
					if(InitList(L)==OK) {
						printf("线性表创建成功！\n");
						j=k;
					}
					else printf("线性表创建失败！\n");
				}
				else printf("线性表已经创建，请重试\n");
			}
			else printf("请输入正确的值\n");
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
				if(flag==false) printf("表不为空\n");  //使用函数的返回值进行判断并输出
				else printf("表为空\n");
			}     
			getchar();getchar();
			break;
		case 5:
			flag=ListLength(L);
			if(flag>0)
			printf("线性表的长度为%d\n",flag);   
			else if(flag==FALSE) printf("表为空\n");    //若函数的输出为error，由listlength的返回值知表为空
			getchar();getchar();
			break;
		case 6:
		    if(L.length)
			printf("请输入位置值：（输入范围为1~%d）\n",L.length);
			else printf("请输入位置值：\n");
			scanf("%d",&i);
			flag=GetElem(L,i,e);
			if(flag==FALSE)
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
			if(L.elem)
			printf("请输入要插入的位置：（输入范围为1~%d）\n",L.length+1);
			else printf("请输入要插入的位置：\n");
			scanf("%d",&i);
			flag=ListInsert(L,i,e);
			if (flag==OVERFLOW) printf("存储空间不够\n");
			else if(flag==OK) printf("插入成功\n"); 
			else if(flag==FALSE) printf("位置值不对哦,最大输入位置值为%d\n",L.length+1); 
			getchar();getchar();
			break;
		case 11:
			if(L.length)
			printf("请输入要删除的位置：（输入范围为1~%d）\n",L.length);
			else {
				printf("表为空，无法删除\n");
				getchar();getchar();
				break;
			}
			scanf("%d",&i);
			flag=ListDelete(L,i,e);
			if(flag==OK) printf("成功删除第%d位元素，其值为%d\n",i,e);
			else if(flag==FALSE) printf("位置值不对哦,最大输入位置值为%d\n",L.length);   
			getchar();getchar();
			break;
		case 12:
			flag=ListTrabverse(L);  
			if(flag==FALSE) printf("线性表是空表！\n");
			else if(flag!=ERROR) printf("一共是%d个元素\n",flag);
			getchar();getchar();
			break;
		case 13:
			if(j) Q[j-1]=L;
			printf("选择要切换的表：\n");
			for(k=0;k<30;k++) 
			if(Q[k].elem!=NULL)
			printf("%d ",k+1);
			printf("\n");
			scanf("%d",&k);
			if(k<=0 || k>30) printf("请输入正确的值\n");
			else if(Q[k-1].elem!=NULL){
				L=Q[k-1];
				printf("切换成功\n");
				j=k;
			}
			else printf("切换的表不存在\n");
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
system("pause");
}//end of main()
/*--------page 23 on textbook --------------------*/
status InitList(SqList &L){
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L.elem) exit(OVERFLOW);
	L.length=0;
    L.listsize=LIST_INIT_SIZE;
	return OK;
}  //创立一个顺序表，若无法创立返回overflow

status DestroyList(SqList& L){
	int flag=ListEmpty(L);
	if (flag!=ERROR){  //首先判断是否创建了表
		char c;
		getchar();
		printf("确认删除？【y/n】\n");  //进行确认是否删除
		scanf("%c",&c);
		if(c=='y'){
			free(L.elem);  //若确认删除，就清空数组
			L.elem=NULL;  //将数组中的元素归零
			L.listsize=0;
			L.length=0;
			printf("删除成功\n");
			return OK;
		}
		else {
			printf("停止删除\n");
			return STOP;  //若停止删除，则返回stop
		}
	}
	else return ERROR;
}  //正确删除线性表，则返回ok；若停止删除，则返回stop；若表为不存在，则返回error

status ClearList(SqList& L){
	int flag=ListEmpty(L);
	if(flag==FALSE){
		getchar();
		printf("确认清空线性表？【y/n】\n"); //进行确认是否删除，避免误操作
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
		if(flag==TRUE) printf("表为空,不用清空\n");
		return ERROR;
	}
}  //若正确清空，则返回ok；若停止，则返回stop；若表为空，则返回error

status ListEmpty(SqList L){
	if(L.elem){
		if(!L.length) return TRUE;
		else return FALSE;
	}
	else{
		printf("线性表不存在，请先创建线性表\n");  //与其他函数一起配合，可以简化判断条件，便于优化
		return ERROR;                           //可以在其他函数中进行省略这句话
	}
}

status ListLength(SqList L){
	int flag;
	flag=ListEmpty(L);  //调用函数进行判断，并储存返回值在flag里面
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
		else return OVERFLOW; //若输入值超过限制，则返回overflow
	}
	else if(flag==TRUE) return FALSE; //若表为空，返回false
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
			printf("该元素在表首，无前结点\n");  //超限条件的判断和提示
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
			printf("该元素在表尾，无后继结点\n");  //超限条件的判断与提示
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
		if(!newbase) exit(OVERFLOW);  //若扩容不成功，便返回overflow
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
}  //成功删除返回OK，错误返回error

status ListTrabverse(SqList L){
	int flag;
	flag=ListEmpty(L);
	if(flag==TRUE) return FALSE;
	else if(flag==ERROR) return ERROR;
	int i;
	printf("\n-----------all elements -----------------------\n");
	for(i=0;i<L.length;i++) printf("%d ",L.elem[i]);   //使用间隔分割输出的元素
	printf("\n------------------ end ------------------------\n");
	return L.length;
}
