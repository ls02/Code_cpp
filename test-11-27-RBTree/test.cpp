#define _CRT_SECURE_NO_WARNINGS 1
#include "Map.h"
#include "RBTree.h"
#include "Set.h"

struct T
{
	int operator()(const int k)
	{
		return k;
	}
};

void Test1()
{
	int a = 30;
	int b = 20;
	T c;

	if (c(a) > c(b))
	{
		cout << a << endl;
	}
	else
	{
		cout << b << endl;
	}
}

int main()
{
	//Test1();

	return 0;
}