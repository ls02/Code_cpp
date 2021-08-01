#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void menu()
{
	printf("******************\n");
	printf("***  1. Play   ***\n");
	printf("***  0. Exit   ***\n");
	printf("******************\n");
}

void game()
{
	char ret = 0;
	char board[ROW][COL] = { 0 };
	initboard(board, ROW, COL);

	while (1)
	{
		Disboard(board, ROW, COL);
		Playerchee(board, ROW, COL);
		ret = CheckWin(board, ROW, COL);
		if (ret != 'c')
		{
			break;
		}
		comupterchee(board, ROW, COL);
		ret = CheckWin(board, ROW, COL);
		if (ret != 'c')
		{
			break;
		}
		system("cls");
	}

	system("cls");

	if (ret == 'q')
	{
		printf("平局!\n");
	}
	else if (ret == '*')
	{
		printf("玩家赢!\n");
	}
	else if (ret == '#')
	{
		printf("电脑赢！\n");
	}

	Disboard(board, ROW, COL);
	printf("按回车键继续!\n");
	getchar();
	getchar();

}

int main()
{
	int input = 0;
	srand((unsigned)time(NULL));

	do
	{
		system("cls");
		menu();
		printf("请输入:>");
		scanf("%d", &input);

		switch (input)
		{
		case 1:
			system("cls");
			game();
			break;
		case 0:
			printf("程序已退出!\n");
			break;
		default:
			printf("输入错误,请输入有效数字!\n");
			Sleep(1000);
			system("cls");
			break;
		}
	} while (input);

	return 0;
}