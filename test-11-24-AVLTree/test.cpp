#define _CRT_SECURE_NO_WARNINGS 1
#include "AVLTree.h"

void TestAVLTree1()
{
	//int a[] = { 1, 3, 5, 7, 6 };
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };

	AVLTree<int, int> t;

	for (auto e : a)
	{
		t.Insert(make_pair(e, e));
	}

	t.InOrder();

	cout << t.IsAVLTree() << endl;

	cout << t.Find(3)->_kv.first << endl;

	t[7] *= 40;

	t.InOrder();

	cout << "----------------------------------" << endl;

	AVLTree<int, int> t1(t);

	t1.InOrder();
}

void TestAVLTree2()
{
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int a[] = { 16, 3, 7};
	AVLTree<int, int> t1;

	for (auto e : a)
	{
		t1.Insert(make_pair(e, e));
	}

	AVLTree<int, int> t2;
	t2 = t1;

	t2.InOrder();
}

int main()
{
	//TestAVLTree1();
	TestAVLTree2();

	return 0;
}