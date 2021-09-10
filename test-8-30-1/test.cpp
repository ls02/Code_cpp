#define _CRT_SECURE_NO_WARNINGS 1
//#include <iostream>
//using namespace std;
//
//class Stack
//{
//public:
//	Stack(int capacity = 4)
//	{
//		cout << this << "构造函数" << endl;
//
//		if (capacity <= 0)
//		{
//			_a = nullptr;
//			_size = _capacity = 0;
//		}
//		else
//		{
//			_a = (int*)malloc(sizeof(int) * capacity);
//			if (!_a)
//			{
//				exit(-1);
//			}
//			_capacity = capacity;
//			_size = 0;
//		}
//	}
//
//	~Stack()
//	{
//		cout << this << "析构函数" << endl;
//		free(_a);
//		_a = nullptr;
//		_size = 0;
//		_capacity = 0;
//	}
//
//	inline void Expansion(int size, int capacity)
//	{
//		if (size == capacity)
//		{
//			int* temp = (int*)realloc(_a ,sizeof(int*) * capacity * 2);
//			if (temp)
//			{
//				_a = temp;
//			}
//			_capacity = capacity * 2;
//		}
//	}
//
//	void Push(int val)
//	{
//		Expansion(_size, _capacity);
//		_a[_size] = val;
//		_size++;
//	}
//	
//	void Printf()
//	{
//		int i = 0;
//
//		for (i = 0; i < _size; i++)
//		{
//			cout << _a[i] << endl;
//		}
//	}
//
//private:
//	int* _a;
//	int _size;
//	int _capacity;
//};
//
//int main()
//{
//	Stack s1;
//	s1.Push(1);
//	s1.Push(2);
//	s1.Push(3);
//	s1.Push(4);
//	s1.Push(5);
//
//	Stack s2;
//	s2.Push(1);
//	s2.Push(2);
//	s2.Push(3);
//	s2.Push(4);
//	s2.Push(5);
//
//	return 0;
//}

//#include <iostream>
//
//using namespace std;
//
//class Date
//{
//public:
//	Date(int year = 1, int month = 1, int day = 1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//
//	bool Equel(const Date d)
//	{
//		return  _year == d._year &&
//				_month == d._month &&
//				_day == d._day;
//	}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main()
//{
//	Date d1;
//	Date d2;
//	cout << d1.Equel(d2) << endl;
//
//	return 0;
//}

//#include <iostream>
//
//using namespace std;
//
//class Date
//{
//public:
//	Date(int year = 1, int month = 1, int day = 1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//
//	bool operator==(const Date d)
//	{
//		return _year == d._year &&
//			_month == d._month &&
//			_day == d._day;
//	}
//
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main()
//{
//	Date d1;
//	Date d2;
//
//	cout << (d1 == d2) << endl;
//
//	return 0;
//}

//#include <iostream>
//
//using namespace std;
//
//class Date
//{
//public:
//	Date(int year = 1, int month = 1, int day = 1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//
//	Date(const Date& d)
//	{
//		_year = d._year;
//		_month = d._month;
//		_day = d._day;
//	}
//
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};

//int main()
//{
//	Date d1;
//	Date d2(d1);
//	float a = 10.5f;
//
//	cout << a << endl;
//
//	return 0;
//}

#include <iostream>

using namespace std;

class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	Date& operator=(Date& d)
	{
		if (this != &d)//检查如果不是自己给自己赋值，才需要拷贝
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	}

private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1;
	Date d2(2020, 5, 3);
	Date d3;

	d3 = d1 = d2;

	return 0;
}