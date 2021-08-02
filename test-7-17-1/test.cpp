#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

#define ADD(x,y) ((x) + (y))

using std::cout;
using std::cin;
using std::endl;

int main()
{
	int a = 10;
	int b = 20;

	cout << ADD(a, b) << endl;

	return 0;
}