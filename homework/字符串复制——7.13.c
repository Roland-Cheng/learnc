#include<stdio.h>
void mycpy (char *s,int k);
int main()
{
    int i, n, k, w;
    scanf("%d",&n);
    getchar();
    for (i = 0;i < n;i++)
    {
        char s[1000]={0};
        for(w=0;;w++)
        {
            s[w] = getchar();
            if (s[w] == '\n') 
            {
                s[w] = '\0';
                scanf("%d",&k);
                getchar();
                break;
            } 
        }
        mycpy(s,k);
    }
}

void mycpy (char *s,int k)
{
    int i=0;
    for (i;i<k;i++) putchar(s[i]);
    printf ("\n");
}