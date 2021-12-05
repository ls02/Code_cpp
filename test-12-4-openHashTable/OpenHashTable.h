#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace ls
{
	template <class K>
	struct Hash
	{
		int operator()(const K& key)
		{
			return key;
		}
	};

	template <>
	struct Hash<string>
	{
		int operator()(const string& str)
		{
			int value = 0;

			for (auto ch : str)
			{
				value += ch;
				value *= 131;
			}

			return value;
		}
	};

	template <class K, class V>
	struct HashNode
	{
		HashNode<K, V>* _next;
		pair<K, V> _kv;

		HashNode(const pair<K, V>& kv)
			:_next(nullptr)
			,_kv(kv)
		{}
	};

	template <class K, class V, class HashFunc = Hash<K>>
	class HashTable
	{
		typedef HashNode<K, V> Node;
	private:
		vector<Node*> _table;
		size_t _n = 0;

	public:
		size_t GetNextPrime(size_t prime)
		{
			const int PRIMECOUNT = 28;
			static const size_t primeList[PRIMECOUNT] =
			{
				53ul, 97ul, 193ul, 389ul, 769ul,
				1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
				49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
				1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
				50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
			};

			size_t i = 0;
			for (; i < PRIMECOUNT; ++i)
			{
				if (primeList[i] > prime)
					return primeList[i];
			}

			return primeList[i];
		}

		bool Insert(const pair<K, V>& kv)
		{
			if (nullptr != Find(kv.first))
			{
				return false;
			}

			HashFunc hf;

			//负载因子为1时扩容
			if (_n == _table.size())
			{
				vector<Node*> newtable;
				newtable.resize(GetNextPrime(_table.size()));

				for (size_t i = 0; i < _table.size(); i++)
				{
					if (nullptr != _table[i])
					{
						Node* cur = _table[i];

						while (nullptr != cur)
						{
							Node* next = cur->_next;
							size_t index = hf(cur->_kv.first) % newtable.size();

							//头插
							cur->_next = newtable[index];
							newtable[index] = cur;

							cur = next;
						}

						_table[i] = nullptr;
					}
				}

				_table.swap(newtable);
			}

			size_t index = hf(kv.first) % _table.size();
			Node* newNode = new Node(kv);

			//头插
			newNode->_next = _table[index];
			_table[index] = newNode;

			++_n;

			return true;
		}

		Node* Find(const K& key)
		{
			if (!_table.size())
			{
				return nullptr;
			}

			HashFunc hf;
			size_t index = hf(key) % _table.size();
			Node* cur = _table[index];

			while (nullptr != cur)
			{
				if (cur->_kv.first == key)
				{
					return cur;
				}
				else
				{
					cur = cur->_next;
				}
			}

			return nullptr;
		}

		bool Erase(const K& key)
		{
			HashFunc hf;
			size_t index = hf(key) % _table.size();
			Node* prev = nullptr;
			Node* cur = _table[index];

			while (nullptr != cur)
			{
				if (cur->_kv.first == key)
				{
					if (_table[index] == cur)
					{
						_table[index] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}

					delete cur;
					--_n;

					return true;
				}

				prev = cur;
				cur = cur->_next;
			}

			return false;
		}
	};
}