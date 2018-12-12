#include "stdio.h"
char *strcpy(char *s,char *t);
void main(void)
{
    char a[60],b[60]="there is a boat on the lake.";
    printf("%s\n",strcpy(a,b));

}
char *strcpy(char *s,char *t)
{
    int i=0;
    while(*s++=*t++) i++;
    return (s-i-1);
}