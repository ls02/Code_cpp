#include <iostream>

using namespace std;

class A
{
private:
	char ch;
	int a;
};

//����
class B
{

};

int main()
{
	cout << "A:" << sizeof(A) << endl;
	cout << "B:" << sizeof(B) << endl;

	return 0;
}

//inline int Add(int a, int b)
//{
//	return a + b;
//}
//
//int main()
//{
//	Add
//
//	return 0;
//}

//int main()
//{
//	int a = 10;
//	int& b = a;//���﷨�Ƕ���������b��a�ı���
//
//	int* pa = &a;//���﷨�Ƕ��������Ǵ�����һ��ָ�����ָ����a
//
//	return 0;
//}

//inline int Add(int a, int b)
//{
//	return a + b;
//}
//
//int main()
//{
//	int a = 10;
//	cout << Add(10, 30) << endl;
//	cout << typeid(a).name << endl;
//
//	return 0;
//}

//template <class T1, class T2>
//class Per
//{
//private:
//	T1 _name;
//	T2 _age;
//
//public:
//	Per(T1 name, T2 age)
//	{
//		_name = name;
//		_age = age;
//	}
//};
//
//int main()
//{
//	Per<string, int> p1("str", 12);
//
//	return 0;
//}

//template<class T>
//T Add(T a, T b)
//{
//	return a + b;
//}
//
////double Add(double a, double b)
////{
////	return a + b;
////}
//
//int main()
//{
//	cout << Add(10, 30) << endl;
//	cout << Add(2.3, 5.3) << endl;
//
//	int&& b = 30;
//
//	cout << b << endl;
//
//	return 0;
//}

//int& Add(int a, int b)
//{
//	int c = a + b;
//
//	return c;
//}
//
//int main()
//{
//	int& a = Add(40, 30);
//
//	return 0;
//}

//int main()
//{
//	int a = 10;
//	const double& b = a;//�������õĲ���a�ˣ���Ϊ��������ʽ����ת������b���õ���һ����ʱ��������ֻ���ģ����Ը��лᱨ��
//	
//	a = 400;
//
//	cout << "b:" << b << endl;
//	cout << "a:" << a << endl;
//
//	return 0;
//}