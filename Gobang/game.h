#pragma once
#include <stdio.h>
#include <Windows.h>
#include <time.h>

#define ROW 10
#define COL 10

//���̳�ʼ��
void initboard(char board[ROW][COL], int row, int col);

//��ʾ����
void Disboard(char board[ROW][COL], int row, int col);

//�������
void Playerchee(char board[ROW][COL], int row, int col);

//��������
void comupterchee(char board[ROW][COL], int row, int col);

//�ж���Ӯ
//���Ӯ -- * ����Ӯ -- # ƽ�� -- q ���� -- c
char CheckWin(char board[ROW][COL], int row, int col);