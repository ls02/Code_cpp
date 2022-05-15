#include "RBTree.h"
#include "Map.h"
#include "Set.h"

int main(void)
{
	ls::map<int, int> m1;

	m1.Insert(std::make_pair(1, 1));
	m1.Insert(std::make_pair(2, 2));
	m1.Insert(std::make_pair(3, 3));
	m1.Insert(std::make_pair(4, 4));

	return 0;
}