#include "cnf.h"

int main()
{
    int k;
    FILE *fp;
    int argc = 2;
    char argv[200] = "data.cnf";
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
        clock_t time1, time2;
        time1 = clock();
        int flag = dplld(congju, clanum, varnum, 1, 0);
        time2 = clock();
        double cha;
        cha = (double)(time2 - time1);
        printf("\n%.0fms\n", cha);
        if (flag)
            printf("ok\n");
        else
            printf("not ok\n");
    }
    system("pause");
}

int dplld(clause *&congju, int clanum, int varnum, int floor, int bianliang)
{
    rechange(congju, clanum, floor);
    int *ok = (int *)calloc(varnum, sizeof(int));
    int i = 0;
    ok[0] = change(congju, clanum, bianliang, floor);
    for (; ok[i] != 0 && ok[i] != 1000; ok[i + 1] = change(congju, clanum, ok[i], floor), i++)
        ;
    if (ok[i] == 0)
        return 0;
    shun *shunxu = queue1(congju, clanum, varnum);
    if (shunxu->x == 0)
    {
        printok(ok);
        return 1;
    }
    if (dplld(congju, clanum, varnum, floor + 1, abs(shunxu->next->x)))
    {
        printok(ok);
        printf("%d ", abs(shunxu->next->x));
        return 1;
    }
    else
    {
        if (dplld(congju, clanum, varnum, floor + 1, -abs(shunxu->next->x)))
        {
            printok(ok);
            printf("%d ", -abs(shunxu->next->x));
            return 1;
        }
        else
            return 0;
    }
}

int change(clause *&congju, int clanum, int elem, int floor)
{
    int flag1 = 0, flag2 = 0;
    for (size_t i = 0; i < clanum; i++)
    {
        if (congju[i].change)
            continue;
        var *p = congju[i].first;
        for (p = congju[i].first; p->next; p = p->next)
        {
            if (p->change)
                continue;
            if (p->x == elem)
            {
                congju[i].change = floor;
                p->change = floor;
                congju[i].key--;
            }
            else if (p->x == -elem)
            {
                p->change = floor;
                congju[i].key--;
            }
        }
        if (congju[i].key == 0 && congju[i].change == 0)
            flag1 = 1;
        else if (congju[i].key == 1 && congju[i].change == 0)
        {
            for (p = congju[i].first; p->change; p = p->next)
                ;
            flag2 = p->x;
        }
    }
    if (flag1)
        return 0;
    if (flag2)
        return flag2;
    return 1000;
}

void rechange(clause *&congju, int clanum, int floor)
{
    for (size_t i = 0; i < clanum; i++)
    {
        if (congju[i].change < floor && congju[i].change != 0)
            continue;
        else
            congju[i].change = 0;
        var *p = congju[i].first;
        for (p = congju[i].first; p->next; p = p->next)
        {
            if (p->change < floor)
                continue;
            else
            {
                congju[i].key++;
                p->change = 0;
            }
        }
    }
}

shun *queue(clause *&congju, int clanum, int varnum)
{
    float *shu = (float *)calloc(varnum * 2 + 1, sizeof(float));
    for (size_t i = 0; i < clanum; i++)
    {
        if (congju[i].change)
            continue;
        var *p = congju[i].first;
        for (p = congju[i].first; p->next; p = p->next)
        {
            if (p->change)
                continue;
            shu[varnum + p->x]++;
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
    free(shu);
    return shunxu;
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

shun *queue1(clause *&congju, int clanum, int varnum)
{
    float *shu = (float *)calloc(varnum + 1, sizeof(float));
    for (size_t i = 0; i < clanum; i++)
    {
        if (congju[i].change)
            continue;
        var *p = congju[i].first;
        for (p = congju[i].first; p->next; p = p->next)
        {
            if (p->change)
                continue;
            shu[abs(p->x)] += pow(2, (-congju[i].key));
        }
    }
    shun *shunxu = (shun *)malloc(sizeof(shun));
    shunxu->next = (shun *)malloc(sizeof(shun));
    shunxu->x = 0;
    shunxu->next->x = 0;
    shunxu->next->next = NULL;
    for (size_t i = 1; i < varnum + 1; i++)
    {
        if (shu[i] == 0)
            continue;
        shun *p, *q;
        for (p = shunxu; shu[i] < shu[p->next->x]; p = p->next)
            ;
        q = p->next;
        p->next = (shun *)malloc(sizeof(shun));
        p->next->x = i;
        p->next->next = q;
        shunxu->x++;
    }
    free(shu);
    return shunxu;
}

void printok(int *ok)
{
    for (int i = 0; ok[i] != 0 && ok[i] != 1000; i++)
        printf("%d ", ok[i]);
}