#include "cnf.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int find(clause *&congju, int elem, int clanum);
int main()
{
	int k;
	FILE *fp;
	int argc = 2;
	char argv[200] = /*"problem2-50.txt"; //*/ "problem1-20.cnf";
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
		printf("%d %d\n", varnum, clanum);
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
		int flag = dpllb(congju, varnum, clanum);
		if (flag)
			printf("ok\n");
		else
			printf("not ok\n");
	}
	system("pause");
}

int dpllb(clause *&congju, int varnum, int clanum)
{
	int a[1000], b[1000];
	int i, t;
	for (i = 1; i <= 1000; i++)
		a[i] = 11, b[i] = 12;
	int flag = 0;
	var *q;
	while (flag == 0)
	{
		flag = 1;
		for (i = 0; i < clanum; i++)
			if (congju[i].change == 0 && congju[i].key == 1)
			{

				for (q = congju[i].first; q->change != 0; q = q->next)
					;
				t = q->x;
				//printf("%d-\n",t);
				/*for (size_t i = 0; i < clanum; i++)
	            {
	              if(congju[i].change)continue;
		          printf("\n");
		          var *p = congju[i].first;
		          printf("%d %d %d      ", i, congju[i].key, congju[i].change);
                  for (; p; p = p->next)
		            {
			      if(p->change)continue;
                  printf("%d\t", p->x);
		             }
	           }
	        printf("\n\n");*/
				flag = 0;
				if (!find(congju, t, clanum))
				{
					recover(congju, t, clanum);
					return 0;
				}
				break;
			}
	}
	float *shu = (float *)calloc(varnum * 2 + 1, sizeof(float));
	for (size_t i = 0; i < clanum; i++)
	{
		if (congju[i].change != 0)
			continue;
		var *p;
		for (p = congju[i].first; p->next; p = p->next)
		{
			if (p->change != 0)
				continue;
			shu[p->x + varnum]++;
			shu[varnum - p->x] += pow(2, (-congju[i].key));
		}
	}
	shun *shunxu = (shun *)malloc(sizeof(shun));
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
	/*
	for (size_t i = 0; i < varnum * 2 + 1; i++)
		printf("%d %f\n", i - varnum, shu[i]);
	printf("\n\n");*/
	/*for (shun *p = shunxu->next; p; p = p->next)
		printf("%d %.4f\t", p->x, shu[p->x + varnum]);
	printf("\n\n\n");*/
	if (shunxu->x == 0)
		return 1;
	free(shu);
	/*for (size_t i = 0; i < clanum; i++)
	{
	    if(congju[i].change)continue;
		printf("\n");
		var *p = congju[i].first;
		printf("%d %d %d      ", i, congju[i].key, congju[i].change);
		for (; p; p = p->next)
		{
			 if(p->change)continue;
             printf("%d\t", p->x);
		}
	}
	printf("\n\n");*/
	for (shun *p = shunxu->next; p->next != NULL; p = p->next)
	{
		//for(i=1;i<=1000;i++)
		//if(a[i]==b[i])return 0;
		// shun *p = shunxu->next;
		int k = find(congju, p->x, clanum);
		if (k == 1)
		{
			//printf("%d**\n",p->x);
			int j = dpllb(congju, varnum, clanum);
			if (j == 1)
				return 1;
			else
				recover(congju, p->x, clanum);
		}
		else
		{
			// int j;
			//  k=find(congju, -p->x, clanum);
			// if(k)
			// {
			//      j=dpllb(congju, varnum, clanum);
			//      if(j)return j;
			//  }

			/*if(p->x<0)b[-p->x]=1;
            else a[p->x]=1;
			printf("%d///\n",p->x), */
			recover(congju, -p->x, clanum);
		}
	}
	return 0;
}

int find(clause *&congju, int elem, int clanum)
{
	int i;
	for (i = 0; i < clanum; i++)
	{
		if (congju[i].change != 0)
			continue;
		var *p;
		for (p = congju[i].first; p; p = p->next)
		{
			if (p->change)
				continue;
			if (p->x == elem)
				congju[i].change = elem;
			else if (p->x == -elem)
			{
				congju[i].key--;
				p->change = 1;
			}
		}
	}
	for (i = 0; i < clanum; i++)
		if (congju[i].key == 0 && congju[i].change == 0)
		{ /*var *p = congju[i].first;
		          printf("%d %d %d      ", i, congju[i].key, congju[i].change);
                  for (; p; p = p->next)
		            {
			      if(p->change)continue;
                  printf("%d\t", p->x);
                  printf("\n");*/
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
