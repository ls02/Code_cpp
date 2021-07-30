#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void menu()
{
	printf("***************\n");
	printf("*** 1. Play ***\n");
	printf("*** 0. Exit ***\n");
	printf("***************\n");
}

void game()
{
	system("cls");
	//布雷棋盘
	char mine[ROWS][COLS] = { 0 };

	//扫雷棋盘
	char show[ROWS][COLS] = { 0 };

	initboard(mine, ROWS, COLS, ROW, COL, '0');
	initboard(show, ROWS, COLS, ROW, COL, '*');

	Set_Min(mine, ROW, COL);
	system("cls");
	Disboard(show, ROWS, COLS);
	FindMine(mine, show, ROW, COL);
}

int main()
{
	srand((unsigned)time(NULL));
	int input = 0;

	do
	{
		menu();
		printf("请输入:>");
		scanf("%d", &input);

		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("程序已退出!\n");
			break;
		default:
			printf("请输入有效数字!\n");
			Sleep(1000);
			system("cls");
			break;
		}
	} while (input);

	return 0;
}