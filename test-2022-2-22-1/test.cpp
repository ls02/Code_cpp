#include <iostream>

using namespace std;

int main()
{
	int* p1 = new int;//动态申请一个整形
	int* p2 = new int(30);//动态申请整型并初始化成30
	int* p3 = new int[20];//动态申请多个个整型
	int* p4 = new int[5]{ 1, 2, 3, 4, 5 };//动态申请5个整型并初始化成1 2 3 4 5；

	delete p1;//释放一个动态内存
	delete p2;
	delete[] p3;//释放多个节点必须使用[]否则会出现不可预知的问题
	delete[] p4;

	return 0;
}

//class A
//{
//public:
//	void Print(void)
//	{
//		cout << _a << endl << _b << endl;
//	}
//private:
//	int _a = 20;
//	int _b = 30;
//};
//
//class B
//{
//public:
//	//B(int a = 3)
//	//{
//	//	_a = a;
//	//}
//
//private:
//	int _a;
//};
//
//int main()
//{
//	A a1;
//
//	a1.Print();
//
//	return 0;
//}

//class A
//{
//public:
//	static int _a;
//};
//
//int A::_a = 20;//对静态成员初始化，
//
//int main()
//{
//	A a1;
//	A a2;
//
//	cout << a1._a << endl;
//	cout << a2._a << endl;
//
//	a1._a++;
//
//	cout << a1._a << endl;
//	cout << a2._a << endl;
//
//	return 0;
//}

//class A
//{
//public:
//	A(int a)
//	{
//		_a = a;
//	}
//
//	int GetA(void)
//	{
//		return _a;
//	}
//private:
//	int _a;
//};
//
//
//class Date
//{
//public:
//	Date(int day, int& ra)
//		:_day(day)
//		,_A(20)
//		,_ra(ra)
//	{
//
//	}
//
//	void Print(void)
//	{
//		printf("_day:%d\n_A:%d\n_ra:%d\n", _day, _A.GetA(), _ra);
//	}
//private:
//	const int _day;
//	A _A;
//	int& _ra;
//};
//
//
//int main()
//{
//	int b = 50;
//	Date d1(1000, b);
//
//	Date(19, b).Print();
//
//	d1.Print();
//
//	return 0;
//}

//class B;//前置声明
//class A
//{
//	friend class B;
//public:
//	A(int a = 5)
//	{
//		_a = a;
//	}
//
//	void PrintA(void)
//	{
//		cout << "A" << endl;
//	}
//
//private:
//	int _a;
//};
//
//class B
//{
//public:
//	B(int b = 10)
//	{
//		_b = b;
//	}
//
//	void PrintB(void)
//	{
//		
//		cout << "B:" << _b << "\t_A:" << _A._a << endl;
//		_A.PrintA();
//	}
//
//private:
//	int _b;
//	A _A;
//};
//
//int main()
//{
//	A a;
//	B b;
//
//	b.PrintB();
//
//	return 0;
//}