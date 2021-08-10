#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>

void menu()
{
	printf("*****************************\n");
	printf("***  1. play   0. exit    ***\n");
	printf("*****************************\n");
}

void game()
{
	int guess = 0;
	int num = rand() % 100 + 1;
	while (1)
	{
		printf("请猜数字:");
		scanf("%d", &guess);

		if (guess > num)
		{
			printf("猜大了!\n");
		}
		else if (guess < num)
		{
			printf("猜小了!\n");
		}
		else
		{
			printf("恭喜你猜对了!\n");
			return;
		}
	}
}

void test1()
{
	
	srand(unsigned int (time(NULL)));
	int input = 0;

	do
	{
		menu();
		printf("请选择:");
		scanf("%d", &input);

		switch (input)
		{
		case 1:
			game();
			Sleep(1000);
			break;
		case 0:
			break;
		default:
			printf("选择错误！\n");
			Sleep(1000);
			break;
		}
		system("cls");

	} while (input);
}

int main()
{
	test1();

	return 0;
}