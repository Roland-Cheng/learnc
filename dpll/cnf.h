#pragma once
#include "global.h"
#include <time.h>
#define TURE 1
#define FALSE 0
#define INCRESE 5

typedef int ElemType;
typedef struct var
{
	int x;
	struct var *next = NULL;
	int change;
} var;
typedef struct clause
{
	int key;
	struct var *first = NULL;
	int change;
} clause;
typedef struct shun
{
	int x;
	struct shun *next;
} shun;

void printsentece(clause *congju, int clanum);
int dplld(clause *&congju, int clanum, int varnum, int floor, int bianliang);
int change(clause *&congju, int clanum, int elem, int floor);
void rechange(clause *&congju, int clanum, int floor);
shun *queue(clause *&congju, int clanum, int varnum);
shun *queue1(clause *&congju, int clanum, int varnum);
void printok(int *ok);