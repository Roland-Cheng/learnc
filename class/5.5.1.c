#include<stdio.h>
void strnins(char s[],char t[],int n);

int main()
{
    char s[100],t[100];
    int n;
    printf("Please input two string:\n");
    scanf("%[^\n]",s);
    getchar();
    scanf("%[^\n]",t);
    getchar();
    printf("Please input a number:\n");
    scanf("%d",&n);
    strnins(s,t,n);
}
void strnins(char s[],char t[],int n)
{
     char m[500];
     int i=0,j=0;
     while (i<n)
     {
        m[i] = s[i];
        i++;
     }
     while (t[j])
     {
         m[i+j] = t[j];
         j++;
     }
     while (s[i-1])
     {
         m[i+j] = s[i];
         i++;
     }
     printf("%s\n",m);
 }