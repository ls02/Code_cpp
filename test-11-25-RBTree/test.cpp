#define _CRT_SECURE_NO_WARNINGS 1
#include "RBTree.h"
#include <time.h>
#include <map>

void TestRBTree1()
{
	int a[] = { 16, 3, 7 , 11, 9, 26, 18, 14, 15 };
	RBTree<int, int> t;
	int n = 1000000;
	
	//for (auto e : a)
	//{
	//	t.Insert(make_pair(e, e));
	//}
	srand((size_t)time(0));

	for (int i = 0; i < n; ++i)
	{
		int e = rand();
		t.Insert(make_pair(e, e));
	}

	//t.InOrder();
	cout << t.CheckBlance();
}

void TestMap1()
{
	std::string s1("ÄãºÃ");
	std::string s2("hello");
	std::map<std::string, std::string> m1;

	m1.insert(pair<std::string, std::string>(s1, s2));
	//m1.insert(make_pair(s1, s2));

	std::map<std::string, std::string>::iterator it = m1.begin();

	while (it != m1.end())
	{
		cout << it->second << "£º" << it->first << endl;
		it++;
	}
	
}

int main()
{
	//TestRBTree1();
	//std::map<int, int> m;
	//int n = 100;
	//srand((size_t)time(0));

	//m.insert(std::pair<int, int>(3, 4));

	//std::map<int, int>::iterator it = m.begin();

	//for (int i = 0; i < n; i++)
	//{
	//	int temp = rand();
	//	m.insert(std::pair<int, int>(temp, i));
	//}

	//while (it != m.end())
	//{
	//	cout << (*it).second << "£º" << it->first << endl;
	//	it++;
	//}

	TestMap1();

	return 0;
}