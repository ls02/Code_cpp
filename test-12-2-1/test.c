#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>


int main()
{
	int arr[4] = { 0 };
	int i = 0;
	int j = 0;

	scanf("%d%d%d%d", arr, arr + 1, arr + 2, arr + 3);

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	printf("a:%d b:%d c:%d d:%d", arr[0], arr[1], arr[2], arr[3]);


	//int a = 4;
	//int b = 3;
	//int c = 2;
	//int d = 1;
	//int temp = 0;

	//scanf("%d%d%d", &a, &b, &c);

	//if (a > b)
	//{
	//	temp = a;
	//	a = b;
	//	b = temp;
	//}

	//if (a > c)
	//{
	//	temp = a;
	//	a = c;
	//	c = temp;
	//}

	//if (a > d)
	//{
	//	temp = a;
	//	a = d;
	//	d = temp;
	//}

	//printf("%d%d%d%d", a, b, c, d);

	return 0;
}