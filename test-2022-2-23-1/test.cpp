#include <iostream>

class A
{
	static int a;
};

static A::int a = 10;

//template <class T>
//class A
//{
//public:
//	A()
//		:
//	{}
//private:
//
//	T _a;
//	T _b;
//	static int b;
//};
//
//static int A::b = 0;
//
//int main()
//{
//	A<int> a;
//	A<double> b;
//}

//template<class T>
//void Swap(T& left, T& right)
//{
//	T temp = left;
//	left = right;
//	right = temp;
//}
//
//int main()
//{
//	int a = 10;
//	int b = 20;
//
//	Swap(a, b);//隐式实列化
//	Swap<int>(a, b);//显示实列化
//
//	return 0;
//}

//class A
//{
//public:
//	A(int a = 0)
//		:_a(a)
//	{}
//
//private:
//	int _a;
//};
//
//int main()
//{
//	A* p1 = (A*)malloc(sizeof(A));
//	A* p2 = (A*)malloc(sizeof(A));
//
//	//定位new
//	new(p1) A;//调用A的构造函数给p1的指向初始化
//	new(p2) A(20);//调用A的构造函数给p1的指向初始化成指定值
//
//	return 0;
//}

//int main()
//{
//	int* p1 = new int(1);
//	int* p2 = (int*)operator new(sizeof(int));
//
//	return 0;
//}