#include <iostream>

using namespace std;

class Data
{
private:
	int year;
	int month;
	int day;

public:
	Data(int year, int month, int day)//这里看起来只有三个参数实际上有四个，还有一个是this指针不过被隐含了
	{
		this->year = year;
		this->month = month;
		this->day = day;
	}
};

int main()
{
	Data d1(2020, 2, 4);

	return 0;
}

//int main()
//{
//	int a = 0;
//	int b = 0;
//	int c = 0;
//	int d = 0;
//	int max = 0;
//
//	cin >> a >> b >> c >> d;
//	max = a;
//
//	(((((max > b) ? (max) : (max = b)) > c) ? (max) : (max = c)) > d) ? (max) : (max = d);
//	cout << max << endl;
//
//	return 0;
//}