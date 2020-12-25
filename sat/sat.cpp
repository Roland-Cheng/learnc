#include "sat.h"

int jie[5000];

int main()
{
    int op = 1;
    char s[200];
    int flag;
    int n;
    double cha;
    while (op)
    {
        system("cls");
        putchar('\n');
        printf("\tWelcome to use Menu for SAT\n");
        printf("----------------------------------------------------\n");
        printf("  1.cnf文件处理     2.求解二进制数独     0.退出\n");
        printf("请选择你的操作(0~2)\n"); //输出菜单
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("请输入读取的文件名：");
            scanf("%s", s);
            cnf(s);
            getchar();
            getchar();
            break;
        case 2:
            printf("请问处理几阶数独：");
            scanf("%d", &n);
            getchar();
            if (n % 2)
                printf("请输入偶数\n");
            else
                suduku(n);
            getchar();
            getchar();
            break;
        case 0:
            break;
        default:
            printf("请输入正确的数字！\n"); //其他情况代表输入数字出错，提示重新输入
            getchar();
            getchar();
            break;
        }
    }
    printf("----------------------------------------------------\n");
    printf("程序结束，感谢使用！\n");
    system("pause");
    return 0;
}

void cnf(char *argv)
{
    int k;
    for (size_t i = 0; i < 5000; i++)
        jie[i] = 0;
    int varnum, clanum;
    clause *congju = readfile(argv, clanum, varnum);
    if (congju == NULL)
    {
        printf("文件无法打开\n");
        return;
    }
    clock_t time1, time2;
    time1 = clock();
    int flag = dpll(congju, clanum, varnum, 1, 0);
    time2 = clock();
    double cha;
    cha = (double)(time2 - time1);
    if (flag)
    {
        changefile1(argv);
        FILE *fp = fopen(argv, "wt");
        fprintf(fp, "1\n%.0f", cha);
        for (size_t i = 1; i <= varnum; i++)
        {
            if (i % 10 == 1)
                fprintf(fp, "\n");
            if (jie[i])
                fprintf(fp, "%5d ", jie[i]);
        }
        fprintf(fp, "\n");
        printf("问题可以求解，用时%.0fms,解已存储在“%s”中\n", cha, argv);
        fclose(fp);
    }
    else
    {
        changefile1(argv);
        FILE *fp = fopen(argv, "wt");
        fprintf(fp, "0\n%.0f\n", cha);
        printf("问题不可求解，用时%.0fms\n", cha);
        fclose(fp);
    }
    return;
}

