#include<stdio.h>
#define queennum 8

void queen(int i, int j);
int lay(int i, int j);
void print(int s[queennum][queennum]);

int chess[queennum][queennum];
const int line = queennum;
int times;

int main()
{
    queen(0,0);
    printf("\n");
}

void queen(int i, int j)
{
    if (j >= line) return;
    if(lay(i,j)) 
    {
        chess[i][j] = 1;
        if (i==line-1) print(chess);
        else queen(i+1,0);
    }
    chess[i][j] = 0;
    queen(i,j+1);
}

int lay(int i,int j)
{
    int k;
    for (k=0;k<line;k++)
    if (chess[k][j]) return 0;
    for (k=0;k<line;k++)
    if (chess[i][k]) return 0;
    for (k=(-line);k<=line;k++)
    {
        if (0<=(k+i)&&(k+i)<line&&(k+j)>=0&&(k+j)<line)
        if (chess[k+i][k+j]) return 0;
        if (0<=(i-k)&&(i-k)<line&&(k+j)>=0&&(k+j)<line)
        if (chess[i-k][k+j]) return 0;
    }
    return 1;
}

void print(int s[queennum][queennum])
{
    times++;
    printf("(%d):\n",times);
    int i, j;
    for (i=0;i<line;i++)
    {
        for (j=0;j<line;j++)
        {
            if (s[i][j]) printf("Q ");
            else printf ("+ ");
        }
        printf("\n");
    }
    printf("\n");
}