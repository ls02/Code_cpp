#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

class Date
{
public:
	//���캯���޲�
	Date()
	{

	}

	//���ι��캯��
	Date(int year, int moth, int day)
	{
		_year = year;
		_moth = moth;
		_day = day;
	}
	
	int operator+(const Date& d)//���������
	{
		_day += d._day;

		return _day;
	}

	Date& operator=(const Date&d)
	{
		//������ж��Ƿ�ֹ�Լ����Լ���ֵ
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
	//�����޲ι��캯��
	Date d1;//ע�⣺�����޲ι��캯�����ܴ����ţ���Ȼ����������Ϊ�Ǻ�������

	//���ô��ι��캯��
	Date d2(2021, 7, 2);
	int a = d1 + d2;//������d1+d2ʵ���ϱ����������ת��Ϊ int operator+(d1, d2);

	d1 = d2;//�����d1��d2��������һ�������һ�����ᱻ�������滻��

	return 0;
}