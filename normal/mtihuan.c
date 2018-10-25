#include<stdio.h>
int main()
{
		int c;
		c = getchar();
		while (c != EOF){
				if (c == ' ')
						printf("blank");
				else if (c == '\t')
						printf("\\t");
				else if (c == '\n')
						printf("\\n");
		        else if (c != ' ','\t','\n')
				        putchar(c);
		}
		return 0;
}
