#define _CRT_SECURE_NO_WARNINGS 1
#include "HashTable.h"
#include <unordered_map>
#include <time.h>

void TestHashTable1()
{
	HashTable<int, int> ht1;
	int a[] = { 10, 2, 5, 40, 3, 100, 1000, 10000, 100000 };
	
	for (auto e : a)
	{
		ht1.Insert(make_pair(e, e));
	}

	HashTableData<int, int>* ret = ht1.Find(2);

	if (ret != nullptr)
	{
		cout << "找到了" << endl;
	}
	else
	{
		cout << "没找到" << endl;
	}
}

void TestHashTable2()
{
	HashTable<string, string> ht1;
	string s[] = { "hello", "left", "right", "head", "tail" };

	for (const auto& str : s)
	{
		ht1.Insert(make_pair(str, str));
	}

	ht1.Erase("left");

	HashTableData<string, string>* ht2 = ht1.Find("left");

	if (nullptr != ht2)
	{
		cout << "找到了!" << endl;
	}
	else
	{
		cout << "没找到 " << endl;
	}
	
}

vector<string> uncommonFromSentences(string s1, string s2) {
	string str = s1 + " " + s2;
	size_t i = 0;
	vector<string> retV;

	for (i = 0; i < str.size(); i++)
	{
		string temp;

		while (i < str.size() && str[i] != ' ')
		{
			temp += str[i];
			i++;
		}

		retV.push_back(temp);
	}

	std::unordered_map<string, int> um;

	for (const auto& e : retV)
	{
		um[e]++;
	}

	retV.clear();

	for (const auto& e : um)
	{
		if (e.second == 1)
		{
			retV.push_back(e.first);
		}
	}

	return retV;
}

void TestHashTable3()
{
	HashTable<int, int> ht1, ht2;
	size_t n = 100000;
	size_t i = 0;
	
	srand((size_t)time(0));

	size_t begin1 = clock();

	for (i = 0; i < n; i++)
	{
		int e = rand();

		ht1.Insert(make_pair(e, e));
	}
	size_t end1 = clock();


	cout << "ht1：" << end1 - begin1 << endl;
}

//int main()
//{
//	//TestHashTable1();
//	//TestHashTable2();
//	TestHashTable3();
//
//	//string s1 = "this apple is sweet";
//	//string s2 = "this apple is sour";
//
//	//vector<string> v = uncommonFromSentences(s1, s2);
//
//	//for (auto e : v)
//	//{
//	//	cout << e << endl;
//	//}
//
//	return 0;
//}

int main()
{
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int temp = 0;

	scanf("%d%d%d%d", &a, &b, &c, &d);

	if (a > b)
	{
		
	}
	else

	return 0;
}