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

//�ػ�
template <>
struct Hash<string>
{
	size_t operator()(const string& str)
	{
		size_t value = 0;

		for (auto ch : str)
		{
			value += ch;
			//*131�ǳ�ͻ���ٵķ���
			value *= 131;
		}

		return value;
	}
};

template <class K, class V>
struct HashTableData
{
	pair<K, V> _kv;
	State _state;//״̬����
};

template <class K, class V, class HashFunc = Hash<K>>
class HashTable
{
private:
	vector<HashTableData<K, V>> _table;
	size_t _n;//��¼�洢����Ч���ݸ���,��������

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
		//�������0.7���Ǿͽ�������
		//��Ϊ�ܴ�Ŀռ�ԽС��ô�����׳��ֹ���ӵ��
		//���̫����ô���Ǿͻ��˷Ѻܶ�ռ䣬����ֵһ������0.7��0.8
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
			//��ֹҪ����λ�ó����ռ��С
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