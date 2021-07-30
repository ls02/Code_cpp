#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void initboard(char board[ROWS][COLS], int rows, int cols, int row, int col, char set)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}

void Disboard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;

	printf("----------ɨ����Ϸ-----------\n");

	for (j = 0; j < col - 1; j++)
	{
		printf("%d ", j);
	}
	printf("\n");

	for (i = 1; i < row - 1; i++)
	{
		printf("%d ", i);

		for (j = 1; j < col - 1; j++)
		{
			printf("%c ", board[i][j]);
		}

		printf("\n");
	}

	printf("----------ɨ����Ϸ-----------\n");
}

void Set_Min(char mine[ROWS][COLS], int row, int col)
{
	int count = EASY_COUNT;

	while (count)
	{
		int x = rand() % row + 1;
		int y = rand() % col + 1;

		if (mine[x][y] == '0')
		{
			mine[x][y] = '1';
			count--;
		}
	}
}

//ɨ��
int Get_MineCount(char mine[ROWS][COLS], int x, int y)
{
	int count =
		mine[x][y + 1] +
		mine[x][y - 1] +
		mine[x - 1][y] +
		mine[x - 1][y + 1] +
		mine[x - 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] +
		mine[x + 1][y - 1] -
		8 * '0';

	return count;
}

//ͳ�������ϵ���
static int Get_showMine(char show[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	int count = 0;

	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			if (show[i][j] == '*')
			{
				count++;
			}
		}
	}

	return count;
}

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int win = 0;
	int x = 0;
	int y = 0;

	//�������ϵ��׺����õ������ʱ�˳�
	while (win != EASY_COUNT)
	{
		printf("����������:>");
		scanf("%d%d", &x, &y);
		if (x > 0 && x <= row && y > 0 && y <= col)
		{
			if (mine[x][y] == '1')
			{
				Disboard(mine, ROWS, COLS);
				printf("���ź��㱻ը����!\n");
				printf("���س�����!\n");
				getchar();
				getchar();
				system("cls");

				return;
			}
			else
			{
				//չ����ͳ����Χ�׸���
				NoMine(mine, show, x, y);

				//ͳ����������
				win = Get_showMine(show, row, col);
				system("cls");
			}
		}
		else
		{
			printf("��������Ч����!\n");
			Sleep(1000);
			system("cls");
		}

		Disboard(show, ROWS, COLS);
	}

	//�ж��Ƿ��ų�������
	if (win == EASY_COUNT)
	{
		Disboard(mine, ROWS, COLS);
		printf("��ϲ�����׳ɹ�!\n");
		printf("���س�����!\n");
		getchar();
		getchar();
		system("cls");
	}
}

void NoMine(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
	//ͳ����Χ�׵ĸ���
	int ret = Get_MineCount(mine, x, y);

	//û���׾͵ݹ�չ��
	if (ret == 0)
	{
		show[x][y] = ' ';
		if ((x - 1) > 0 && (y - 1) > 0 && (show[x - 1][y - 1] == '*'))
		{
			NoMine(mine, show, x - 1, y - 1);
		}
		if ((x - 1) > 0 && (y) > 0 && (show[x - 1][y] == '*'))
		{
			NoMine(mine, show, x - 1, y);
		}
		if ((x - 1) > 0 && (y + 1) > 0 && (show[x - 1][y + 1] == '*'))
		{
			NoMine(mine, show, x - 1, y + 1);
		}
		if ((x) > 0 && (y - 1) > 0 && (show[x][y - 1] == '*'))
		{
			NoMine(mine, show, x, y - 1);
		}
		if ((x) > 0 && (y + 1) > 0 && (show[x][y + 1] == '*'))
		{
			NoMine(mine, show, x, y + 1);
		}
		if ((x + 1) > 0 && (y - 1) > 0 && (show[x + 1][y - 1] == '*'))
		{
			NoMine(mine, show, x + 1, y - 1);
		}
		if ((x + 1) > 0 && (y) > 0 && (show[x + 1][y] == '*'))
		{
			NoMine(mine, show, x + 1, y);
		}
		if ((x + 1) > 0 && (y + 1) > 0 && (show[x + 1][y + 1] == '*'))
		{
			NoMine(mine, show, x + 1, y + 1);
		}
	}
	else
	{
		//��ʾ��Χ�׵ĸ���
		show[x][y] = ret + '0';
	}
}