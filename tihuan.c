#include<stdio.h>
int main()
{
		int c;
		while ((c = getchar()) != EOF){
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
