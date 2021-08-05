#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

inline void test1()
{
	int a = 10;
	int& x = a;

	cout << &x << endl;
	cout << &a << endl;
}

void test2()
{
	int arr[] = { 1, 2, 3, 4, 5 };

	for (auto& a : arr)
	{
		a += 2;
		cout << a << ' ';
	}
}

void f(int a)
{
	cout << "f(int)" << endl;
}

void f(int* a)
{
	cout << "f(int*)" << endl;
}

void test3()
{
	f(0);
	f(NULL);
	f((int*)NULL);
	f(nullptr);
}

int main()
{
	test3();

	return 0;
}