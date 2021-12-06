#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace OpenHashTable
{
	template <class K>
	struct Hash
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	template <>
	struct Hash<string>
	{
		size_t operator()(const string& str)
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

	template <class T>
	struct HashNode
	{
		HashNode<T>* _next;
		T _data;

		HashNode(const T& data)
			:_data(data)
			,_next(nullptr)
		{}
	};

	template <class K, class T, class KeyOfT, class HashFunc>
	class HashTable;

	//迭代器
	template <class K, class T, class KeyOfT, class HashFunc = Hash<K>>
	struct __HTIterator
	{
		typedef HashNode<T> Node;
		typedef HashTable<K, T, KeyOfT, HashFunc> HT;
		typedef __HTIterator<K, T, KeyOfT, HashFunc> Self;

		HT* _pht;
		Node* _node;

		__HTIterator(Node* node, HT* pht)
			:_pht(pht)
			,_node(node)
		{}

		Self& operator++()
		{
			if (nullptr != _node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				//定位当前桶的位置
				size_t index = HashFunc()(KeyOfT()(_node->_data)) % _pht->_table.size();
				index++;

				while (index < _pht->_table.size())
				{
					//看这个桶是否为空，不为空就是，为空就找下个桶
					if (nullptr != _pht->_table[index])
					{
						_node = _pht->_table[index];

						return *this;
					}
					else
					{
						index++;
					}
				}

				//到尾了，_node置空
				_node = nullptr;
			}

			return *this;
		}

		Self operator++(int)
		{
			Self temp = *this;

			if (nullptr != _node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				//定位当前桶的位置
				size_t index = HashFunc()(KeyOfT()(_node->_data)) % _pht->_table.size();
				index++;

				while (index < _pht->_table.size())
				{
					//看这个桶是否为空，不为空就是，为空就找下个桶
					if (nullptr != _pht->_table[index])
					{
						_node = _pht->_table[index];

						return *this;
					}
					else
					{
						index++;
					}
				}

				//到尾了，_node置空
				_node = nullptr;
			}

			return temp;
		}

		T& operator*()
		{
			return _node->_data;
		}

		T* operator->()
		{
			return &_node->_data;
		}

		bool operator!=(const Self& s)const
		{
			return _node != s._node;
		}

		bool operator==(const Self& s)const
		{
			return _node == s._node;
		}
	};

	template <class K, class T, class KeyOfT, class HashFunc = Hash<K>>
	class HashTable
	{
		typedef HashNode<T> Node;

		template <class K, class T, class KeyOfT, class HashFunc>
		friend struct __HTIterator;

	public:
		typedef __HTIterator<K, T, KeyOfT, HashFunc> iterator;
		HashTable() = default;

		iterator begin()
		{
			size_t i = 0;

			for (i = 0; i < _table.size(); i++)
			{
				if (nullptr != _table[i])
				{
					return iterator(_table[i], this);
				}
			}

			return end();
		}

		iterator end()
		{
			return iterator(nullptr, this);
		}

		//拷贝构造
		HashTable(const HashTable& ht)
		{
			_table.resize(ht._table.size());
			_n = ht._n;

			for (size_t i = 0; i < _table.size(); i++)
			{
				if (nullptr != ht._table[i])
				{
					Node* cur = ht._table[i];

					while (nullptr != cur)
					{
						Node* copyNode = new Node(cur->_data);

						copyNode->_next = _table[i];
						_table[i] = copyNode;

						cur = cur->_next;
					}
				}
			}
		}

		HashTable& operator=(HashTable ht)
		{
			_table.swap(ht._table);

			return *this;
		}

		~HashTable()
		{
			size_t i = 0;

			for (i = 0; i < _table.size(); i++)
			{
				if (nullptr != _table[i])
				{
					Node* cur = _table[i];

					while (nullptr != cur)
					{
						Node* next = cur->_next;

						delete cur;
						cur = next;
					}

					_table[i] = nullptr;
				}
			}
		}

		pair<iterator, bool> Insert(const T& data)
		{
			iterator ret = Find(KeyOfT()(data));

			if (ret != end())
			{
				return make_pair(ret, false);
			}

			if (_n == _table.size())//负载因子为1，超过就扩容
			{
				vector<Node*> newTable;
				size_t i = 0;

				newTable.resize(GetNextPrime(_table.size()));

				//把旧表的数据挂到新表
				for (i = 0; i < _table.size(); i++)
				{
					if (nullptr != _table[i])
					{
						Node* cur = _table[i];
						//算出在新表的位置
						size_t index = HashFunc()(KeyOfT()(cur->_data)) % newTable.size();
						
						while (nullptr != cur)
						{
							Node* next = cur->_next;
							
							//头插
							cur->_next = newTable[index];
							newTable[index] = cur;
							cur = next;
						}

						//旧表断开数据的连接
						_table[i] = nullptr;
					}
				}

				_table.swap(newTable);
			}

			size_t index = HashFunc()(KeyOfT()(data)) % _table.size();
			Node* newNode = new Node(data);

			//头插
			newNode->_next = _table[index];
			_table[index] = newNode;
			_n++;

			return make_pair(iterator(newNode, this), true);
		}

		iterator Find(const K& key)
		{
			if (!_table.size())
			{
				return end();
			}

			size_t index = HashFunc()(key) % _table.size();
			Node* cur = _table[index];
			
			while (nullptr != cur)
			{
				if (KeyOfT()(cur->_data) == key)
				{
					return iterator(cur, this);
				}
				else
				{
					cur = cur->_next;
				}
			}

			return end();
		}

		bool Erase(const K& key)
		{
			size_t index = HashFunc()(key) % _table.size();
			Node* cur = _table[index];
			Node* prev = nullptr;

			while (nullptr != cur)
			{
				if (cur->_data == key)
				{
					if (cur == _table[index])
					{
						_table[index] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}

					--_n;
					delete cur;

					return true;
				}

				prev = cur;
				cur = cur->_next;
			}


			return false;
		}

	private:
		vector<Node*> _table;
		size_t _n = 0;//记录有效数据个数

		//素数表
		size_t GetNextPrime(const size_t& prime)
		{
			const size_t PRIMECOUNT = 28;
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
			for (; i < PRIMECOUNT; i++)
			{
				if (prime < primeList[i])
				{
					return primeList[i];
				}
			}

			return primeList[i];
		}
	};
}