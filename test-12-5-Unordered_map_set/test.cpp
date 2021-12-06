#define _CRT_SECURE_NO_WARNINGS 1
#include <time.h>
#include "Unordered_set.h"
#include "Unordered_map.h"
#include "BitSet.h"

//void TestOpenHashTable1()
//{
//	srand((size_t)time(0));
//
//	OpenHashTable::HashTable<int, int> ht1;
//	int arr[] = { 10, 100, 40, 500, 2 };
//	int n = 10000;
//
//	for (auto e : arr)
//	{
//		ht1.Insert(e);
//	}
//
//	//for (int i = 0; i < n; i++)
//	//{
//	//	int e = rand();
//	//	ht1.Insert(e);
//	//}
//
//	ht1.Erase(10);
//
//	cout << endl;
//}

void TestUnordered_set1()
{
	ls::Unordered_set<int> s1;
	//srand((size_t)time(0));
	//int n = 1000;

	//for (int i = 0; i < n; i++)
	//{
	//	int e = rand();
	//	s1.insert(e);
	//}

	//cout << endl;

	int arr[] = { 10, 100, 40, 500, 2 };

	for (auto e : arr)
	{
		s1.insert(e);
	}

	ls::Unordered_set<int> s2;
	s2 = s1;

	cout << endl;

	//ls::Unordered_set<int>::iterator it = s1.begin();

	//while (it != s1.end())
	//{
	//	cout << *it << endl;
	//	++it;
	//}
}

void TestUnordered_map1()
{
	ls::Unordered_map<int, int> m1;

	srand((size_t)time(0));
	//int n = 1000;

	//for (int i = 0; i < n; i++)
	//{
	//	int e = rand();
	//	m1.insert(make_pair(e, e));
	//}

	//cout << endl;

	int arr[] = { 10, 100, 40, 500, 2 };

	for (auto e : arr)
	{
		m1.insert(make_pair(e, e));
	}
	ls::Unordered_map<int, int> m2;

	m2 = m1;

	cout << endl;

	//ls::unordered_map<int, int>::iterator it = m1.begin();

	//while (it != m1.end())
	//{
	//	cout << it->first << ":" << it->second << endl;
	//	it++;
	//}
}

void TestBitSet1()
{
	ls::BitSet <1> bs1;

	bs1.Set(20);
	bs1.Set(30);
	bs1.Set(10);
	bs1.Set(11);

	cout << bs1.size() << endl;
}

int main()
{
	//TestOpenHashTable1();
	//TestUnordered_set1();
	//TestUnordered_map1();

	TestBitSet1();

	return 0;
}