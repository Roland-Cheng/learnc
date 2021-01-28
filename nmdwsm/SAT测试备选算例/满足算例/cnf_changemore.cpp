#include "cnf.h"

int main()
{
	int k;
	FILE *fp;
	int argc = 2;
	char argv[200] = "S/problem2-50.cnf";
	for (k = 1; k < argc; k++)
	{
		fp = fopen(argv, "r");
		int varnum, clanum;
		for (;;)
		{
			char c = fgetc(fp);
			if (c == 'c')
				continue;
			if (c == 'p')
			{
				c = fgetc(fp);
				if (c != ' ')
					continue;
				c = fgetc(fp);
				if (c != 'c')
					continue;
				c = fgetc(fp);
				if (c != 'n')
					continue;
				c = fgetc(fp);
				if (c != 'f')
					continue;
				fscanf(fp, "%d%d", &varnum, &clanum);
				break;
			}
		}
		clause *congju = (clause *)calloc(1, clanum * sizeof(clause));
		for (size_t i = 0; i < clanum; i++)
		{
			var *p = (var *)malloc(sizeof(var));
			congju[i].first = p;
			congju[i].change = 0;
			int bian, n = 0;
			for (;;)
			{
				fscanf(fp, "%d", &bian);
				if (bian != 0)
				{
					n++;
					p->x = bian;
					p->change = 0;
					p->next = (var *)malloc(sizeof(var));
					p = p->next;
				}
				else
				{
					congju[i].key = n;
					p->x = 0;
					p->change = 0;
					p->next = NULL;
					break;
				}
			}
		}
		printf("%d%d\n", varnum, clanum);
		/*find(congju, 1, clanum);
		for (size_t i = 0; i < clanum; i++)
		{
			printf("\n");
			var *p = congju[i].first;
			printf("%d %d %d      ", i, congju[i].key, congju[i].change);
			for (; p; p = p->next)
			{

				printf("%d %d\t", p->x, p->change);
			}
		}
		recover(congju, 1, clanum);
		printf("\n\n\n");
		for (size_t i = 0; i < clanum; i++)
		{
			printf("\n");
			var *p = congju[i].first;
			printf("%d %d %d      ", i, congju[i].key, congju[i].change);
			for (; p; p = p->next)
			{

				printf("%d %d\t", p->x, p->change);
			}
		}*/
		int *shu = (int *)calloc(varnum + 1, sizeof(int));
		for (int k = 1;;)
		{
			if (k == 0)
			{
				printf("not ok\n");
				break;
			}
			else if (k == varnum + 1)
			{
				printf("ok\n");
				break;
			}
			if (shu[k] == 0)
				shu[k] = k;
			//printf("%d\n", shu[k]);
			if (find(congju, shu[k], clanum) == 0)
			{
				if (shu[k] == k)
				{
					shu[k] = -k;
					recover(congju, k, clanum);
				}
				else if (shu[k] == -k)
				{
					for (; shu[k] < 0;)
					{
						recover(congju, -k, clanum);
						shu[k] = 0;
						k--;
					}
					recover(congju, k, clanum);
					shu[k] = -k;
				}
			}
			else
				k++;
		}
	}
	system("pause");
}

int find(clause *&congju, int elem, int clanum)
{
	for (size_t i = 0; i < clanum; i++)
	{
		if (congju[i].change != 0)
			continue;
		var *p;
		for (p = congju[i].first; p; p = p->next)
		{
			if (p->x == elem)
				congju[i].change = elem;
			else if (p->x == -elem)
			{
				congju[i].key--;
				p->change = 1;
			}
		}
		if (congju[i].key == 0)
			return 0;
	}
	return 1;
}

void recover(clause *&congju, int elem, int clanum)
{
	for (size_t i = 0; i < clanum; i++)
	{
		if (congju[i].change == elem)
			congju[i].change = 0;
		else if (congju[i].change != 0)
			continue;
		var *p;
		for (p = congju[i].first; p; p = p->next)
		{
			if (p->x == -elem && p->change == 1)
			{
				congju[i].key++;
				p->change = 0;
			}
		}
	}
}