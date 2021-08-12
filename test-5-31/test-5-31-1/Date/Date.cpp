#define _CRT_SECURE_NO_WARNINGS 1
#include "Date.h"

//构造函数
Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
}

//构造拷贝函数
Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

//打印函数
void Date::Print()const
{
	printf("%d年%d月%d日\n", _year, _month, _day);
}



// 获取某年某月的天数
inline int Date::GetMonthDay(int year, int month)
{
	static int days[13] = { 0 , 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	if (month == 2 && (((year % 400 == 0) && (year % 100 != 0)) || year % 4 == 0))
	{
		days[month] = 29;
	}

	return days[month];
}

//+=天数
Date& Date::operator += (int day)
{
	_day += day;

	//判断天数是否合法，如果不合法就进行调整
	while (_day > GetMonthDay(_year, _month))
	{
		//刷新天数
		_day -= GetMonthDay(_year, _month);
		_month++;

		//如果月也不合法也进行调整
		if (_month >= 12)
		{
			_year++;
			_month = 1;
		}
	}

	return *this;
}

// 日期+天数
Date Date::operator + (int day)
{
	Date ret(*this);
	ret += day;

	return ret;
}

// 日期-=天数
Date& Date::operator -= (int day)
{
	//如果day是负数，那么就相当于加，我们直接调用重载后的+=接口，同时传值的时候给负数。
	if (day <= 0)
	{
		return *this += -day;
	}

	//先减掉day日期
	_day -= day;

	//如果_day是负数，那么这不是一个合法日期，我们要稍作处理
	while (_day <= 0)
	{
		//小于0说明要减掉这个月，用上个月来和_day相加
		_month--;
		//如果month等于0我们就减年
		if (_month <= 0)
		{
			_month = 12;
			_year--;

			//如果年小于0，说明需要调整，没有负数年这个东西
			if (_year < 0)
			{
				_year = 0;
				_month = 0;
				_day = 0;

				return *this;
			}
		}

		//获取上个月的天数，来和_day相加，因为_day是小于或等于0的数，如果小于或等于那么就进不来
		_day += GetMonthDay(_year, _month);

	}

	return *this;
}

Date Date::operator - (int day)
{
	Date ret(*this);

	ret -= day;

	return ret;
}

//深度拷贝日期类
Date& Date::operator = (const Date& d)
{
	if (this != &d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	return *this;
}

// 前置++
Date& Date::operator ++ ()
{
	*this += 1;

	return *this;
}

//后置++
Date Date::operator ++ (int)
{
	Date ret(*this);
	ret += 1;

	return ret;
}

//前置--
Date& Date::operator -- ()
{
	*this -= 1;

	return *this;
}

//后置--
Date Date::operator--(int)
{
	Date ret(*this);

	ret -= 1;

	return ret;
}

//比较日期类大小
bool Date::operator > (const Date & d)
{
	return _year > d._year ||
		_month > d._month ||
		_day > d._day;
}

bool Date::operator < (const Date& d)
{
	return _year < d._year ||
		_month < d._month ||
		_day < d._day;
}

bool Date::operator == (const Date& d)
{
	return _year == d._year ||
		_month == d._month ||
		_day == d._day;
}

bool Date::operator != (const Date& d)
{
	return !(*this == d);
}

inline bool Date::operator >= (const Date& d)
{
	return *this > d || *this == d;
}

inline bool Date::operator <= (const Date& d)
{
	return *this < d || *this == d;
}