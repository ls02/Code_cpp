#define _CRT_SECURE_NO_WARNINGS 1
#include "BingarySearchTree.h"

void TestBSTree1()
{
	K::BSTree<int>  bs1;
	K::BSTree<int>  bs2;
	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };

	for (auto e : arr)
	{
		bs1.Insert(e);
	}

	bs1.Order();

	bs1.Erase(0);
	bs2 = bs1;
	bs1.Order();
	bs2.Order();

	//K::BSNode<int>* a =bs2.Find(99);

	//cout << a << endl;
}

void TestBSTree2()
{
	K::BSTree<int> bs1;
	K::BSTree<int> bs2;

	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };

	for (auto e : arr)
	{
		bs1.Insert(e);
	}
	bs1.Order();

	bs1.EraseR(8);
	bs1.Order();

	bs1.InsertR(20);
	bs1.InsertR(-1);
	bs1.Order();

	cout << bs1.FindR(1) << endl;
}

void TestBSTree3()
{
	KV::BSTree<std::string, std::string> bs1;
	std::string s1;

	std::vector<std::string> v1 = { "你好", "世界", "尾、尾巴", "排序" };
	std::vector<std::string> v2 = { "hello", "world", "tail", "sort" };

	auto it1 = v1.begin();
	auto it2 = v2.begin();

	while (it1 != v1.end())
	{
		bs1.InsertR(*it2, *it1);

		it1++;
		it2++;
	}

	while (std::cin >> s1)
	{
		KV::BSNode<std::string, std::string>* bn = bs1.FindR(s1);

		if (bn == nullptr)
		{
			cout << "没有录入词库！" << endl;
		}
		else
		{
			cout << bn->_value << endl;
		}
	}
}

void TestBSTree()
{
	KV::BSTree < std::string, std:: string > dict;
	dict.InsertR("insert", "插入");
	dict.InsertR("erase", "删除");
	dict.InsertR("left", "左边");
	dict.InsertR("string", "字符串");

	std::string str;
	while (std::cin >> str)
	{
		auto ret = dict.FindR(str);
		if (ret)
		{
			cout << str << ":" << ret->_value << endl;
		}
		else
		{
			cout << "单词拼写错误" << endl;
		}
	}

	std::string strs[] = { "苹果", "西瓜", "苹果", "樱桃", "苹果", "樱桃", "苹果", "樱桃", "苹果" };
	// 统计水果出现的次
	KV::BSTree<std::string, int> countTree;
	for (auto str : strs)
	{
		auto ret = countTree.FindR(str);
		if (ret == nullptr)
		{
			countTree.InsertR(str, 1);
		}
		else
		{
			ret->_value++;
		}
	}
	countTree.Order();
}

int main()
{
	//TestBSTree1();
	//TestBSTree2();
	TestBSTree();

	return 0;
}