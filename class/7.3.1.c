#include<stdio.h>

struct bits{
    unsigned char bit0:1,bit1:1,bit2:1,bit3:1,bit4:1,bit5:1,bit6:1,bit7:1;
}c;
union lianhe{
    unsigned char x;
    struct bits a;
}m;
void f0(struct bits b)
{
	printf("the function 0 is called!\n");
}
void f1(struct bits b)
{
	printf("the function 1 is called!\n");
}
void f2(struct bits b)
{
	printf("the function 2 is called!\n");
}
void f3(struct bits b)
{
	printf("the function 3 is called!\n");
}
void f4(struct bits b)
{
	printf("the function 4 is called!\n");
}
void f5(struct bits b)
{
	printf("the function 5 is called!\n");
}
void f6(struct bits b)
{
	printf("the function 6 is called!\n");
}
void f7(struct bits b)
{
	printf("the function 7 is called!\n");
}

int main()
{
    printf("Please input a character:\n");
    m.x=getchar();
    void (*p_fun[8])(struct bits b);
    int i;
    p_fun[0]=*f0;
    p_fun[1]=*f1;
    p_fun[2]=*f2;
    p_fun[3]=*f3;
    p_fun[4]=*f4;
    p_fun[5]=*f5;
    p_fun[6]=*f6;
    p_fun[7]=*f7;
    if (m.a.bit0) p_fun[0](m.a);
    if (m.a.bit1) p_fun[1](m.a);
    if (m.a.bit2) p_fun[2](m.a);
    if (m.a.bit3) p_fun[3](m.a);
    if (m.a.bit4) p_fun[4](m.a);
    if (m.a.bit5) p_fun[5](m.a);
    if (m.a.bit6) p_fun[6](m.a);
    if (m.a.bit7) p_fun[7](m.a);
}