#pragma once
#include <stdio.h>
#include <Windows.h>
#include <time.h>

#define ROW 10
#define COL 10

//棋盘初始化
void initboard(char board[ROW][COL], int row, int col);

//显示棋盘
void Disboard(char board[ROW][COL], int row, int col);

//玩家下棋
void Playerchee(char board[ROW][COL], int row, int col);

//电脑下棋
void comupterchee(char board[ROW][COL], int row, int col);

//判断输赢
//玩家赢 -- * 电脑赢 -- # 平局 -- q 继续 -- c
char CheckWin(char board[ROW][COL], int row, int col);