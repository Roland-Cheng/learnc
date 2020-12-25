#include "cnf.h"

int main()
{
	int k;
	FILE *fp;
	int argc = 2;
	char argv[200] = "unsat-5cnf-30.cnf";
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
			int bian, n = 0;
			for (;;)
			{
				fscanf(fp, "%d", &bian);
				if (bian != 0)
				{
					n++;
					p->x = bian;
					p->next = (var *)malloc(sizeof(var));
					p = p->next;
				}
				else
				{
					congju[i].key = n;
					p->x = 0;
					p->next = NULL;
					break;
				}
			}
		}
		printf("%d%d\n", varnum, clanum);
		/*for (size_t i = 0; i < clanum; i++)
		{
			printf("\n");
			var *p = congju[i].first;
			for (size_t m = 0; m <= congju[i].key; m++)
			{
				printf("%d ", p->x);
				p = p->next;
			}
		}*/
		int s = dpll(congju, varnum + 1, clanum);
		if (s)
			printf("OK");
		if (s == FALSE)
			printf("NOT OK");
		//for (size_t i = 0; i < 20; i++) printf("%d\n",congju[i].key);
		//gai(congju);
		//for (size_t i = 0; i < 20; i++) printf("%d\n",congju[i].key);
	}
	system("pause");
}

int dpll(clause *yuanju, int bianliang, int clanum)
{
	if (bianliang == 0)
		return TURE;
	clause *congju = (clause *)calloc(clanum, sizeof(clause));
	for (int i = 0; i < clanum; i++)
	{
		var *p = yuanju[i].first;
		var *q = congju[i].first;
		int flag;
		for (flag = 0; p != NULL; p = p->next)
		{
			if (p->x == bianliang)
				flag = 1;
			if (p->x == -bianliang)
				flag = -1;
		}
		//printf("%d\n", flag);
		if (flag == 1 || yuanju[i].first == NULL)
		{
			congju[i].first = NULL;
			congju[i].key = 0;
			continue;
		}

		if (flag == 0)
		{
			congju[i].key = yuanju[i].key;
			congju[i].first = (var *)calloc(1, sizeof(var));
			for (q = congju[i].first, p = yuanju[i].first; p->next;)
			{
				q->next = (var *)calloc(1, sizeof(var));
				q->x = p->x;
				q = q->next;
				p = p->next;
			}
			q->x = 0;
			q->next = NULL;
		}
		if (yuanju[i].key == 1 && flag == -1)
			return FALSE;
		else if (flag == -1)
		{
			congju[i].key = yuanju[i].key;
			congju[i].first = (var *)calloc(1, sizeof(var));
			for (q = congju[i].first, p = yuanju[i].first; p->next; p = p->next)
			{
				if (p->x == -bianliang)
				{
					congju[i].key--;
					continue;
				}
				q->next = (var *)calloc(1, sizeof(var));
				q->x = p->x;
				q = q->next;
			}
			q->x = 0;
			q->next = NULL;
		}
	}
	/*for (size_t i = 0; i < clanum; i++)
	{
		printf("\n");
		var *p = congju[i].first;
		if (p == NULL)
			printf("NULL");
		for (; p; p = p->next)
		{
			printf("%d ", p->x);
		}
	}
	printf("\n\n");*/
	if (bianliang < 0)
		bianliang = -bianliang;
	int s = dpll(congju, bianliang - 1, clanum);
	if (s == TURE)
		return s;
	else
	{
		s = dpll(congju, 1 - bianliang, clanum);
		makeempty(congju, clanum);
		return s;
	}
}

int makeempty(clause *congju, int clanum)
{
	for (size_t i = 0; i < clanum; i++)
	{
		var *p = congju[i].first;
		var *q;
		for (; p;)
		{
			q = p;
			p = p->next;
			free(q);
		}
	}
	free(congju);
}
