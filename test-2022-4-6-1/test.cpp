#include <iostream>

//template<class T, class P>
//class A
//{
//
//public:
//	A(void)
//	{
//		std::cout << "δ�ػ�" << std::endl;
//	}
//
//	T a;
//	P b;
//};
//
////ȫ�ػ�
//template<>
//class A<int, int>
//{
//public:
//	A(void)
//	{
//		std::cout << "ȫ�ػ�" << std::endl;
//	}
//
//	int a;
//	int b;
//};
//
////ƫ�ػ�
//template<class T>
//class A<T, int>
//{
//public:
//	A(void)
//	{
//		std::cout << "ƫ�ػ�" << std::endl;
//	}
//
//	T a;
//	int b;
//};
//
//
//int main(void)
//{
//	A<int, int> a;
//	A<double, double> b;
//	A<double, int> c;
//
//	return 0;
//}

template<class T>
bool Equal(const T left, const T right)
{
	std::cout << "δ�ػ�" << std::endl;

	return left == right;
}

//�ػ�
template<>
bool Equal<const char*>(const char* left, const char* right)
{
	std::cout << "�ػ�" << std::endl;

	return strcmp(left, right) == 0;
}


int main(void)
{
	char str1[] = "hello";
	char str2[] = "hello";

	const char* p1 = "hello";
	const char* p2 = "hello";

	std::cout << Equal(1, 3) << std::endl;
	std::cout << Equal(1.1, 1.1) << std::endl;
	std::cout << Equal("nihao", "nihao") << std::endl;
	std::cout << Equal(str1, str2) << std::endl;
	std::cout << Equal(p1, p2) << std::endl;

	return 0;
}