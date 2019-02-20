#include<stdio.h>

struct bits{
    unsigned int bit0:1,bit1:1,bit2:1,bit3:1,bit4:1,bit5:1,bit6:1,bit7:1,rsv:8;
}c;
union lianhe{
    unsigned short x;
    struct bits a;
}m;
void isr0(void)
{
	printf("The Interrupt Service Routine isr0 is called!\n");
}
void isr1(void)
{
	printf("The Interrupt Service Routine isr1 is called!\n");
}
void isr2(void)
{
	printf("The Interrupt Service Routine isr2 is called!\n");
}
void isr3(void)
{
	printf("The Interrupt Service Routine isr3 is called!\n");
}
void isr4(void)
{
	printf("The Interrupt Service Routine isr4 is called!\n");
}
void isr5(void)
{
	printf("The Interrupt Service Routine isr5 is called!\n");
}
void isr6(void)
{
	printf("The Interrupt Service Routine isr6 is called!\n");
}
void isr7(void)
{
	printf("The Interrupt Service Routine isr7 is called!\n");
}

int main()
{
    int i,n;
    void (*p_isr[8])(void);
    p_isr[0]=*isr0;
    p_isr[1]=*isr1;
    p_isr[2]=*isr2;
    p_isr[3]=*isr3;
    p_isr[4]=*isr4;
    p_isr[5]=*isr5;
    p_isr[6]=*isr6;
    p_isr[7]=*isr7;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
    scanf("%hu",&(m.x));
    printf("%hu:\n",m.x);
    if (m.a.bit0) p_isr[0]();
    if (m.a.bit1) p_isr[1]();
    if (m.a.bit2) p_isr[2]();
    if (m.a.bit3) p_isr[3]();
    if (m.a.bit4) p_isr[4]();
    if (m.a.bit5) p_isr[5]();
    if (m.a.bit6) p_isr[6]();
    if (m.a.bit7) p_isr[7]();
    printf("\n");
    }
}