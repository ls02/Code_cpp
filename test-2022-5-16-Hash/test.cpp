#include "HashTable.h"

void TestHash1(void)
{
	CloseHash::HashTable<int, int> h1;

	h1.Insert(std::make_pair(1, 1));
	h1.Insert(std::make_pair(2, 2));
	h1.Insert(std::make_pair(3, 3));
	h1.Insert(std::make_pair(4, 4));

	
}

int main(void)
{
	TestHash1();
	return 0;
}