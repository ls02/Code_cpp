#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

//����
class Date
{
public:
	//...
	void Printf()
	{
		cout << "5";
	}
protected:
	int _day;
	int _month;
	int _year;
};

//������
class A :public Date
{
public:
	void func()
	{
		_day = 10;
	}
};

void test1()
{
	A a;
	a.func();
	
	
}

int main()
{
	test1();

	return 0;
}