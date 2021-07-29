#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <math.h>

int is_prime(int x)
{
	int i = 0;

	for (i = 2; i <= sqrt(x); i++)
	{
		if (!(x % i))
		{
			return 0;
		}
	}

	return 1;
}

void test1()
{
	int i = 0;
	int cout = 0;

	for (i = 2; i <= 50; i++)
	{
		if (is_prime(i))
		{
			double ret = sqrt(i);
			printf("i:%d ret:%f\n", i, ret);
			cout++;
		}
	}

	printf("\ncout:%d", cout);
}

int binary_search(int* arr, int k, int sz)
{
	int left = 0;
	int right = sz - 1;

	while (left <= right)
	{
		//取中间值
		int mid = (right - left) / 2 + left;

		if (arr[mid] > k)
		{
			right = mid - 1;
		}
		else if (arr[mid] < k)
		{
			left = mid + 1;
		}
		else
		{
			return mid;
		}
	}

	return -1;
}

void test2()
{
	int arr[] = { 1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9, 10 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	int k = 4;

	int ret = binary_search(arr, k, sz);

	printf("%d", arr[ret]);
}

void Print(int n)
{
	printf("%d ", n % 10);
	if (n > 9)
	{
		Print(n / 10);
	}
}
void test3()
{
	int num = 0;

	scanf("%d", &num);
	Print(num);
}

int main()
{
	test3();

	return 0;
}