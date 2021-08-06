#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

//inline int add(int& a, int& b)
//{
//
//	return a + b;
//}

int add(int a, int b)
{
	return a + b;
}

void Test1()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	int i = 0;

	for (auto& i : arr)
	{
		i *= 2;
	}

	for (auto i : arr)
	{
		cout << i << ' ';
	}
}

class Time
{
public:
	Time()
	{
		cout << "Time();" << endl;

		_hour = 0;
		_minute = 0;
		_second = 0;
	}
private:
	int _hour;
	int _minute;
	int _second;
};

class Date
{
private:
	int _year;
	int _month;
	int _day;

	Time _t;
};

void Test2()
{
	//int a = 10;
	//int b = 20;

	//add(a, b);

	Date a2;
}


int main()
{
	Test2();

	return 0;
}