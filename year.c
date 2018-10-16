#include<stdio.h>
int main()
{
		printf("How many days in a year?\n");
		int year;
		scanf("%d", &year);
		if (year != 366){
				if (year == 365)
						printf("It is not a leap year.\n");
		        else 
						printf("Are you kidding me?\n");
		}
		else{
				printf("It is a leap year.\n");
		}
		return 0;
}
