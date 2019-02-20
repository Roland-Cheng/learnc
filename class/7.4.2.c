#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct table{
    char num[15];
    char name[20];
    float eng,math,phy,c,ave;
    struct table *next, *prior;
}table;

void print(table *head);
void printback(table *tail);
void printave(table *head);
void printorder(table *head,table *tail,int n);

int main()
{
    int n,i,j,m;
    char class[4][15]={"English","Math","Physics","C"};
    scanf("%d",&n);
    table *head=NULL;
    head=(table *)malloc(sizeof(table));
    head->prior=NULL;
    table *tail=head,*p=head;
    scanf("%s%s",tail->num,tail->name);
    scanf("%f%f%f%f",&tail->eng,&tail->math,&tail->phy,&tail->c);
    for(i=1;i<n;i++)
    {
        tail->next=(table *)malloc(sizeof(table));
        tail->next->prior=tail;
        tail=tail->next;
        scanf("%s%s",tail->num,tail->name);
        scanf("%f%f%f%f",&tail->eng,&tail->math,&tail->phy,&tail->c);
    }
    tail->next=NULL;
    print(head);
    printf("Backaway:\n");
    printback(tail);
    scanf("%d",&m);
    for(j=0;j<m;j++)
    {
        char xuehao[15];
        char grade[15];
        float gra;
        scanf ("%s %s %f",xuehao,grade,&gra);
        for(p=head;p;p=p->next)
        {
            int a;
            if(strcmp(xuehao,p->num)==0)
            {
                for(a=0;a<4;a++) if(strcmp(grade,class[a])==0) break;
                switch(a)
                {
                    case 0:p->eng=gra;
                    break;
                    case 1:p->math=gra;
                    break;
                    case 2:p->phy=gra;
                    break;
                    case 3:p->c=gra;
                    break;
                }
            }
        }
    }
    printf("Alter:\n");
    print(head);
    printave(head);
    printorder(head,tail,n);
}

void print(table *head)
{
    table *p=head;
    printf("ID             Name                English   Math      Physics   C         \n");
    for(;p;p=p->next) printf("%-15s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n",p->num,p->name,p->eng,p->math,p->phy,p->c);
    printf("\n");
}
void printback(table *tail)
{
    table *p=tail;
    printf("ID             Name                English   Math      Physics   C         \n");
    for(;p;p=p->prior) printf("%-15s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n",p->num,p->name,p->eng,p->math,p->phy,p->c);
    printf("\n");
}
void printave(table *head)
{
    table *p=head;
    printf("SumAndAvg:\nID             Name                SUM       AVG       \n");
    for(;p;p=p->next) 
    {
        p->ave=(p->eng+p->math+p->phy+p->c)/4.0;
        printf("%-15s%-20s%-10.2f%-10.2f\n",p->num,p->name,(p->eng+p->math+p->phy+p->c),p->ave);
    }
    printf("\n");
}
void printorder(table *head,table *tail,int n)
{
    int i,j;
    table *p=head;
    printf("Sort:\nID             Name                AVG       \n");
    for(i=0;i<n-1;i++,p=head)
        for(j=0;j<n-1;j++,p=p->next)
            if (p->ave > p->next->ave)
            {
                table *q=p->next;
                if(p==head)
                {
                    table *y=q->next;
                    head=q;
                    q->next=p;
                    p->next=y;
                    y->prior=p;
                    p->prior=q;
                    q->prior=NULL;
                    p=q;
                }
                else if(q==tail)
                {
                    table *x=p->prior;
                    x->next=q;
                    q->next=p;
                    p->next=NULL;
                    tail=p;
                    p->prior=q;
                    q->prior=x;
                    p=q;
                }
                else 
                {
                    table *x=p->prior,*y=q->next;
                    x->next=q;
                    q->next=p;
                    p->next=y;
                    y->prior=p;
                    p->prior=q;
                    q->prior=x;
                    p=q;
                }
            }
    p=head;
    for(;p;p=p->next) printf("%-15s%-20s%-10.2f\n",p->num,p->name,p->ave);
}
void exchange(table *p,table *q)
{
    table *x;
    x=p->next;
    p->next=q->next;
    q->next=x;
    x=p->prior;
    p->prior=q->prior;
    q->prior=x;
}

/*5
U20140101 ZhangChuanChao 85 86 87 88
U20140126 MaiDouDou 99 99 99 99
U20140158 XiaoDouDou 56 85 89 59
U20140312 DaoDaoDog 84 89 65 100
U20140359 XiDaDa 88.8 88.8 88.8 88.8
3
U20140101 Math 95.6
U20140359 C 100
U20140359 English 100
*/