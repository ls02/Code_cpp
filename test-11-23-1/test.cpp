#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

int main()
{
	int i = 0;
	int a = 100;
	;
	printf("ż����");
	for (i = 0; i < a; i++)
	{
		if (!(i % 2))
		{
			printf("%d ", i);
		}

	}

	printf("\n������");

	for (i = 0; i < a; i++)
	{
		if (i % 2)
		{
			printf("%d ", i);
		}
	}

	return 0;
}