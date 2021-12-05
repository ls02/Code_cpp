#define _CRT_SECURE_NO_WARNINGS 1
#include "OpenHashTable.h"
#include <time.h>

void TestHashTable1()
{
	ls::HashTable<int, int> ht;
	int arr[] = { 10, 100, 1000, 10000, 5, 20, 3, 50 };

	for (auto e : arr)
	{
		ht.Insert(make_pair(e, e));
	}

	ht.Erase(10);
}

void TestHashTable2()
{
	ls::HashTable<string, string> ht;
	string s[] = { "苹果", "梨子", "西瓜" };

	for (auto e : s)
	{
		ht.Insert(make_pair(e, e));
	}

	ht.Erase("西瓜");
}

void TestHashTable3()
{
	ls::HashTable<int, int> ht;
	srand((size_t)time(0));
	int n = 10000000;

	size_t begin = clock();
	for (int i = 0; i < n; i++)
	{
		int e = rand();

		ht.Insert(make_pair(e, e));
	}
	size_t end = clock();

	cout << end - begin << endl;
}

int main()
{
	//TestHashTable1();
	//TestHashTable2();
	TestHashTable3();

	return 0;
}