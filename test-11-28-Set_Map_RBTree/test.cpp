#define _CRT_SECURE_NO_WARNINGS 1
#include "Map.h"
#include <time.h>
#include "Set.h"
#include <string>

//template <class Con>
//void testPrint(Con& k)
//{
//	ls::set<int, int>::iterator it = k.begin();
//
//	while (it != k.end())
//	{
//		cout << *it << endl;
//		++it;
//	}
//}

void TestMap1()
{
	srand((size_t)time(0));
	ls::map<int, int> m1;
	int n = 100;
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };


	for (auto e : a)
	{
		m1.insert(make_pair(e, e));
	}

	//for (int i = 0; i < n; i++)
	//{
	//	int e = rand();
	//	m1.insert(make_pair(e, e));
	//}

	ls::map<int, int> m2;
	m2 = m1;
	ls::map<int, int>::iterator it1 = m1.begin();
	//while (it1 != m1.end())
	//{
	//	cout << it1->first << endl;

	//	++it1;
	//}

	//ls::map<int, int>::reverse_iterator rit = m2.rbegin();
	//while (rit != m2.rend())
	//{
	//	cout << (*rit).first << endl;
	//	++rit;
	//}

	ls::map<int, int>::iterator it = m2.begin();
	while (it != m2.end())
	{
		cout << it->first << endl;
		++it;
	}

	cout << m1.CheckBlance() << endl;
}

void TestMap2()
{
	ls::map<std::string, int> m;

	m.insert(make_pair("left", 1));
	m.insert(make_pair("left", 1));
	m.insert(make_pair("left", 1));
	m.insert(make_pair("left", 1));
	m.insert(make_pair("left", 1));
	m.insert(make_pair("left", 1));

	m["left"]++;


	for (auto e : m)
	{
		cout << e.first << ":" << e.second << endl;
	}
}

void TestSet1()
{
	ls::set<int, int> s1;
	int n = 100;

	srand((size_t)time(0));

	//s1.insert(10);
	//s1.insert(20);
	//s1.insert(30);

	for (int i = 0; i < n; i++)
	{
		int e = rand();

		s1.insert(e);
	}
	
	//testPrint(s1);
	//ls::set<int, int>::reverse_iterator rit = s1.rbegin();

	//while (rit != s1.rend())
	//{
	//	cout << *rit << endl;
	//	++rit;
	//}

	ls::set<int, int> s2;
	s2 = s1;
	
	cout << s1.CheckBlance() << endl;

	ls::set<int, int>::iterator it2 = s2.begin();

	while (it2 != s2.end())
	{
		cout << *it2 << endl;
		++it2;
	}

	//ls::set<int, int>::iterator it = s1.begin();

	//while (it != s1.end())
	//{
	//	cout << *it << endl;
	//	++it;
	//}
}


int main()
{
	//TestMap1();
	//TestMap2();
	//TestSet1();

	int* a = new int(1);

	free(a);

	return 0;
}
