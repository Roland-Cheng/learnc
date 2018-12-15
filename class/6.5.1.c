#include<stdio.h>
int main()
{
    int a[30],b[30],c[31]={0},i;
    for(i=0;i<20;i++) scanf("%1d",&a[i]);
    getchar();
    for(;i<30;i++)scanf("%1d",&a[i]);
    for(i=0;i<20;i++) scanf("%1d",&b[i]);
    getchar();
    for(;i<30;i++)scanf("%1d",&b[i]);
    for(i = 0;i<30;i++) c[i]=a[29-i]+b[29-i];
    for(i=0;i<30;i++) if(c[i]>=10) c[i]-=10,c[i+1]+=1;
    if (c[30]) printf("%d",c[30]);
    for(i = 29;i>=10;i--) printf("%d",c[i]);
    putchar('.');
    for(i=9;i>=0;i--) printf("%d",c[i]);
    printf("\n");
}