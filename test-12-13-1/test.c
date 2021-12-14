#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <windows.h>

int main()
{
	int i = 10;

	while (i > 0)
	{
		printf("%-2d\r", i);
		Sleep(1000);
		i--;
	}

	return 0;
}