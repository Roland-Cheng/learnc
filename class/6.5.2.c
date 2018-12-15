#include<stdio.h>
#define line 100

char c[2*line];
char d[2*line];
char * s1(const char *a,const char *b);
char * s2(const char *a,const char *b);
int main()
{
    int n;
    char a[line],b[line];
    printf("Please input two string:\n");
    scanf("%[^\n] %[^\n]",a,b);
    char * (*p[2])(const char *,const char *);
    p[0]=&s1,p[1]=&s2;
    printf("Which way do you want to deal with them?\n1.insert\n2.paste\n3.quit\n");
    scanf("%d",&n);
    if(n!=3) printf("%s\n",p[n-1](a,b));
}

char * s1(const char *a,const char *b)
{
    const char *s=a,*t=b;
    char *p=c;
    for(;*s&&*t;s++,t++) *(p++)=*s,*(p++)=*t;
    if (*s) return s2(c,s);
    else return s2(c,t);
}

char * s2(const char *a,const char *b)
{
    const char *s=a,*t=b;
    char *p=d;
    while (*(s)) *(p++)=*(s++);
    for(;*(t);t++,p++) *p=*t;
    return d;
}