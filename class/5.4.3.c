#include<stdio.h>
typedef struct data{
    char name[20];
    int x;
} date;

int main()
{
    int n, i;
    scanf("%d",&n);
    date table[n];
    for (i = 0;i<n;i++)
    {
        date *p = &table[i];
        scanf("%s%d",p->name,&p->x);
    }
    int j;
    for(i=0;i<n;i++)
    {
    for (j = 0;j<n-1;j++)
    {
        date y;
        if (table[j].x <= table[j+1].x) 
        {
            y = table[j];
            table[j] = table[j+1];
            table[j+1] = y;
        }
    }
    }
    for (i = 0;i<n;i++)
    printf("%-20s %d\n",table[i].name,table[i].x);
    printf("\n");
    int e;
    scanf("%d",&e);
    getchar();
    int num[e];
    for (i= 0;i<e;i++) scanf(" %d",&num[i]);
    for (i= 0;i<e;i++)
    {
        int front = 0,back = n-1,middle;
        while(front<=back){
            middle = (front+back)/2;
            if(num[i]>table[middle].x) back = middle-1;
            else if (num[i]<table[middle].x) front = middle+1;
            else 
            {
                printf("%-20s %d",table[middle].name,table[middle].x);
                goto inx;
            }   
        }
        printf ("Not found!");
        inx:    printf("\n");
    } printf("\n");

}