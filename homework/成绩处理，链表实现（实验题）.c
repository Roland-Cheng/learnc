#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct table{
    char num[15];
    char name[20];
    float eng,math,phy,c,ave;
    struct table *next;
}table;

void print(table *head);
void printave(table *head);
void printorder(table *head,int n);
void exchange(table *p,table *q);

int main()
{
    int n,i,j,m;
    char class[4][15]={"English","Math","Physics","C"};
    scanf("%d",&n);
    table *head=NULL;
    head=(table *)malloc(sizeof(table));
    table *tail=head,*p=head;
    scanf("%s%s",tail->num,tail->name);
    scanf("%f%f%f%f",&tail->eng,&tail->math,&tail->phy,&tail->c);
    for(i=1;i<n;i++)
    {
        tail->next=(table *)malloc(sizeof(table));
        tail=tail->next;
        scanf("%s%s",tail->num,tail->name);
        scanf("%f%f%f%f",&tail->eng,&tail->math,&tail->phy,&tail->c);
    }
    tail->next=NULL;
    print(head);
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
    printorder(head,n);
}

void print(table *head)
{
    table *p=head;
    printf("ID             Name                English   Math      Physics   C         \n");
    for(;p;p=p->next) printf("%-15s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n",p->num,p->name,p->eng,p->math,p->phy,p->c);
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
void printorder(table *head,int n)
{
    int i,j;
    table *p=head;
    printf("Sort:\nID             Name                AVG       \n");
    for(i=0;i<n-1;i++,p=head)
        for(j=0;j<n-1;j++,p=p->next)
            if (p->ave > p->next->ave)
                exchange(p,p->next);
    p=head;
    for(;p;p=p->next) printf("%-15s%-20s%-10.2f\n",p->num,p->name,p->ave);
}
void exchange(table *p,table *q)
{
    char num[15],name[20];
    strcpy(num,p->num);
    strcpy(name,p->name);
    float a=p->eng,s=p->math,d=p->phy,f=p->c,g=p->ave;
    p->eng=q->eng,p->math=q->math,p->phy=q->phy,p->c=q->c,p->ave=q->ave;
    strcpy(p->num,q->num);
    strcpy(p->name,q->name);
    q->eng=a,q->math=s,q->phy=d,q->c=f,q->ave=g;
    strcpy(q->num,num);
    strcpy(q->name,name);
}