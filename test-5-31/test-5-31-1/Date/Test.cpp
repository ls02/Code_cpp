#define _CRT_SECURE_NO_WARNINGS 1
#include "Date.h"

void Test1()
{
	Date d1(2021, 3, 31);
	Date d2(2021, 3, 31);

	//d2 = d1 - 50;
	printf("d1:");
	d1.Print();
	printf("\nd2:");
	d2.Print();

	int ret = d2 > d1;
	std::cout << ret << std::endl;
}

int main()
{
	Test1();

	return 0;
}