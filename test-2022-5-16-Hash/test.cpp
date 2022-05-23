#include "HashTable.h"
#include "BitSet.h"

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

void TestBitSet1(void)
{
	ls::BitSet<-1> b;

	b.Set(30);

	std::cout << b.Test(30) << std::endl;
}


int main(void)
{
	//Test
	TestBitSet1();
	TestHash2();
	TestHash1();
	return 0;
}