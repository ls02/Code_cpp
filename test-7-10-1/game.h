#pragma once
#include <stdio.h>
#include <Windows.h>
#include <time.h>

#define ROW 9
#define COL 9
#define ROWS ROW + 2
#define COLS COL + 2
#define EASY_COUNT 10
//��ʼ������
void initboard(char board[ROWS][COLS],int rows, int cols, int row, int col, char set);

//��ʾ����
void Disboard(char board[ROWS][COLS], int row, int col);

//������
void Set_Min(char mine[ROWS][COLS], int row, int col);

//����
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);

//չ��û���׵�λ��
void NoMine(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y);

//ͳ�������ϵ���
int Get_showMine(char show[ROWS][COLS], int row, int col);