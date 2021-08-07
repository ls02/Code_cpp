#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

class Date
{
public:
	//构造函数无参
	Date()
	{

	}

	//带参构造函数
	Date(int year, int moth, int day)
	{
		_year = year;
		_moth = moth;
		_day = day;
	}
	
	int operator+(const Date& d)//运算符重载
	{
		_day += d._day;

		return _day;
	}

	Date& operator=(const Date&d)
	{
		//这里的判断是防止自己给自己赋值
		if (this != &d)
		{
			_year = d._year;
			_moth = d._moth;
			_day = d._day;
		}
	}


private:
	int _year;
	int _moth;
	int _day;
};

int main()
{
	//调用无参构造函数
	Date d1;//注意：调用无参构造函数不能带括号，不然编译器会认为是函数声明

	//调用带参构造函数
	Date d2(2021, 7, 2);
	int a = d1 + d2;//看着是d1+d2实际上编译器会把它转换为 int operator+(d1, d2);

	d1 = d2;//这里的d1、d2和上面那一条的情况一样都会被编译器替换。

	return 0;
}