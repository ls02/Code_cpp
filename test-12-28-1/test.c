#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int main()
{
	srand((size_t)time(0));
	int arr[10] = { 0 };
	int i = 0;

	for (i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100 + 1;
	}


	while (1)
	{
		system("cls");
		printf("****** 1. �齱 *******\n");
		printf("****** 0. �˳� *******\n");
		printf("������>:");
		
		int val = 0;
		scanf("%d", &val);

		if (!val)
		{
			printf("�������˳�\n");

			break;
		}

		int temp = rand() % 100 + 1;
		int falk = 1;

		for (i = 0; i < 10; i++)
		{
			if (temp == arr[i])
			{
				printf("��ϲ���н��ˣ�\n");
				Sleep(1000);
				falk = 0;
			}
		}

		if (falk)
		{
			printf("���ź���δ�н���\n");
			Sleep(1000);
		}
	}

	return 0;
}