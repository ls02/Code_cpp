#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

void f2()
{
	cout << "f2:" << &f2 << endl;
}

void f1()
{
	cout << "f1:" << &f1 << endl;
	f2();
}

void Test1()
{
	f1();
}

int main()
{
	Test1();

	return 0;
}