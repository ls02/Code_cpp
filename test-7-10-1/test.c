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
	//��������
	char mine[ROWS][COLS] = { 0 };

	//ɨ������
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
		printf("������:>");
		scanf("%d", &input);

		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("�������˳�!\n");
			break;
		default:
			printf("��������Ч����!\n");
			Sleep(1000);
			system("cls");
			break;
		}
	} while (input);

	return 0;
}