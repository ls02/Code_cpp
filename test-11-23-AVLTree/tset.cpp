#define _CRT_SECURE_NO_WARNINGS 1
#include "AVLTree.h"

void TestAVLTree1()
{
	//int a[] = { 1, 3, 5, 7, 6 };
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };

	AVLTree<int, int> t;

	for (auto e : a)
	{
		t.Insert(make_pair(e, e));
	}

	t.InOrder();
	cout << t.IsAVLTree() << endl;

	t[3] *= 20;
	t[5] *= 20;

	t.InOrder();

	AVLTree<std::string, std::string> dict;

	dict.Insert(make_pair("sort", "ÅÅÐò"));
	dict.Insert(make_pair("left", "×ó±ß"));

	dict.InOrder();
}

int main()
{
	TestAVLTree1();
	return 0;
}