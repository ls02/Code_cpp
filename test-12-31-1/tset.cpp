#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

class Date
{
public:
	Date()
	{
		_day = 0;
		_month = 0;
		_year = 0;
	}

	Date(int day = 1, int month = 1, int year = 1)
	{
		this->_day = day;
		this->_month = month;
		this->_year = year;
	}

private:
	int _day;
	int _month;
	int _year;
};

int main()
{
	Date d1(2, 2, 2);


	return 0;
}