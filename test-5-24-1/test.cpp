#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

class Stack
{
public:
	void Init(int)
	{
		cout << "Init();" << endl;
	}

	void Init(int*)
	{
		cout << "Init(int*);" << endl;
	}


private:
	int* a;
	int size;
};


void Test1()
{
	int a = 10;
	auto b = a;
	int& c = a;
	int* d = 0;
	Stack a1;

	cout << sizeof(b) << endl;

	a1.Init(a);
	a1.Init(c);
	a1.Init(nullptr);

}

struct Tim
{
	int _tim;
};

class Date
{
public:
	void SetDate(int year = 0, int month = 1, int day = 1)
	{
		this->_year = year;
		this->_month = month;
		this->_day = day;
	}

	void Print(int year, int month, int day)
	{
		cout << year << ' ' <<  month << ' ' << day << endl;
	}

	//Date(int year = 1, int month = 1, int day = 1)
	//{
	//	_year = year;
	//	_month = month;
	//	_day = day;
	//}

private:
	int _year;
	int _month;
	int _day;

	Tim _t;
};

void Test2()
{
	Date a1;
	Date a2;
	int year = 2021;
	int month = 3;
	int day = 26;

	a1.SetDate(year, month, day);
	a1.Print(year, month, day);

	a2 = a1;
}

int main()
{
	Test2();

	return 0;
}