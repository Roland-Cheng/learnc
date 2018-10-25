#include <stdio.h>
int main()
{
		printf("Fahrenheot-Celsius table\n");
		printf("Fahr Celsius\n");
		float fahr, celsius;
		int lower, upper, step;

		lower = 0;
		upper = 300;
		step = 10;

		celsius = lower;
		while (celsius <= upper) {
				fahr = (9/5)*celsius+32;
				printf("%4.0f  %3.0f\n", fahr, celsius);
				celsius=celsius+step;
		}
}
