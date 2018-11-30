#include<stdio.h>
char *strncat(char s[],char t[],int n);
int main(void)
{
      char a[50]="The adopted symbol is ",b[27]="abcdefghijklmnopqrstuvwxyz";
      //a = strncat(a, b, 4);
      printf("%s\n",strncat(a,b,4));
      return 0;
}
char *strncat(char s[],char t[], int n)
{
      int i = 0, j;
while(s[i++]) ;
for(j = 0,i = i-1; j < n && t[j];)
s[i++] = t[j++];
      s[i] = '\0';
      return s;
}