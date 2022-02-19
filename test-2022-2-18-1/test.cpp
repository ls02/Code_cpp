#include <iostream>

using namespace std;

int main()
{
	int a = 10;
	const int& b = a;

	return 0;
}




//int Add(int x, int y = 40)
//{
//	return x + y;
//}
//
//int main()
//{
//	int a = 50;
//	int& ra = a;
//
//	cout << "ra：" << ra << endl;
//	cout << "a：" << a << endl;
//
//	ra = 100;
//	cout << "ra：" << ra << endl;
//	cout << "a：" << a << endl;
//
//	return 0;
//}

//int main()
//{
//	int x = 100;
//	int y = 30;
//
//	cout << Add(x, y) << endl;//传实参不使用缺省参数
//	cout << Add(x) << endl;//不传实参使用默认值
//
//	return 0;
//}

//int main()
//{
//	int x = 100;
//	int y = 30;
//
//	cout << Add(x, y) << endl;//传实参不使用缺省参数
//	cout << Add() << endl;//不传实参使用默认值
//
//	return 0;
//}

//namespace ls
//{
//	int a = 30;//ls空间域
//}
//
//int a = 100;//全局域
//
//int main()
//{
//	int a = 200;//局部域
//
//	cout << a << endl;//如果不指定空间域那么使用的是局部域，因为局部优先
//	cout << ::a << endl;//指定空域是优先使用全局域
//	cout << ls::a << endl;//指定使用某个空间域
//
//	return 0;
//}