#include "BinarySearchTree.h"

void Test1(void)
{
	K::BSTree<int> k;
	k.Insert(7);
	k.Insert(3);
	k.Insert(10);
	k.InOrder();

	K::BSTree<int> k1(k);
	K::BSTree<int> k2;
	k2 = k;

	k.Erase(7);
	k.InOrder();
	k.Erase(10);
	k.InOrder();
	k.Erase(3);
	k.InOrder();

	k1.InOrder();
	k2.InOrder();
}

int main(void)
{
	Test1();

	return 0;
}