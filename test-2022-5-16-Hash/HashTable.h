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

#endif