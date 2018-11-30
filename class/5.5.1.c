#include<stdio.h>
void strnins(char s[],char t[],int n);

int main()
{
    char s[] ="asdsakafjfkj";
    char *p;
    strnins(s,s,4);
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
     while (s[i])
     {
         m[i+j] = s[i];
         i++;
     }
     printf("%s\n",m);
 }