#include "AVLTree.h"

void Test1()
{
	ls::AVLTree<int, int> t1;
	t1.Insert(std::make_pair(20, 1));
	t1.Insert(std::make_pair(50, 2));
	t1.Insert(std::make_pair(10, 3));
	t1.Insert(std::make_pair(60, 4));
	t1.Insert(std::make_pair(33, 5));
	t1.Insert(std::make_pair(70, 6));
	t1.Insert(std::make_pair(110, 7));

	t1.InOrder();
}

int main()
{
	Test1();

	return 0;
}