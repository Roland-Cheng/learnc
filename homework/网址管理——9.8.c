#include<stdio.h>
#include<string.h>
typedef struct Web{
    char mini[20],full[40],url[60];
} web;

int main()
{
    int n,i;
    scanf("%d",&n);
    getchar();
    web ysy[n];
    for(i=0;i<n;i++) scanf("%s%s%s",ysy[i].mini,ysy[i].full,ysy[i].url);
    for(i=0;i<n;i++) printf("%-20s%-40s%s\n",ysy[i].mini,ysy[i].full,ysy[i].url);
    printf("\n");
    for(i=0;i<n-1;i++)
    {
        int j;
        web x;
        for (j=0;j<n-i-1;j++) 
        if(strcmp(ysy[j].mini,ysy[j+1].mini)>0) 
        x=ysy[j],ysy[j]=ysy[j+1],ysy[j+1]=x;
    }
    for(i=0;i<n;i++) printf("%-20s%-40s%s\n",ysy[i].mini,ysy[i].full,ysy[i].url);
}
