#include "RBTree.h"
#include <stdlib.h>

void TestRBTree1()
{
	srand((size_t)time(0));
	ls::RBTree<int, int> t1;
	ls::RBTree<int, int> t2;
	int arr1[] = { 5,3,4,1,7,8,2,6,0,9 };

	for (auto e : arr1)
	{
		
		t1.Insert(std::make_pair(e, e));
	}


	for (int i = 0; i < 10; i++)
	{
		int e = rand() % 100;

		t2.Insert(std::make_pair(e, e));
	}

	t1.Inorder();
	std::cout << std::endl;
	t2.Inorder();

	std::cout << t1.IsRBTree() << std::endl;
	std::cout << t2.IsRBTree() << std::endl;
}

int main(void)
{
	TestRBTree1();

	return 0;
}