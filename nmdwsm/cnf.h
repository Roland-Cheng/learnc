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

int dpll(clause *yuanju, int bianliang, int clanum);
int paixu(clause *congju, int varnum, int clanum, shun *&shunxu);
void printsentece(clause *congju, int clanum);
int dpllc(clause *&congju, int bianliang, int clanum);
int dpllb(clause *&congju, int varnum, int clanum);
int dplla(clause *&congju, int varnum, int bianliang, int clanum);
int copycla(clause *yuanju, clause *congju, int clanum);
int makeempty(clause *congju, int clanum);
int check(clause *&congju, int elem, int clanum);
void recover(clause *&congju, int elem, int clanum);
int catchmin(clause *congju, int clanum);
int find(clause *&congju, int elem, int clanum);
int dplld(clause *&congju, int clanum, int varnum, int floor, int bianliang);
int change(clause *&congju, int clanum, int elem, int floor);
void rechange(clause *&congju, int clanum, int floor);
shun *queue(clause *&congju, int clanum, int varnum);