int dpll(clause *&congju, int clanum, int varnum, int floor, int bianliang)
{
    rechange(congju, clanum, floor);
    int *ok = (int *)calloc(varnum, sizeof(int));
    int i = 0;
    ok[0] = change(congju, clanum, bianliang, floor);
    for (; ok[i] != 0 && ok[i] != 3000; ok[i + 1] = change(congju, clanum, ok[i], floor), i++)
        ;
    if (ok[i] == 0)
        return 0;
    shun *shunxu = queue(congju, clanum, varnum);
    if (shunxu->x == 0)
    {
        printok(ok);
        return 1;
    }
    if (dpll(congju, clanum, varnum, floor + 1, shunxu->next->x))
    {
        printok(ok);
        jie[shunxu->next->x] = shunxu->next->x;
        return 1;
    }
    else
    {
        if (dpll(congju, clanum, varnum, floor + 1, -shunxu->next->x))
        {
            printok(ok);
            jie[shunxu->next->x] = -shunxu->next->x;
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
    return 3000;
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
        jie[abs(ok[i])] = ok[i];
}

clause *readfile(char *argv, int &clanum, int &varnum)
{
    FILE *fp;
    fp = fopen(argv, "r");
    if (fp == NULL)
        return NULL;
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
            fscanf(fp, " %d %d", &varnum, &clanum);
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
            fscanf(fp, " %d", &bian);
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
    return congju;
}

void changefile1(char *&s)
{
    char *p = s;
    for (; *p != '.'; p++)
        ;
    p++;
    *p = 'r';
    p++;
    *p = 'e';
    p++;
    *p = 's';
    p++;
    *p = '\0';
    return;
}

void changefile2(char *&s)
{
    char *p = s;
    for (; *p != '.'; p++)
        ;
    p++;
    *p = 't';
    p++;
    *p = 'x';
    p++;
    *p = 't';
    p++;
    *p = '\0';
    return;
}

void changefile3(char *&s)
{
    char *p = s;
    for (; *p != '.'; p++)
        ;
    p++;
    *p = 'c';
    p++;
    *p = 'n';
    p++;
    *p = 'f';
    p++;
    *p = '\0';
    return;
}

void suduku(int n)
{
    char *s = (char *)calloc(100, sizeof(char));
    FILE *fp;
    int line = 0;
    printf("1.键盘输入    2.文件输入   \n请选择输入方式：");
    int x;
    scanf("%d", &x);
    if (x != 1 && x != 2)
    {
        printf("请输入正确的值\n");
        return;
    }
    else if (x == 2)
    {
        printf("请输入文件名：");
        scanf("%s", s);
        FILE *fp0 = fopen(s, "r");
        if (fp0 == NULL)
        {
            printf("文件打不开\n");
            return;
        }
        changefile3(s);
        fp = fopen(s, "wt");
        fprintf(fp, "p cnf               \n");
        for (size_t i = 1; i <= n * n; i++)
        {
            char c = fgetc(fp0);
            if (c == '0')
            {
                fprintf(fp, "%d 0\n", -i);
                line++;
            }
            else if (c == '1')
            {
                fprintf(fp, "%d 0\n", i);
                line++;
            }
        }
        fclose(fp0);
    }
    else
    {
        printf("请输入将的存储文件名：");
        scanf("%s", s);
        getchar();
        changefile3(s);
        fp = fopen(s, "wt");
        changefile2(s);
        FILE *fp1 = fopen(s, "wt");
        fprintf(fp, "p cnf               \n");
        printf("请输入句子：");
        for (size_t i = 1; i <= n * n; i++)
        {
            char c = getchar();
            fprintf(fp1, "%c", c);
            if (c == '0')
            {
                fprintf(fp, "%d 0\n", -i);
                line++;
            }
            else if (c == '1')
            {
                fprintf(fp, "%d 0\n", i);
                line++;
            }
        }
        printf("数独源文件已经存储进文件“%s”中\n", s);
        fclose(fp1);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n - 2; j++)
        {
            int p = (i - 1) * n + j, q = (j - 1) * n + i;
            fprintf(fp, "%d %d %d 0\n", p, p + 1, p + 2);
            fprintf(fp, "%d %d %d 0\n", -p, -p - 1, -p - 2);
            fprintf(fp, "%d %d %d 0\n", q, q + n, q + n + n);
            fprintf(fp, "%d %d %d 0\n", -q, -q - n, -q - n - n);
            line += 4;
        }
    }
    int *zhan = (int *)calloc(n / 2 + 2, sizeof(int));
    int zhanp = n / 2 + 1;
    for (size_t i = 1; i <= n / 2; i++)
    {
        zhan[i] = i;
    }
    zhan[zhanp] = zhanp - 1;
    for (int k = n;;)
    {
        for (; zhan[zhanp] >= k;)
        {
            zhan[zhanp] = 0;
            zhanp--;
            k--;
        }
        if (zhanp == 0)
            break;
        zhan[zhanp]++;
        for (; zhanp < n / 2 + 1;)
        {
            zhan[zhanp + 1] = zhan[zhanp] + 1;
            zhanp++;
            k++;
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n / 2 + 1; j++)
                fprintf(fp, "%d ", (i - 1) * n + zhan[j]);
            fprintf(fp, "0\n");
            for (int j = 1; j <= n / 2 + 1; j++)
                fprintf(fp, "%d ", -((i - 1) * n + zhan[j]));
            fprintf(fp, "0\n");
            for (int j = 1; j <= n / 2 + 1; j++)
                fprintf(fp, "%d ", (zhan[j] - 1) * n + i);
            fprintf(fp, "0\n");
            for (int j = 1; j <= n / 2 + 1; j++)
                fprintf(fp, "%d ", -((zhan[j] - 1) * n + i));
            fprintf(fp, "0\n");
            line += 4;
        }
    }
    int times = 0;
    for (size_t j = 1; j < n; j++)
    {
        for (size_t k = j + 1; k <= n; k++)
        {
            for (size_t l = 0; l <= n; l++)
            {
                if (l == 0)
                {
                    int bian1 = times * (3 * n + 1) + 1 + n * n;
                    fprintf(fp, "%d 0\n", bian1);
                    fprintf(fp, "%d ", -bian1);
                    for (size_t m = 1; m <= n; m++)
                        fprintf(fp, "%d ", -(bian1 + 3 * m - 2));
                    fprintf(fp, "0\n");
                    for (size_t m = 1; m <= n; m++)
                        fprintf(fp, "%d %d 0\n", (bian1 + 3 * m - 2), bian1);
                    line += n + 2;
                    continue;
                }
                for (size_t s = 0; s <= 2; s++)
                {
                    int bian2 = times * (3 * n + 1) + l * 3 - 1 + n * n;
                    if (s == 0)
                    {
                        fprintf(fp, "%d %d %d 0\n", -bian2, bian2 + 1, bian2 + 2);
                        fprintf(fp, "%d %d 0\n", bian2, -bian2 - 1);
                        fprintf(fp, "%d %d 0\n", bian2, -bian2 - 2);
                        line += 3;
                    }
                    else if (s == 1)
                    {
                        fprintf(fp, "%d %d 0\n", -((j - 1) * n + l), -(bian2 + 1));
                        fprintf(fp, "%d %d 0\n", -((k - 1) * n + l), -(bian2 + 1));
                        fprintf(fp, "%d %d %d 0\n", ((j - 1) * n + l), ((k - 1) * n + l), (bian2 + 1));
                        line += 3;
                    }
                    else
                    {
                        fprintf(fp, "%d %d 0\n", ((j - 1) * n + l), -(bian2 + 2));
                        fprintf(fp, "%d %d 0\n", ((k - 1) * n + l), -(bian2 + 2));
                        fprintf(fp, "%d %d %d 0\n", -((j - 1) * n + l), -((k - 1) * n + l), (bian2 + 2));
                        line += 3;
                    }
                }
            }
            times++;
        }
    }
    times = 0;
    for (size_t j = 1; j < n; j++)
    {
        for (size_t k = j + 1; k <= n; k++)
        {
            for (size_t l = 0; l <= n; l++)
            {
                if (l == 0)
                {
                    int bian1 = n * (n - 1) * (3 * n + 1) / 2 + times * (3 * n + 1) + 1 + n * n;
                    fprintf(fp, "%d 0\n", bian1);
                    fprintf(fp, "%d ", -bian1);
                    for (size_t m = 1; m <= n; m++)
                        fprintf(fp, "%d ", -(bian1 + 3 * m - 2));
                    fprintf(fp, "0\n");
                    for (size_t m = 1; m <= n; m++)
                        fprintf(fp, "%d %d 0\n", (bian1 + 3 * m - 2), bian1);
                    line += n + 2;
                    continue;
                }
                for (size_t s = 0; s <= 2; s++)
                {
                    int bian2 = n * (n - 1) * (3 * n + 1) / 2 + times * (3 * n + 1) + l * 3 - 1 + n * n;
                    if (s == 0)
                    {
                        fprintf(fp, "%d %d %d 0\n", -bian2, bian2 + 1, bian2 + 2);
                        fprintf(fp, "%d %d 0\n", bian2, -bian2 - 1);
                        fprintf(fp, "%d %d 0\n", bian2, -bian2 - 2);
                        line += 3;
                    }
                    else if (s == 1)
                    {
                        fprintf(fp, "%d %d 0\n", -((l - 1) * n + j), -(bian2 + 1));
                        fprintf(fp, "%d %d 0\n", -((l - 1) * n + k), -(bian2 + 1));
                        fprintf(fp, "%d %d %d 0\n", ((l - 1) * n + j), ((l - 1) * n + k), (bian2 + 1));
                        line += 3;
                    }
                    else
                    {
                        fprintf(fp, "%d %d 0\n", ((l - 1) * n + j), -(bian2 + 2));
                        fprintf(fp, "%d %d 0\n", ((l - 1) * n + k), -(bian2 + 2));
                        fprintf(fp, "%d %d %d 0\n", -((l - 1) * n + j), -((l - 1) * n + k), (bian2 + 2));
                        line += 3;
                    }
                }
            }
            times++;
        }
    }
    fclose(fp);
    changefile3(s);
    fp = fopen(s, "r+");
    fprintf(fp, "p cnf %d %d", n * n + (3 * n + 1) * n * (n - 1), line);
    fclose(fp);
    printf("数独的cnf文件已经存放进“%s”中\n", s);
    getchar();
    printf("是否对其求解？（y/n）：");
    char c;
    for (c = getchar(); c != 'y' && c != 'Y' && c != 'n' && c != 'N'; c = getchar())
        printf("请输入正确值（y/n）：");
    if (c == 'y' || c == 'Y')
        shuducnf(s, n);
    return;
}

void shuducnf(char *argv, int n)
{
    int k;
    for (size_t i = 0; i < 5000; i++)
        jie[i] = 0;
    int varnum, clanum;
    clause *congju = readfile(argv, clanum, varnum);
    clock_t time1, time2;
    time1 = clock();
    int flag = dpll(congju, clanum, varnum, 1, 0);
    time2 = clock();
    double cha;
    cha = (double)(time2 - time1);
    if (flag)
    {
        changefile1(argv);
        FILE *fp = fopen(argv, "wt");
        fprintf(fp, "解题用时：%.0fms\n以下是解答:", cha);
        for (size_t i = 1; i <= n * n; i++)
        {
            if (i % n == 1)
                fprintf(fp, "\n");
            if (jie[i] > 0)
                fprintf(fp, "1  ");
            else
                fprintf(fp, "0  ");
        }
        fprintf(fp, "\n");
        printf("数独已求解，用时%.0fms,解已存储在“%s”中\n", cha, argv);
        fclose(fp);
    }
    else
    {
        printf("数独不可求解，用时%.0fms\n", cha);
    }
}