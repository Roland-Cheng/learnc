typedef int ElemType;
typedef  struct  Dnode
{
    ElemType     data;
    struct  Dnode *prior,*next;
}  *DuLinkList;

void  adjust(DuLinkList  L);

void  adjust(DuLinkList  L){
    DuLinkList p;
    p=L->next;
    while (p->next!=L&&p->next->next!=L)
    {
        p->next=p->next->next;
        p=p->next;
    }
    if (p->next==L) p->next=L->prior->prior;
    else p->next=p->prior;
    p=p->next;
    while (p->prior->prior!=L)
    {
        p->next=p->prior->prior;
        p=p->next;
    }
    if(p!=L)
    p->next=L;
    for(p=L;p->next!=L;p=p->next) p->next->prior=p; 
    L->prior=p;
}

#include<stdlib.h>
#include<stdio.h>

int main(){
    int n;
    scanf("%d",&n);
    int i;
    DuLinkList l,p;
    l=(DuLinkList)malloc(sizeof(struct  Dnode));
    l->data=n;
    p=l;
    for(i=0;i<n;i++){
        p->next=(DuLinkList)malloc(sizeof(struct Dnode));
        p->next->prior=p;
        p=p->next;
        p->data=i+1;        
    }
    p->next=l;
    l->prior=p;
    for(p=l->next;p!=l;p=p->next)
        printf("%d\n",p->data);
    adjust(l);
    for(p=l->next;p!=l;p=p->next)
        printf("%d\n",p->data);
    for(p=l->prior;p!=l;p=p->prior)
        printf("%d\n",p->data);
}