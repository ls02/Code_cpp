#pragma once
#ifndef __BLOOMFILTER_H__
#define __BLOOMFILTER_H__
#include "BitSet.h"

using std::cout;
using std::endl;

struct HashBKDR
{
	// "int"  "insert" 
	// 字符串转成对应一个整形值，因为整形才能取模算映射位置
	// 期望->字符串不同，转出的整形值尽量不同
	// "abcd" "bcad"
	// "abbb" "abca"
	size_t operator()(const std::string& s)
	{
		// BKDR Hash
		size_t value = 0;
		for (auto ch : s)
		{
			value += ch;
			value *= 131;
		}

		return value;
	}
};

struct HashAP
{
	// "int"  "insert" 
	// 字符串转成对应一个整形值，因为整形才能取模算映射位置
	// 期望->字符串不同，转出的整形值尽量不同
	// "abcd" "bcad"
	// "abbb" "abca"
	size_t operator()(const std::string& s)
	{
		// AP Hash
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; i < (long)s.size(); i++)
		{
			ch = s[i];
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}
};

struct HashDJB
{
	// "int"  "insert" 
	// 字符串转成对应一个整形值，因为整形才能取模算映射位置
	// 期望->字符串不同，转出的整形值尽量不同
	// "abcd" "bcad"
	// "abbb" "abca"
	size_t operator()(const std::string& s)
	{
		// BKDR Hash
		register size_t hash = 5381;
		for (auto ch : s)
		{
			hash += (hash << 5) + ch;
		}

		return hash;
	}
};

template<size_t N, class K = std::string,
	class Hash1 = HashBKDR,
	class Hash2 = HashAP,
	class Hash3 = HashDJB>
class BloomFilter
{
private:
	ls::BitSet<N> _bitset;

public:
	void Set(const K& key)
	{
		size_t i1 = Hash1()(key) % N;
		size_t i2 = Hash2()(key) % N;
		size_t i3 = Hash3()(key) % N;

		_bitset.Set(i1);
		_bitset.Set(i2);
		_bitset.Set(i3);
	}

	bool Test(const K& key)
	{
		size_t i1 = Hash1()(key) % N;
		if (_bitset.Test(i1) == false)
		{
			return false;
		}

		size_t i2 = Hash2()(key) % N;
		if (_bitset.Test(i2) == false)
		{
			return false;
		}

		size_t i3 = Hash3()(key) % N;
		if (_bitset.Test(i3) == false)
		{
			return false;
		}

		// 这里3个位都在，有可能是其他key占了，在是不准确的，存在误判
		// 不在是准确的
		return true;
	}
};

void TestBloomFilter()
{
	/*BloomFilter<100> bf;
	bf.Set("张三");
	bf.Set("李四");
	bf.Set("牛魔王");
	bf.Set("红孩儿");

	cout << bf.Test("张三") << endl;
	cout << bf.Test("李四") << endl;
	cout << bf.Test("牛魔王") << endl;
	cout << bf.Test("红孩儿") << endl;
	cout << bf.Test("孙悟空") << endl;*/

	BloomFilter<600> bf;

	size_t N = 100;
	std::vector<std::string> v1;
	for (size_t i = 0; i < N; ++i)
	{
		std::string url = "https://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html";
		url += std::to_string(1234 + i);
		v1.push_back(url);
	}

	for (auto& str : v1)
	{
		bf.Set(str);
	}

	for (auto& str : v1)
	{
		cout << bf.Test(str) << endl;
	}
	cout << endl << endl;

	std::vector<std::string> v2;
	for (size_t i = 0; i < N; ++i)
	{
		std::string url = "https://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html";
		url += std::to_string(6789 + i);
		v2.push_back(url);
	}

	size_t n2 = 0;
	for (auto& str : v2)
	{
		if (bf.Test(str))
		{
			++n2;
		}
	}
	cout << "相似字符串误判率:" << (double)n2 / (double)N << endl;

	std::vector<std::string> v3;
	for (size_t i = 0; i < N; ++i)
	{
		std::string url = "https://zhuanlan.zhihu.com/p/43263751";
		url += std::to_string(6789 + i);
		v3.push_back(url);
	}

	size_t n3 = 0;
	for (auto& str : v3)
	{
		if (bf.Test(str))
		{
			++n3;
		}
	}
	cout << "不相似字符串误判率:" << (double)n3 / (double)N << endl;

}

#endif