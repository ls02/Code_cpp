#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

int main()
{
	int a = 10;
	int& ra = a;
	int* pa = &a;

	return 0;
}

//int add(int a, int b)
//{
//	return a + b;
//}
//
//int main()
//{
//	int a = 10;
//	const double& b = a;
//	a = 50;
//
//	return 0;
//}