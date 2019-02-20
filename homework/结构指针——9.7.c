#include<stdio.h>

int main()
{
    struct Student{int num;char name[19]; double score;} stu[3],*p=stu;
    int n,i;
    scanf ("%d",&n);
    for(i=0;i<n;i++)
    {
        int j;
        for(j=0;j<3;j++) 
        scanf("%d%s%lf",&stu[j].num,stu[j].name,&stu[j].score);
        for(j=0;j<3;j++) 
        printf("%d\t%-20s%f\n",stu[j].num,stu[j].name,stu[j].score);
        for(j=0,p=stu;j<3;j++,p++) 
        printf("%d\t%-20s%f\n",p->num,p->name,p->score);
    }
}