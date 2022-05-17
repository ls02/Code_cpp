#include "HashTable.h"

void TestHash1(void)
{
	CloseHash::HashTable<int, int> h1;

	h1.Insert(std::make_pair(1, 1));
	h1.Insert(std::make_pair(2, 2));
	h1.Insert(std::make_pair(3, 3));
	h1.Insert(std::make_pair(4, 4));

	
}

void TestHash2(void)
{
	OpenHash::HashTable<int, int> h1;

	h1.Insert(std::make_pair(1, 1));
	h1.Insert(std::make_pair(2, 2));
	h1.Insert(std::make_pair(3, 3));
	h1.Insert(std::make_pair(4, 4));
	h1.Insert(std::make_pair(11, 11));

	h1.Erase(11);
	h1.Erase(1);
	h1.Erase(2);
}

int main(void)
{
	TestHash2();
	//TestHash1();
	return 0;
}