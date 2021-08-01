#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void initboard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			//二维数组初始化为空字符
			board[i][j] = ' ';
		}
	}
}

void Disboard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;

	for (j = 1; j <= col; j++)
	{
		printf(" %d  ", j);
	}
	printf("\n");

	for (i = 0; i < row; i++)
	{

		for (j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);

			if (j < col - 1)
			{
				printf("|");
			}
		}

		printf(" %d", i + 1);

		printf("\n");

		if (i < row - 1)
		{
			for (j = 0; j < col; j++)
			{
				printf("---");

				if (j < row - 1)
				{
					printf("|");
				}
			}

			printf("\n");
		}


	}
}

void Playerchee(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;

	while (1)
	{
		printf("玩家下棋:\n");
		printf("请输入坐标:>");
		scanf("%d%d", &x, &y);

		if (x > 0 && x <= ROW && y > 0 && y <= COL)
		{
			if (board[x - 1][y - 1] == ' ')
			{
				board[x - 1][y - 1] = '*';
				break;
			}
			else
			{
				printf("坐标已被占用!\n");
			}
		}
		else
		{
			printf("请输入有效坐标!\n");
		}
	}
}

void comupterchee(char board[ROW][COL], int row, int col)
{
	int x = 0;
	int y = 0;

	while (1)
	{
		x = rand() % row;
		y = rand() % row;
		
		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			break;
		}
	}
}

static char is_Full(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
			{
				return 0;
			}
		}
	}

	return 1;
}

char CheckWin(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3] && board[i][j] == board[i][j + 4] && board[i][j] != ' ')
			{
				return board[i][j];
			}
			else if (board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j] && board[i][j] == board[i + 4][j] && board[i][j] != ' ')
			{
				return board[i][j];
			}
			else if (board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] && board[i][j] == board[i + 3][j + 3] && board[i][j] == board[i + 4][j + 4] && board[i][j] != ' ')
			{
				return board[i][j];
			}
			else if (board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2] && board[i][j] == board[i + 3][j - 3] && board[i][j] == board[i + 4][j - 4] && board[i][j] != ' ')
			{
				return board[i][j];
			}
		}
	}

	if (is_Full(board, row, col))
	{
		return 'q';
	}

	return 'c';
}
