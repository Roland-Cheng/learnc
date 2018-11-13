#include <stdio.h>
void main(void)
{ 
int i,n,s=1;
  printf("Please enter n:");
  scanf("%d",&n);
  i = 1;
  while (i <= n)
    { s=s*i;
    i++;
    }
  printf("%d! = %d",n,s);
}