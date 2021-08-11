#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <Windows.h>

void test1()
{
	char arr1[] = "Hello world!";
	char arr2[] = "############";
	int left = 0;
	int right = sizeof(arr1) - 2;

	while (left <= right)
	{
		arr2[left] = arr1[left];
		arr2[right] = arr1[right];
		left++;
		right--;
		printf("%s\n", arr2);
		Sleep(1000);
		system("cls");
	}

	printf("%s\n", arr2);
}

int main()
{
	test1();

	return 0;
}