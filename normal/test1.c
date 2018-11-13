#include <stdio.h>

#include <stdlib.h>

int is_c(int j,int i);

int is_c(int j,int i)

{

  if (j==0||i==0)

  return 1;

  if(i>=1)

  return is_c(j-1,i)*(i-j+1)/j;

}

int main()

{

  int N,a,j,i;

  i=0,j=0;

  scanf("%d",&N);

  for(;N!=0;)

  {

  for(;i<N;)

  {

  for(a=1;a<=(2*(N-i)-1);++a)

   putchar(' ');

 for(j=0;j<=i;++j)

   {

     printf("%4d",is_c(j,i));

   }

   printf("\n");

  i=i+1;

  }

  scanf("%d",&N);

  i=0;
  }

}