#define LIST_INIT_SIZE 20
#define LISTINCREMENT 10
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct
   { ElemType *elem;
     int length;
     int listsize;
} SqList;

int insert(SqList &L,ElemType x);

int insert(SqList &L,ElemType x){
    int i=0,j=0;
    while (L.elem[i]<x&&i<L.length) i++;
    L.length++;
    if(L.length>=L.listsize)
    L.elem=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
    for (j=L.length-1;j>i;j--)
        L.elem[j]=L.elem[j-1];
    L.elem[i]=x;
}

int main(){
    SqList l;
    int i=0,n,x;
    scanf("%d%d",&n,&x);
    l.length=n;
    l.listsize=LIST_INIT_SIZE*sizeof(ElemType);
    l.elem=(ElemType *)malloc(l.listsize);
    for(i=0;i<l.length;i++) l.elem[i]=i*10+10;
    insert(l,x);
    for(i=0;i<l.length;i++) printf("%d\n",l.elem[i]);
    return 0;
}