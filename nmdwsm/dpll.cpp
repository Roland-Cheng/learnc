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
		int flag = dplla(congju, varnum, 1, clanum);
		if (flag)
			printf("ok\n");
		else
		{
			flag = dplla(congju, varnum, -1, clanum);
			if (flag)
				printf("ok\n");
			else
				printf("not ok\n");
		}
	}
	//system("pause");
}

int dplla(clause *&congju, int varnum, int bianliang, int clanum)
{
	if (check(congju, bianliang, clanum) == 1)
	{
		//printsentece(congju, clanum);
		shun *shunxu = (shun *)malloc(sizeof(shun));
		paixu(congju, varnum, clanum, shunxu);
		if (shunxu->x == 0)
			return 1;
		for (shun *p = shunxu->next; p->next; p = p->next)
		{
			if (dplla(congju, varnum, p->x, clanum))
			{
				printf("%d ", p->x);
				return 1;
			}
		}
		return 0;
	}
	else
	{
		recover(congju, bianliang, clanum);
		return 0;
	}
	/*printf("%d\n", bianliang);
	if (check(congju, bianliang, clanum))
	{
		if (bianliang == varnum || bianliang == -varnum)
			return 1;
		if (bianliang > 0)
		{
			if (dplla(congju, varnum, bianliang + 1, clanum))
			{
				return 1;
			}
			else
				return dplla(congju, varnum, -bianliang - 1, clanum);
		}
		else
		{
			if (dplla(congju, varnum, 1 - bianliang, clanum))
			{
				return 1;
			}
			else
				return dplla(congju, varnum, -1 + bianliang, clanum);
		}
	}
	else
	{
		recover(congju, bianliang, clanum);
		return 0;
	}*/
}

int check(clause *&congju, int elem, int clanum)
{
	int flag = 0;
	for (size_t i = 0; i < clanum; i++)
	{
		if (congju[i].change != 0)
			continue;
		var *p;
		for (p = congju[i].first; p->next; p = p->next)
		{
			//if (p->change)
			//continue;
			if (p->x == elem)
			{
				p->change = 1;
				congju[i].change = elem;
			}

			else if (p->x == -elem)
			{
				congju[i].key--;
				p->change = 1;
			}
		}
		if (congju[i].key == 0)
			flag = 1;
	}
	if (flag)
		return 0;
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
		for (p = congju[i].first; p->next; p = p->next)
		{
			if (p->x == elem)
			{
				p->change = 0;
				congju[i].change = 0;
			}
			if (p->x == -elem)
			{
				congju[i].key++;
				p->change = 0;
			}
		}
	}
}

int paixu(clause *congju, int varnum, int clanum, shun *&shunxu)
{
	float *shu = (float *)calloc(varnum * 2 + 1, sizeof(float));
	for (size_t i = 0; i < clanum; i++)
	{
		if (congju[i].change != 0)
			continue;
		var *p = congju[i].first;
		/*if (congju[i].key == 1)
		{
			for (; p->next; p = p->next)
			{
				if (p->change)
					continue;
				shu[varnum - p->x] -= 10086;
			}
		}*/
		for (p = congju[i].first; p->next; p = p->next)
		{
			if (p->change)
				continue;
			shu[p->x + varnum]++;
			shu[varnum - p->x] += pow(2, (-congju[i].key));
		}
	}
	/*for (size_t i = 1; i <= varnum; i++)
	{
		if (shu[varnum - i] < 0 && shu[varnum + i] < 0)
			return 0;
	}*/
	shunxu->next = (shun *)malloc(sizeof(shun));
	shunxu->x = 0;
	shunxu->next->x = 0;
	shunxu->next->next = NULL;
	for (size_t i = 0; i < varnum * 2 + 1; i++)
	{
		if (shu[i] == 0)
			continue;
		shun *p, *q;
		for (p = shunxu; shu[i] < shu[p->next->x + varnum]; p = p->next)
			;
		q = p->next;
		p->next = (shun *)malloc(sizeof(shun));
		p->next->x = i - varnum;
		p->next->next = q;
		shunxu->x++;
	}
	free(shu);
	return 1;
}

void printsentece(clause *congju, int clanum)
{
	for (size_t i = 0; i < clanum; i++)
	{
		printf("\n");
		var *p = congju[i].first;
		printf("%d %d %d\t\t", i, congju[i].key, congju[i].change);
		for (; p; p = p->next)
		{
			printf("%d %d\t", p->x, p->change);
		}
	}
	printf("\n");
}
