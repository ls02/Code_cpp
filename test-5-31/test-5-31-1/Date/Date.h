#pragma once
#include <iostream>

class Date
{
public:
	Date(int year = 0, int month = 1, int day = 1);
	void Print()const;

	// 获取某年某月的天数
	inline int GetMonthDay(int year, int month);

	// 拷贝构造函数
  // d2(d1)
	Date(const Date& d);

	// 赋值运算符重载
  // d2 = d3 -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d);

	// 析构函数
	//~Date();

	// 日期+=天数
	Date& operator+=(int day);

	// 日期+天数
	Date operator+(int day);

	// 日期-天数
	Date operator-(int day);

	// 日期-=天数
	Date& operator-=(int day);

	// 前置++
	Date& operator++();

	// 后置++
	Date operator++(int);

	// 后置--
	Date operator--(int);

	// 前置--
	Date& operator--();

	// >运算符重载
	bool operator>(const Date& d);

	// ==运算符重载
	bool operator==(const Date& d);

	// >=运算符重载
	inline bool operator >= (const Date& d);

	// <运算符重载
	bool operator < (const Date& d);

	// <=运算符重载
	bool operator <= (const Date& d);

	// !=运算符重载
	bool operator != (const Date& d);

private:
	int _year;
	int _month;
	int _day;
};
