#define _CRT_SECURE_NO_WARNINGS 1
#include "RBTree.h"
#include <time.h>

void TestRBTree1()
{
	RBTree<int, int> t1;
	int n = 500000;
	//int a[] = { 1, 40, 2 };
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };

	srand((size_t)time(0));

	for (int i = 0; i < n; i++)
	{
		int e = rand();

		t1.Insert(make_pair(e, e));
	}

	//for (auto e : a)
	//{
	//	t1.Insert(make_pair(e, e));
	//	cout << e << endl;
	//}

	t1.InOrder();

	cout << t1.CheckBlance();
}

void TestRBTree2()
{
	RBTree<int, int> t1;
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };

	for (auto e : a)
	{
		t1.Insert(make_pair(e, e));
	}

	RBTree<int, int> t2;
	t2 = t1;
	t2[1] *= 100;

	t2.InOrder();

	cout << t2.Find(4)->_kv.first;

}

int main()
{
	//TestRBTree1();
	TestRBTree2();

	return 0;
}