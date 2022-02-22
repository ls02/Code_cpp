#include <stdio.h>

void SwapArr(int* arr, int size)
{
	int* left = arr;
	int* right = arr + size;

	while (left < right)
	{
		//是奇数就不需要换
		while (left < right && *left % 2)
		{
			left++;
		}

		//是偶数就不需要换
		while (left < right && !(*right % 2))
		{
			--right;
		}

		int temp = *left;
		*left = *right;
		*right = temp;

		++left;
		--right;
	}
}

void Print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}

	putchar('\n');
}

int main()
{
	int arr[] = { 1, 2, 12, 30, 3, 7, 9 };
	int size = sizeof(arr) / sizeof(arr[0]);

	Print(arr, size);

	SwapArr(arr, size);
	Print(arr, size);

	return 0;
}

//void main(void)
//{
//	printf("hello wordl");
//	return;
//}