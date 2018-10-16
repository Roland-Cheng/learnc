#include<stdio.h>
int main()
{
		int c;
		c = getchar();
		while (c != EOF){
				if (c == ' ')
						printf("blank");
				if (c == '\t')
						printf("\\t");
				if (c == '\n')
						printf("\\n");
		if (c != ' ','\t','\n')
				putchar(c);
		}
		return 0;
}
