#include<stdio.h>
#include<stdlib.h>

typedef struct strings{
    char c;
    struct strings *next;
}strings;

int main()
{
    char x;
    strings *head=NULL,*tail=head,*p=head;
    x=getchar();
    if(x!='#') 
    {
        head=(strings *)malloc(sizeof(strings));
        head->c=x;
        tail=head;
        p=head;
        for(;x=getchar();)
        {
            if(x=='#') break;
            tail->next=(strings *)malloc(sizeof(strings));
            tail=tail->next;
            tail->c=x;
        }
        tail->next=NULL;
        int i;
        for(i=0;p;p=p->next,i++);
        p=head;
        char *p1;
        p1=(char *)malloc((i+1)*sizeof(char));
        for(;p;)
        {
            strings *t=p;
            *p1=p->c;
            p1++;
            putchar(p->c);
            p=p->next;
            free(t);
        }
        *p1='\0';
        p1=p1-i;
        printf("\n\n%s\n",p1);
        free(p1);
    }
    
}