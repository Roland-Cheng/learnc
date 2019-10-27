#include <stdio.h>  
#include <string.h>  
#include <math.h>  
#define size 4

int move[4][2]={{-1,0},{0,-1},{0,1},{1,0}};//�� �� �� ��  �û�˳��
char op[4]={'U','L','R','D'};  
int open[size][size],close[size*size],limit,path[100];  
int flag,length;   
int goal[16][2]= {{3,3},{0,0},{0,1}, {0,2},{0,3}, {1,0},   
            {1,1}, {1,2}, {1,3},{2,0}, {2,1}, {2,2},{2,3},{3,0},{3,1},{3,2}};//��������Ӧ��λ�ö��ձ�
int nixu(int a[size*size])  
{  
    int i,j,ni,w,x,y;  //w����0��λ�� �±꣬x y ����0����������
    ni=0;  
    for(i=0;i<size*size;i++)  //size*size=16
    {  
        if(a[i]==0)  //�ҵ�0��λ��
            w=i;  
        for(j=i+1;j<size*size;j++)  //ע�⣡��ÿһ������������еı�һȦ ����С��i�ĸ������
        {  
            if(a[i]>a[j])  
                ni++;  
        }  
    }  
    x=w/size;  
    y=w%size;  
    ni+=fabs(x-3)+fabs(y-3);  //������0��ƫ���� 
    if(ni%2==1)  
        return 1;  
    else  
        return 0;  
}  

int hv(int a[][size])//���ۺ����������پ��룬С����ʵ���ܲ���  
{  
    int i,j,cost=0;  
    for(i=0;i<size;i++)  
    {  
        for(j=0;j<size;j++)  
        {  
            int w=open[i][j];  
            cost+=fabs(i-goal[w][0])+fabs(j-goal[w][1]);  
        }  
    }  
    return cost;  
}  

void swap(int*a,int*b)  
{  
    int tmp;  
    tmp=*a;  
    *a=*b;  
    *b=tmp;  
}  
void dfs(int sx,int sy,int len,int pre_move)//sx,sy�ǿո��λ��  
{  
    int i,nx,ny;  
        if(flag)  
            return;  
    int dv=hv(open);  
        if(len==limit)  
        {  
            if(dv==0)  //�ɹ��� �˳� 
            {  
                flag=1;  
                length=len;  
                return;  
            }  
            else  
                return;  //����Ԥ�賤�� ����
        }  
        else if(len<limit)  
        {  
            if(dv==0)  //����Ԥ�賤�� �ɹ����˳�
            {  
                flag=1;  
                length=len;  
                return;  
            }  
        }  
    for(i=0;i<4;i++)  
    {  
            if(i+pre_move==3&&len>0)//������һ���ƶ������෴���Եڶ����Ժ����  
                continue;      
        nx=sx+move[i][0];  //�ƶ����Ĳ� ��������
        ny=sy+move[i][1];  
        if(0<=nx&&nx<size && 0<=ny&&ny<size)  //�ж��ƶ�����
        {  
            swap(&open[sx][sy],&open[nx][ny]);  
            int p=hv(open);   //�ƶ���� �����پ���p=16
            if(p+len<=limit&&!flag)  //p+len<=limit&&!flag��֦�ж����
            {  
                path[len]=i;  
                dfs(nx,ny,len+1,i);  //�統ǰ���ɹ��� �ݹ����dfs
                if(flag)  
                    return;  
            }  
            swap(&open[sx][sy],&open[nx][ny]);  //�����������һ��
        }  
    }  
}  
int main()  
{  
    int i,j,k,l,m,n,sx,sy;  
    char c,g;  
    i=0;       
    printf("������ʮ�����룺\n");
    flag=0,length=0;
    memset(path,-1,sizeof(path));  //�Ѷ���path[100]���飬��path����-1   void* memset(void*s,int ch,size_t n):��S��ǰn���ֽ���ch�滻������S��
    for(i=0;i<16;i++)  //��open ��close��ֵopen�Ƕ�ά���飬close��һά����
    {  
        scanf("%d",&close[i]);  
        if(close[i]==0)  
        {   
            open[i/size][i%size]=0;  
            sx=i/size;sy=i%size;  
        }  
        else  
        {  
            open[i/size][i%size]=close[i];  
        }  
    }                                      
    if(nixu(close)==1)                     //��״̬�ɴ�  
    {  
        limit=hv(open);  //ȫ���������پ���֮��
        while(!flag&&length<=50)//Ҫ��50��֮�ڵ���  
        {  
            dfs(sx,sy,0,0);  
            if(!flag)  
            limit++; //�õ�������С����  
        }  
        if(flag)  
        {  
            for(i=0;i<length;i++)  
            printf("%c",op[path[i]]);  //����path���URLD·��
            printf("\n");  
        }  
    }  
    else if(!nixu(close)||!flag)  
        printf("�����ⲻ�ɽ⡣\n");    
    return 0;  
}  