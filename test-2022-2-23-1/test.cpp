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
//	Swap(a, b);//��ʽʵ�л�
//	Swap<int>(a, b);//��ʾʵ�л�
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
//	//��λnew
//	new(p1) A;//����A�Ĺ��캯����p1��ָ���ʼ��
//	new(p2) A(20);//����A�Ĺ��캯����p1��ָ���ʼ����ָ��ֵ
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