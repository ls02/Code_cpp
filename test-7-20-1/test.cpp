#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;
namespace ls
{
	int a = 10;
	void print()
	{
		printf("print\n");
	}
}
using ls::print;

int add(int a, int b)
{
	return a + b;
}

double add(double a, double b)
{
	return a + b;
}


void test1()
{
	cout << add(1, 1) << endl;
	cout << add(1, 2) << endl;
}

void test2()
{
	cout << add(1, 1) << endl;
	cout << add(1.1, 1.1) << endl;
}

int main()
{

	test2();
	//int a = 100;
	//cout << "print";
	//cin >> a;
	//cout << a;
	////printf("a:%d\n", a);
	////printf("a:%d\n", ls::a);
	////print();
	return 0;
}