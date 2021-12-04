#pragma once
#include <iostream>

using namespace std;

//namespace OpenHash
//{
//	template<class K>
//	struct Hash
//	{
//		size_t operator()(const K& key)
//		{
//			return key;
//		}
//	};
//
//	// 特化
//	template<>
//	struct Hash < string >
//	{
//		// "int"  "insert" 
//		// 字符串转成对应一个整形值，因为整形才能取模算映射位置
//		// 期望->字符串不同，转出的整形值尽量不同
//		// "abcd" "bcad"
//		// "abbb" "abca"
//		size_t operator()(const string& s)
//		{
//			// BKDR Hash
//			size_t value = 0;
//			for (auto ch : s)
//			{
//				value += ch;
//				value *= 131;
//			}
//
//			return value;
//		}
//	};
//
//	template<class K, class V>
//	struct HashNode
//	{
//		HashNode<K, V>* _next;
//		pair<K, V> _kv;
//
//		HashNode(const pair<K, V>& kv)
//			:_next(nullptr)
//			, _kv(kv)
//		{}
//	};
//
//	template<class K, class V, class HashFunc = Hash<K>>
//	class HashTable
//	{
//		typedef HashNode<K, V> Node;
//	public:
//		size_t GetNextPrime(size_t prime)
//		{
//			const int PRIMECOUNT = 28;
//			static const size_t primeList[PRIMECOUNT] =
//			{
//				53ul, 97ul, 193ul, 389ul, 769ul,
//				1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
//				49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
//				1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
//				50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
//				1610612741ul, 3221225473ul, 4294967291ul
//			};
//
//			size_t i = 0;
//			for (; i < PRIMECOUNT; ++i)
//			{
//				if (primeList[i] > prime)
//					return primeList[i];
//			}
//
//			return primeList[i];
//		}
//
//		bool Insert(const pair<K, V>& kv)
//		{
//			if (Find(kv.first))
//				return false;
//
//			HashFunc hf;
//			// 负载因子到1时，进行增容
//			if (_n == _table.size())
//			{
//				vector<Node*> newtable;
//				//size_t newSize = _table.size() == 0 ? 8 : _table.size() * 2;
//				//newtable.resize(newSize, nullptr);
//				newtable.resize(GetNextPrime(_table.size()));
//
//				// 遍历取旧表中节点，重新算映射到新表中的位置，挂到新表中
//				for (size_t i = 0; i < _table.size(); ++i)
//				{
//					if (_table[i])
//					{
//						Node* cur = _table[i];
//						while (cur)
//						{
//							Node* next = cur->_next;
//							size_t index = hf(cur->_kv.first) % newtable.size();
//							// 头插
//							cur->_next = newtable[index];
//							newtable[index] = cur;
//
//							cur = next;
//						}
//						_table[i] = nullptr;
//					}
//				}
//
//				_table.swap(newtable);
//			}
//
//			size_t index = hf(kv.first) % _table.size();
//			Node* newnode = new Node(kv);
//
//			// 头插
//			newnode->_next = _table[index];
//			_table[index] = newnode;
//			++_n;
//
//			return true;
//		}
//
//		Node* Find(const K& key)
//		{
//			if (_table.size() == 0)
//			{
//				return false;
//			}
//
//			HashFunc hf;
//			size_t index = hf(key) % _table.size();
//			Node* cur = _table[index];
//			while (cur)
//			{
//				if (cur->_kv.first == key)
//				{
//					return cur;
//				}
//				else
//				{
//					cur = cur->_next;
//				}
//			}
//
//			return nullptr;
//		}
//
//		bool Erase(const K& key)
//		{
//			size_t index = hf(key) % _table.size();
//			Node* prev = nullptr;
//			Node* cur = _table[index];
//			while (cur)
//			{
//				if (cur->_kv.first == key)
//				{
//					if (_table[index] == cur)
//					{
//						_table[index] = cur->_next;
//					}
//					else
//					{
//						prev->_next = cur->_next;
//					}
//
//					--_n;
//					delete cur;
//					return true;
//				}
//				
//				prev = cur;
//				cur = cur->_next;
//			}
//
//			return false;
//		}
//
//	private:
//		vector<Node*> _table;
//		size_t _n = 0;         // 有效数据的个数
//	};
//
//	void TestHashTable1()
//	{
//		int a[] = { 1, 5, 30, 100000, 100, 18, 15, 7, 40, 44 };
//		HashTable<int, int> ht;
//		for (auto e : a)
//		{
//			ht.Insert(make_pair(e, e));
//		}
//		ht.Insert(make_pair(25, 25));
//	}
//
//	void TestHashTable2()
//	{
//		string a[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "橘子", "苹果" };
//		HashTable<string, int> ht;
//		for (auto str : a)
//		{
//			auto ret = ht.Find(str);
//			if (ret)
//			{
//				ret->_kv.second++;
//			}
//			else
//			{
//				ht.Insert(make_pair(str, 1));
//			}
//		}
//	}
//}
