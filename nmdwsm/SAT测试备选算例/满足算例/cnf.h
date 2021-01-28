#pragma once
#include "global.h"
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

int dpll(clause *yuanju, int bianliang, int clanum);
int dpllc(clause *&congju, int bianliang, int clanum);
int copycla(clause *yuanju, clause *congju, int clanum);
int makeempty(clause *congju, int clanum);
int find(clause *&congju, int elem, int clanum);
void recover(clause *&congju, int elem, int clanum);