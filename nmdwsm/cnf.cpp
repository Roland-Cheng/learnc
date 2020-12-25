#include"cnf.h"

int main()
{
	int k;
	FILE* fp;
	int argc=2;
	char argv[200]="/home/roland/git/learnc/nmdwsm/SAT测试备选算例/满足算例/S/problem1-20.cnf";
	for (k = 1; k < argc; k++)
	{
		fp = fopen(argv, "r");
		int varnum, clanum;
		for (;;)
		{
			char c = fgetc(fp);
			if (c == 'c') continue;
			if (c == 'p')
			{
				c = fgetc(fp);
				if (c != ' ') continue;
				c = fgetc(fp);
				if (c != 'c') continue;
				c = fgetc(fp);
				if (c != 'n') continue;
				c = fgetc(fp);
				if (c != 'f') continue;
				fscanf(fp, "%d%d", &varnum, &clanum);
				break;
			}
		}
		clause* congju = (clause*)calloc(1, clanum * sizeof(clause));
		for (size_t i = 0; i < clanum; i++)
		{
			var* p = (var*)malloc(sizeof(var));
			congju[i].first = p;
			int bian, n = 0;
			for (;;)
			{
				fscanf(fp, "%d", &bian);
				if (bian != 0)
				{
					n++;
					p->x = bian;
					p->next = (var*)malloc(sizeof(var));
					p = p->next;
				}
				else
				{
					congju[i].key = n;
					p->x = 0;
					break;
				}
			}
		}
		printf("%d%d\n", varnum, clanum);
		/*for (size_t i = 0; i < clanum; i++)
		{
			printf("\n");
			var* p = congju[i].first;
			for (size_t m = 0; m <= congju[i].key; m++)
			{
				printf("%d ", p->x);
				p = p->next;
			}
		}*/
		int s=dpll(congju, varnum+1, clanum);
		if (s) printf("OK");
		if (s==FALSE) printf("NOT OK");
		//for (size_t i = 0; i < 20; i++) printf("%d\n",congju[i].key);
		//gai(congju);
		//for (size_t i = 0; i < 20; i++) printf("%d\n",congju[i].key);
	}
	//system("pause");
}

int dpll(clause* yuanju, int bianliang, int clanum)
{
	clause congju[clanum];
	copycla(yuanju,congju,clanum);
	if (bianliang == 0)
	{
		for (size_t i = 0; i < clanum; i++)
		{
			if (congju[i].first) return FALSE;
		}
		return TURE;
	}
	else
	{
		for (size_t i = 0; i < clanum; i++)
		{
			var* p = congju[i].first;
			var* q = NULL;
			if (p && p->x == -bianliang)
			{
				congju[i].first = congju[i].first->next;
				free(p);
				congju[i].key--;
			}
			for (p = congju[i].first; p != NULL && p->x != bianliang; p = p->next);
			if (p != NULL)
			{
				p = congju[i].first;
				congju[i].key = 0;
				congju[i].first = NULL;
				/*do
				{
					free(q);
					q = p;
					p = p->next;
				} while (p->next);*/
			}
			for (p = congju[i].first, q = NULL;p!=NULL && p->next != NULL && p->next->x != -bianliang; p = p->next);
			if (p!=NULL && p->next != NULL)
			{
				q = p->next;
				p->next = p->next->next;
				free(q);
				congju[i].key--;
			}
			if (congju[i].key == 0 && congju[i].first ) return FALSE;
		}
	}
	/*for (size_t i = 0; i < clanum; i++)
		{
			printf("\n %d ",congju[i].key);
			var* p = congju[i].first;
			for (;p;p=p->next)
			{
				printf("%d ", p->x);
			}
		}*/
	if(bianliang<0) bianliang=-bianliang;
	if (dpll(congju, bianliang - 1, clanum)) return TURE;
	else return dpll(congju, -(bianliang - 1),clanum);
}

int copycla(clause* yuanju,clause* congju,int clanum)
{
	for (size_t i = 0; i < clanum; i++)
	{
		congju[i].key=yuanju[i].key;
		var *p=yuanju[i].first,*q=NULL;
		if(yuanju[i].key) 
		{
			congju[i].first=(var*)calloc(1,sizeof(var));
			congju[i].first->x=yuanju[i].first->x;
			for(q=congju[i].first;p->next;p=p->next)
			{
				q->next=(var*)calloc(1,sizeof(var));
				q->next->x=p->next->x;
				q=q->next;
			}
			q->next=NULL;
		}
		else {
			congju[i].key=0;
			congju[i].first=NULL;
		}
	}
}