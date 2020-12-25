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
		int s = dpllc(congju, varnum + 1, clanum);
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

int dpllc(clause *&congju, int bianliang, int clanum)
{
	/*for (size_t i = 0; i < clanum; i++)
	{ 
	if (congju[i].change == 0)
		printf("%d", congju[i].key);
}*/
	//printf("%d\n", bianliang);
	if (bianliang == 0)
		return TURE;
	for (size_t i = 0; i < clanum; i++)
	{
		if (congju[i].change != 0)
			continue;
		var *p;
		for (p = congju[i].first; p; p = p->next)
		{
			if (p->x == bianliang)
			{
				congju[i].change = bianliang;
			}
			if (p->x == -bianliang)
			{
				congju[i].key--;
				p->change = 1;
			}
		}
		if (congju[i].key == 0)
			return FALSE;
	}
	if (bianliang < 0)
		bianliang = -bianliang;
	int s = dpllc(congju, bianliang - 1, clanum);
	if (s == TURE)
		return s;
	else
	{
		for (size_t i = 0; i < clanum; i++)
		{
			if (congju[i].change != 0 && congju[i].change != bianliang - 1)
				continue;
			var *p = congju[i].first;
			for (; p; p = p->next)
			{
				if (p->x == 1 - bianliang && p->change == 1)
				{
					congju[i].key++;
					p->change = 0;
				}
				if (p->x == bianliang - 1)
				{
					congju[i].change = 0;
				}
			}
		}
		s = dpllc(congju, 1 - bianliang, clanum);
		if (s == FALSE)
		{
			for (size_t i = 0; i < clanum; i++)
			{
				if (congju[i].change != 0 && congju[i].change != 1 - bianliang)
					continue;
				var *p = congju[i].first;
				for (; p; p = p->next)
				{
					if (p->x == bianliang - 1 && p->change == 1)
					{
						congju[i].key++;
						p->change = 0;
					}
					if (p->x == 1 - bianliang)
					{
						congju[i].change = 0;
					}
				}
			}
		}
		return s;
	}
}