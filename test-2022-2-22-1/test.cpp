#include <iostream>

using namespace std;

int main()
{
	int* p1 = new int;//��̬����һ������
	int* p2 = new int(30);//��̬�������Ͳ���ʼ����30
	int* p3 = new int[20];//��̬������������
	int* p4 = new int[5]{ 1, 2, 3, 4, 5 };//��̬����5�����Ͳ���ʼ����1 2 3 4 5��

	delete p1;//�ͷ�һ����̬�ڴ�
	delete p2;
	delete[] p3;//�ͷŶ���ڵ����ʹ��[]�������ֲ���Ԥ֪������
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
//int A::_a = 20;//�Ծ�̬��Ա��ʼ����
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

//class B;//ǰ������
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