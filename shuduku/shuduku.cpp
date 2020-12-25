#include "shudu.h"

#define n 6

int main()
{
    int shudu[n][n];
    int line = 0;
    char s[200] = "1.txt";
    FILE *fp0 = fopen(s, "r");
    FILE *fp = fopen("data.cnf", "w");
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
    int zhan[n / 2 + 2] = {0};
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
                    fprintf(fp, "%d ", -bian1);
                    for (size_t m = 1; m <= n; m++)
                        fprintf(fp, "%d ", -(bian1 + 3 * m - 2));
                    fprintf(fp, "0\n");
                    for (size_t m = 1; m <= n; m++)
                        fprintf(fp, "%d %d 0\n", (bian1 + 3 * m - 2), bian1);
                    line += n + 1;
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
    fp = fopen("data.cnf", "r+");
    fprintf(fp, "p cnf %d %d", n * n + (3 * n + 1) * n * (n - 1), line);
    fclose(fp);
    return 0;
}

int zhuan(int elem)
{
    int x = elem / 10, y = elem % y;
    return 6 * x + y;
}