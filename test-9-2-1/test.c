#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

int qizi[16][16] = { 0 };

int IsWin(int x, int y, int chess)
{
	int i, j;
	for (i = x + 4, j = y; i >= 4; i--)
	{
		if (qizi[i][j] == chess && qizi[i - 1][j] == chess && qizi[i - 2][j] == chess && qizi[i - 3][j] == chess && qizi[i - 4][j] == chess)
		{
			return chess;
		}
	}
	for (i = x, j = y + 4; j >= 4; j--)
	{
		if (qizi[i][j] == chess && qizi[i][j - 1] == chess && qizi[i][j - 2] == chess && qizi[i][j - 3] == chess && qizi[i][j - 4] == chess)
		{
			return chess;
		}
	}
	for (i = x + 4, j = y + 4; i >= 4, j >= 4; i--, j--)
	{
		if (qizi[i][j] == chess && qizi[i - 1][j - 1] == chess && qizi[i - 2][j - 2] == chess && qizi[i - 3][j - 3] == chess && qizi[i - 4][j - 4] == chess)
		{
			return chess;
		}
	}
	for (i = x + 4, j = y - 4; i >= 4 && j <= 10; i--, j++)
	{
		if (qizi[i][j] == chess && qizi[i - 1][j + 1] == chess && qizi[i - 2][j + 2] == chess && qizi[i - 3][j + 3] == chess && qizi[i - 4][j + 4] == chess)
		{
			return chess;
		}
	}
	return 0;
}

void game()
{
	initgraph(600, 600, SHOWCONSOLE);

	fillrectangle(20, 20, 580, 580);

	setlinecolor(BLACK);
	setlinestyle(0, 2);

	for (int i = 50; i <= 550; i += 50)
	{
		line(50, i, 550, i);
		line(i, 50, i, 550);
	}

	int gg = 0;


	while (1)
	{
		MOUSEMSG msg = GetMouseMsg();
		if (msg.x > 25 && msg.x < 575 && msg.y>25 && msg.y < 575)
		{
			if (msg.uMsg == WM_LBUTTONDOWN && gg % 2 == 0)
			{
				int x = (msg.x + 25) / 50 * 50;
				int y = (msg.y + 25) / 50 * 50;
				if (qizi[x / 50 - 1][y / 50 - 1])
					continue;
				setfillcolor(BLACK);
				fillcircle(x, y, 25);
				qizi[x / 50 - 1][y / 50 - 1] = 1;
				system("cls");
				for (int i = 0; i < 16; i++)
				{
					for (int j = 0; j < 16; j++)
					{
						printf("%d ", qizi[i][j]);
					}
					putchar('\n');
				}
				if (1 == IsWin(x / 50 - 1, y / 50 - 1, 1))
				{
					MessageBox(GetForegroundWindow(), "ºÚÆåÊ¤Àû!", "ÓÎÏ·½áÊø", MB_OK);
					return;
				}
				gg++;
			}
			if (msg.uMsg == WM_LBUTTONDOWN && gg % 2 == 1)
			{
				int x = (msg.x + 25) / 50 * 50;
				int y = (msg.y + 25) / 50 * 50;
				if (qizi[x / 50 - 1][y / 50 - 1])
					continue;
				setfillcolor(WHITE);
				fillcircle(x, y, 25);
				system("cls");
				qizi[x / 50 - 1][y / 50 - 1] = 2;
				for (int i = 0; i < 16; i++)
				{
					for (int j = 0; j < 16; j++)
					{
						printf("%d ", qizi[i][j]);
					}
					putchar('\n');
				}
				if (2 == IsWin(x / 50 - 1, y / 50 - 1, 2))
				{
					MessageBox(GetForegroundWindow(), "°×ÆåÊ¤Àû!", "ÓÎÏ·½áÊø", MB_OK);
					return;
				}
				gg++;
			}
		}
	}
	closegraph();
}
int main()
{
	game();

	return 0;
}