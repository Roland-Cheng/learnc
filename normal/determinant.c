#include<stdio.h>
#include<stdlib.h>
#define order 1              //0为不输入阶数，1为需要输入
typedef struct stack{        //规定一个结构体，便于输入，用于方法2建立栈
    double x;
    struct stack *next;
} stack;

double calculate(int n,double a[n][n]);  //定义了一个函数体
       
int main()
{
#if order               //使用#if判断
    int n,i,j;
    scanf("%d",&n);     //将阶数赋值
    double a[n][n];     //定义double类型数组，将读入数据储存
    for (i=0;i<n;i++)
    for (j=0;j<n;j++)
    scanf("%lf",&a[i][j]);
#else
    stack *head=(stack *)malloc(sizeof(stack)); //建立动态分配存储，并建成链表
    stack *tail=head;
    tail->next=NULL;
    int n=0,i,j;
    for(;;)     //将第一行的数据读入链表并统计数目
    {
        
        char c;
        scanf("%lf",&tail->x);
        tail->next=(stack *)malloc(sizeof(stack));
        tail = tail->next;
        tail->next=NULL;
        c=getchar();
        n++;
        if (c=='\n') break;
    }
    tail=head;
    double a[n][n];  //建立数组储存链表中的数字并将余下的数读入
    for(i=0;i<n;i++)
    {
        a[0][i]=tail->x;
        head=tail;
        tail=tail->next;
        free(head);    
    }
    for(i=1;i<n;i++)
    for(j=0;j<n;j++)
    scanf("%lf",&a[i][j]);
#endif

    printf("The result of this determinant is %.2f\n",calculate(n,a)); //输出保留两位小数
}

double calculate(int n,double a[n][n])  //函数本体
{
    if (n==1) return a[0][0];  //判断递归结束条件
    int k,i,j;
    double sum=0;
    for (k=0;k<n;k++)
    {
        double num[n-1][n-1];  //建立去掉一纵列一横行后将要储存数据的数组
        int I,J,x,y;
        for (i=0,I=0;i<n;i++)  //将a数组中的数据去掉部分后储存在num中
        {
            if (i==k) continue;
            for (j=1,J=0;j<n;j++)
            {
                num[I][J] = a[i][j];
                J++;
            }
            I++;
        }
        //可以将以下部分打开观看num数组的变化
        /*
        printf("\n");
        for(i=0;i<n-1;i++,printf("\n"))
        for(j=0;j<n-1;j++)
        printf("%6.2lf ",num[i][j]);
        */
        if (k%2) sum=sum-a[k][0]*calculate(n-1,num); //开始递归，并且使用公式
        else sum=sum+a[k][0]*calculate(n-1,num);
    }
    return sum; //返回值
}