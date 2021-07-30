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

	printf("----------扫雷游戏-----------\n");

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

	printf("----------扫雷游戏-----------\n");
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

//扫雷
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

//统计棋盘上的雷
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

	//当棋盘上的雷和设置的雷相等时退出
	while (win != EASY_COUNT)
	{
		printf("请输入坐标:>");
		scanf("%d%d", &x, &y);
		if (x > 0 && x <= row && y > 0 && y <= col)
		{
			if (mine[x][y] == '1')
			{
				Disboard(mine, ROWS, COLS);
				printf("很遗憾你被炸死了!\n");
				printf("按回车继续!\n");
				getchar();
				getchar();
				system("cls");

				return;
			}
			else
			{
				//展开并统计周围雷个数
				NoMine(mine, show, x, y);

				//统计棋盘雷数
				win = Get_showMine(show, row, col);
				system("cls");
			}
		}
		else
		{
			printf("请输入有效坐标!\n");
			Sleep(1000);
			system("cls");
		}

		Disboard(show, ROWS, COLS);
	}

	//判断是否排出所有雷
	if (win == EASY_COUNT)
	{
		Disboard(mine, ROWS, COLS);
		printf("恭喜你排雷成功!\n");
		printf("按回车继续!\n");
		getchar();
		getchar();
		system("cls");
	}
}

void NoMine(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
	//统计周围雷的个数
	int ret = Get_MineCount(mine, x, y);

	//没有雷就递归展开
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
		//显示周围雷的个数
		show[x][y] = ret + '0';
	}
}