#include "AVLTree.h"

void Test1()
{
	int arr1[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int arr2[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	ls::AVLTree<int, int> t1;
	ls::AVLTree<int, int> t2;
	for (auto e : arr1)
	{
		t2.Insert(std::make_pair(e, e));
	}
	t1.Insert(std::make_pair(20, 1));
	t1.Insert(std::make_pair(50, 2));
	t1.Insert(std::make_pair(10, 3));
	t1.Insert(std::make_pair(60, 4));
	t1.Insert(std::make_pair(33, 5));
	t1.Insert(std::make_pair(70, 6));
	t1.Insert(std::make_pair(110, 7));

	t1.InOrder();
	std::cout << t1.IsAVLTree() << std::endl;
	std::cout << t2.IsAVLTree() << std::endl;
}

int main()
{
	Test1();

	return 0;
}