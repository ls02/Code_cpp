#define _CRT_SECURE_NO_WARNINGS 1
#include "Date.h"

//���캯��
Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
}

//���쿽������
Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

//��ӡ����
void Date::Print()const
{
	printf("%d��%d��%d��\n", _year, _month, _day);
}



// ��ȡĳ��ĳ�µ�����
inline int Date::GetMonthDay(int year, int month)
{
	static int days[13] = { 0 , 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	if (month == 2 && (((year % 400 == 0) && (year % 100 != 0)) || year % 4 == 0))
	{
		days[month] = 29;
	}

	return days[month];
}

//+=����
Date& Date::operator += (int day)
{
	_day += day;

	//�ж������Ƿ�Ϸ���������Ϸ��ͽ��е���
	while (_day > GetMonthDay(_year, _month))
	{
		//ˢ������
		_day -= GetMonthDay(_year, _month);
		_month++;

		//�����Ҳ���Ϸ�Ҳ���е���
		if (_month >= 12)
		{
			_year++;
			_month = 1;
		}
	}

	return *this;
}

// ����+����
Date Date::operator + (int day)
{
	Date ret(*this);
	ret += day;

	return ret;
}

// ����-=����
Date& Date::operator -= (int day)
{
	//���day�Ǹ�������ô���൱�ڼӣ�����ֱ�ӵ������غ��+=�ӿڣ�ͬʱ��ֵ��ʱ���������
	if (day <= 0)
	{
		return *this += -day;
	}

	//�ȼ���day����
	_day -= day;

	//���_day�Ǹ�������ô�ⲻ��һ���Ϸ����ڣ�����Ҫ��������
	while (_day <= 0)
	{
		//С��0˵��Ҫ��������£����ϸ�������_day���
		_month--;
		//���month����0���Ǿͼ���
		if (_month <= 0)
		{
			_month = 12;
			_year--;

			//�����С��0��˵����Ҫ������û�и������������
			if (_year < 0)
			{
				_year = 0;
				_month = 0;
				_day = 0;

				return *this;
			}
		}

		//��ȡ�ϸ��µ�����������_day��ӣ���Ϊ_day��С�ڻ����0���������С�ڻ������ô�ͽ�����
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

//��ȿ���������
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

// ǰ��++
Date& Date::operator ++ ()
{
	*this += 1;

	return *this;
}

//����++
Date Date::operator ++ (int)
{
	Date ret(*this);
	ret += 1;

	return ret;
}

//ǰ��--
Date& Date::operator -- ()
{
	*this -= 1;

	return *this;
}

//����--
Date Date::operator--(int)
{
	Date ret(*this);

	ret -= 1;

	return ret;
}

//�Ƚ��������С
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