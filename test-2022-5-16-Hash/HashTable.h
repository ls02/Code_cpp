#pragma once
#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__
#include <iostream>
#include <string>
#include <vector>
#include <utility>

namespace CloseHash
{
	enum State
	{
		EXIST,
		EMPTY,
		DELETE,
	};

	template <class K>
	struct Hash
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	template<>
	struct Hash<std::string>
	{
		size_t operator()(const std::string& str)
		{
			size_t value = 0;

			for (auto ch : str)
			{
				value += ch;
				value *= 131;
			}

			return value;
		}
	};

	template <class K, class V>
	struct HashData
	{
		std::pair<K, V> _kv;
		State _state = EMPTY;
	};

	template<class K, class V, class HashFun = Hash<K>>
	class HashTable
	{
		typedef HashTable<K, V, HashFun> HT;
	private:
		std::vector<HashData<K, V>> _table;
		size_t _n = 0;

	public:
		bool Insert(const std::pair<K, V>& kv)
		{
			if (Find(kv.first))
			{
				return false;
			}

			if (!_table.size())
			{
				_table.resize(10);
			}
			else if ((double)_n / (double)_table.size() > 0.7)
			{
				HT newHT;
				newHT._table.resize(_table.size() * 2);

				for (auto& e : _table)
				{
					if (e._state == EXIST)
					{
						newHT.Insert(e._kv);
					}
				}

				_table.swap(newHT._table);
			}

			size_t start = HashFun()(kv.first) % _table.size();
			size_t index = start;
			size_t i = 1;

			while (_table[index]._state != EMPTY)
			{
				index = start + i * i;
				index %= _table.size();
				i++;
			}

			_table[index]._kv = kv;
			_table[index]._state = EXIST;
			_n++;

			return true;
		}

		HashData<K, V>* Find(const K& key)
		{
			if (!_table.size())
			{
				return nullptr;
			}

			size_t start = HashFun()(key) % _n;
			size_t index = start;
			size_t i = 1;

			while (_table[index]._state != EMPTY)
			{
				if (_table[index]._state == EXIST &&
					_table[index]._kv.first == key)
				{
					return &_table[index];
				}

				index = start + i * i;
				index %= _table.size();
				i++;
			}

			return nullptr;
		}

		bool Erase(const K& key)
		{
			HT* ret = Find(key);

			if (nullptr != ret)
			{
				ret._start = DELETE;
				_n--;

				return true;
			}
			else
			{
				return false;
			}
		}
	};
}

namespace OpenHash
{
	template<class K, class V>
	struct HashNode
	{
		HashNode<K, V>* _next;
		std::pair<K, V> _kv;

		HashNode(const std::pair<K, V>& kv)
			:_next(nullptr)
			,_kv(kv)
		{}
	};

	template<class K>
	struct Hash
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	template<>
	struct Hash <std::string>
	{
		size_t operator()(const std::string& str)
		{
			size_t val = 0;

			for (auto ch : str)
			{
				val += ch;
				val *= 131;
			}

			return val;
		}
	};

	template <class K, class V,class HashFunc = Hash<K>>
	class HashTable
	{
		typedef HashNode<K,V> Node;
	private:
		std::vector<Node*> _table;
		size_t _n = 0;

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

	public:
		bool Insert(const std::pair<K, V> kv)
		{
			if (nullptr != Find(kv.first))
			{
				return false;
			}

			if (_n == _table.size())
			{
				std::vector<Node*> newTable;
				newTable.resize(GetNextPrime(_table.size()));

				for (size_t i = 0; i < _table.size(); i++)
				{
					if (nullptr != _table[i])
					{
						Node* cur = _table[i];

						while (nullptr != cur)
						{
							Node* next = cur->_next;
							size_t index = HashFunc()(cur->_kv.first) % newTable.size();
							cur->_next = newTable[index];
							newTable[index] = cur;

							cur = next;
						}

						_table[i] = nullptr;
					}
				}

				_table.swap(newTable);
			}

			size_t index = HashFunc()(kv.first) % _table.size();
			Node* newNode = new Node(kv);

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

			size_t index = HashFunc()(key) % _table.size();

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
			size_t index = HashFunc()(key) % _table.size();
			Node* prev = nullptr;
			Node* cur = _table[index];

			while (nullptr != cur)
			{
				if (cur->_kv.first == key)
				{
					if (cur == _table[index])
					{
						_table[index] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}

					delete cur;
					cur = nullptr;
					_n--;

					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}

			return false;
		}
	};
}

#endif