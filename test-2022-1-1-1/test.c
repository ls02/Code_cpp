#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
	int a = 0;
	short c = 10;
	long e = 0;
	long long d = 20;

	char b = 'a';

	float o = 4.5;
	double p = 5.5;

	printf("a:%d\n", a);
	printf("b:%c\n", b);
	
	printf("o:%f\n", o);
	printf("o:%lf\n", p);

	return 0;
}