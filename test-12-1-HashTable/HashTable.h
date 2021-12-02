#pragma once
#include <iostream>
#include <vector>

using namespace std;

enum State
{
	EMPTY,
	EXITS,
	DELETE
};

template <class K>
struct Hash
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

//特化
template <>
struct Hash<string>
{
	size_t operator()(const string& str)
	{
		size_t value = 0;

		for (auto ch : str)
		{
			value += ch;
			//*131是冲突最少的方案
			value *= 131;
		}

		return value;
	}
};

template <class K, class V>
struct HashTableData
{
	pair<K, V> _kv;
	State _state;//状态因子
};

template <class K, class V, class HashFunc = Hash<K>>
class HashTable
{
private:
	vector<HashTableData<K, V>> _table;
	size_t _n;//记录存储的有效数据个数,负载因子

public:
	bool Insert(const pair<K, V> kv)
	{
		HashTableData<K, V>* ret = Find(kv.first);

		if (nullptr != ret)
		{
			return false;
		}

		if (!_table.size())
		{
			_table.resize(10);
		}
		//如果高于0.7我们就进行扩容
		//因为能存的空间越小那么就容易出现过度拥挤
		//如果太低那么我们就会浪费很多空间，建议值一般是在0.7至0.8
		else if ((double)_n / (double)_table.size() > 0.7)
		{
			HashTable<K, V, HashFunc> newHt;
			newHt._table.resize(_table.size() * 2);

			for (auto& e : _table)
			{
				if (e._state == EXITS)
				{
					newHt.Insert(e._kv);
				}
			}

			_table.swap(newHt._table);
		}

		HashFunc hf;
		
		size_t state = hf(kv.first) % _table.size();
		size_t index = state;
		size_t i = 1;

		while (_table[index]._state == EXITS)
		{
			index = state + i * i;
			//防止要插入位置超过空间大小
			index %= _table.size();
			++i;
		}

		_table[index]._kv = kv;
		_table[index]._state = EXITS;
		_n++;

		return true;
	}

	HashTableData<K, V>* Find(const K& key)
	{
		if (!_table.size())
		{
			return nullptr;
		}

		HashFunc hf;

		size_t i = 1;
		size_t state = hf(key) % _table.size();
		size_t index = state;

		while (_table[index]._state != EMPTY)
		{
			if (_table[index]._state == EXITS && _table[index]._kv.first == key)
			{
				return &_table[index];
			}

			index = state + i * i;
			index %= _table.size();
			++i;
		}

		return nullptr;
	}

	bool Erase(const K& key)
	{
		HashTableData<K, K>* ret = Find(key);

		if (nullptr == ret)
		{
			return false;
		}
		else
		{
			ret->_state = DELETE;
			_n--;

			return true;
		}
	}
};