#pragma once
#include <vector>
#include <iostream>
using namespace std;

namespace ls
{
	enum State
	{
		EMPTY,
		EXITS,
		DELETE,
	};

	template<class K, class V>
	struct HashData
	{
		pair<K, V> _kv;
		State _state = EMPTY;  // ״̬
	};

	template<class K>
	struct Hash
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	// �ػ�
	template<>
	struct Hash<string>
	{
		// "int"  "insert" 
		// �ַ���ת�ɶ�Ӧһ������ֵ����Ϊ���β���ȡģ��ӳ��λ��
		// ����->�ַ�����ͬ��ת��������ֵ������ͬ
		// "abcd" "bcad"
		// "abbb" "abca"
		size_t operator()(const string& s)
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

	template<class K, class V, class HashFunc = Hash<K>>
	class HashTable
	{
	public:
		bool Insert(const pair<K, V>& kv)
		{
			HashData<K, V>* ret = Find(kv.first);
			if (ret)
			{
				return false;
			}

			// �������Ӵ���0.7��������
			//if (_n*10 / _table.size() > 7)
			if (_table.size() == 0)
			{
				_table.resize(10);
			}
			else if ((double)_n / (double)_table.size() > 0.7)
			{
				//vector<HashData> newtable;
				// newtable.resize(_table.size*2);
				//for (auto& e : _table)
				//{
				//	if (e._state == EXITS)
				//	{
				//		// ���¼���ŵ�newtable
				//		// ...����������߼�����
				//	}
				//}

				//_table.swap(newtable);

				HashTable<K, V, HashFunc> newHT;
				newHT._table.resize(_table.size() * 2);
				for (auto& e : _table)
				{
					if (e._state == EXITS)
					{
						newHT.Insert(e._kv);
					}
				}

				_table.swap(newHT._table);
			}

			HashFunc hf;
			size_t start = hf(kv.first) % _table.size();
			size_t index = start;

			// ̽������λ�� -- ����̽�� or ����̽��
			size_t i = 1;
			while (_table[index]._state == EXITS)
			{
				index = start + i;
				index %= _table.size();
				++i;
			}

			_table[index]._kv = kv;
			_table[index]._state = EXITS;
			++_n;

			return true;
		}

		HashData<K, V>* Find(const K& key)
		{
			if (_table.size() == 0)
			{
				return nullptr;
			}

			HashFunc hf;
			size_t start = hf(key) % _table.size();
			size_t index = start;
			size_t i = 1;
			while (_table[index]._state != EMPTY)
			{
				if (_table[index]._state == EXITS
					&& _table[index]._kv.first == key)
				{
					return &_table[index];
				}

				index = start + i;
				index %= _table.size();
				++i;
			}

			return nullptr;
		}

		bool Erase(const K& key)
		{
			HashData<K, V>* ret = Find(key);
			if (ret == nullptr)
			{
				return false;
			}
			else
			{
				ret->_state = DELETE;
				return true;
			}
		}

	private:
		/*	HashData* _table;
			size_t _size;
			size_t _capacity;*/
		vector<HashData<K, V>> _table;
		size_t _n = 0;  // �洢��Ч���ݵĸ���
	};
}