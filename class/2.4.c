#include <stdio.h>
void main(void)
{ 
int i,n,s=1;
  printf("Please enter S:");
  scanf("%d",&n);
  for(i=1;s<=n;)
    { s=s*i;
     i++;}
  printf("n = %d",i-1);
}