#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

int main()
{
	int i = 0;
	int a = 100;
	;
	printf("Å¼Êý£º");
	for (i = 0; i < a; i++)
	{
		if (!(i % 2))
		{
			printf("%d ", i);
		}

	}

	printf("\nÆæÊý£º");

	for (i = 0; i < a; i++)
	{
		if (i % 2)
		{
			printf("%d ", i);
		}
	}

	return 0;
}