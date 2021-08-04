#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

//class Time
//{
//public:
//	Time(int a = 0)
//	{
//		_a = a;
//		cout << "构造函数Time(int a = 0);" << endl;
//	}
//
//
//	~Time()
//	{
//		cout << "析构函数~Date();" << endl;
//	}
//
//	void Print()
//	{
//		cout << _a << endl;
//	}
//
//private:
//	int _a;
//};
//
//class Date
//{
//public:
//	void Print()
//	{
//		cout << _year << _moth << _day << endl;
//		_a.Print();
//	}
//
//
//private:
//	int _year;
//	int _moth;
//	int _day;
//
//	Time _a;
//};
//
//class test1
//{
//public:
//	int a;
//};
//
//struct test2
//{
//	int a;
//};
//
//void Test1()
//{
//	test1 A;
//	A.a = 10;
//}
//
//int main()
//{
//	//Date d2;
//
//	//d2.Print();
//	Test1();
//
//	return 0;
//}

//class test1//空类
//{
//
//};
//
//class test2//成员函数和成员变量构成的类
//{
//public:
//	void Push()
//	{
//		//...
//	}
//
//private:
//	int val;
//};
//
//class test3//成员变量类
//{
//	int val;
//};
//
//int main()
//{
//	cout << "test1:" << sizeof(test1) << endl;
//	cout << "test2:" << sizeof(test2) << endl;
//	cout << "test3:" << sizeof(test3) << endl;
//
//	return 0;
//}

class Date
{
public:
	Date(int year = 1, int moth = 1, int day = 1)
	{
		this->year = year;
		this->moth = moth;
		this->day = day;
	}

	void Print()
	{
		cout << this->year << ' ' << this->moth << ' ' << this->day << endl;
	}

private:
	int year;
	int moth;
	int day;
};

int main()
{
	Date A;

	A.Print();

	return 0;
}