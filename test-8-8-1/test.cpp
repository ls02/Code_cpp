#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

//using namespace std;
using std::cout;
using std::endl;

namespace ls
{
	int a = 20;

	namespace zs
	{
		int add(int a, int b)
		{
			return a + b;
		}

		int a = 50;
	}
}

int main()
{
	cout << ls::a << endl;
	cout << ls::zs::add(20, 40) << endl;
	cout << ls::zs::a << endl;

	return 0;
}

//namespace ls
//{
//	int add(int a, int b)
//	{
//		return a + b;
//	}
//
//	int a = 50;
//
//	namespace zs
//	{
//
//	}
//}

//int main()
//{
//	int a = ls::add(20, 50);
//
//	cout << a << endl;
//	cout << ls::a << endl;
//
//	return 0;
//}
