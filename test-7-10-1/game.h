#pragma once
#include <stdio.h>
#include <Windows.h>
#include <time.h>

#define ROW 9
#define COL 9
#define ROWS ROW + 2
#define COLS COL + 2
#define EASY_COUNT 10
//初始化棋盘
void initboard(char board[ROWS][COLS],int rows, int cols, int row, int col, char set);

//显示棋盘
void Disboard(char board[ROWS][COLS], int row, int col);

//布置雷
void Set_Min(char mine[ROWS][COLS], int row, int col);

//排雷
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);

//展开没有雷的位置
void NoMine(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y);

//统计棋盘上的雷
int Get_showMine(char show[ROWS][COLS], int row, int col);