#include "BinarySearchTree.h"
#include <string>

void Test1(void)
{
	K::BSTree<int> k;
	k.Insert(7);
	k.Insert(3);
	k.Insert(10);
	k.InOrder();

	K::BSTree<int> k1(k);
	K::BSTree<int> k2;
	k2 = k;

	k.Erase(7);
	k.InOrder();
	k.Erase(10);
	k.InOrder();
	k.Erase(3);
	k.InOrder();

	k1.InOrder();
	k2.InOrder();
}

void Test2(void)
{
	KV::BSTree<std::string, std::string> kv1;

	std::string str1[] = { "你好", "我的", "世界", "人才市场" };
	std::string str2[] = { "hello", "my", "world", "talent market" };

	for (int i = 0; i < 4; i++)
	{
		kv1.Insert(str2[i], str1[i]);
	}
	KV::BSTree<std::string, std::string> kv2;
	kv2 = kv1;

	kv1.InOrder();
	kv2.InOrder();
	kv1.Erase("hello");
	kv1.InOrder();
}

int main(void)
{
	//Test1();
	Test2();

	return 0;
}