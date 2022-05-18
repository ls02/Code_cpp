#pragma once
#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <iostream>
#include <vector>
#include <string>

namespace ls
{
	template<class T>
	struct HashNode
	{
		HashNode<T>* _next;
		T _data;

		HashNode(const T& data)
			:_next(nullptr)
			,_data(data)
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

	//前置声明
	template <class K, class T, class KeyOfT, class HashFunc>
	class HashTable;

	template<class K, class T, class KeyOfT, class HashFunc = Hash<K>>
	struct __HTIterator
	{
		typedef HashNode<T> Node;
		typedef __HTIterator<K, T, KeyOfT, HashFunc> Self;
		typedef HashTable<K, T, KeyOfT, HashFunc> HT;

		Node* _node;
		HT* _pht;

		__HTIterator(Node* node, HT* _pht)
			:_node(node)
			,_pht(_pht)
		{}

		Self& operator++()
		{
			if (nullptr != _node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				size_t index = HashFunc()(KeyOfT()(_node->_data)) % _pht->_table.size();

				index++;

				while (index < _pht->_table.size())
				{
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
				size_t index = HashFunc()(KeyOfT()(_node->_data)) % _pht->_table.size();

				index++;

				while (index < _pht->_table.size())
				{
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

				_node = nullptr;
			}

			return temp;
		}

		T& operator*(void)
		{
			return _node->_data;
		}

		T* operator->(void)
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
		template<class K, class T, class KeyOfT, class HashFunc>
		friend struct __HTIterator;
			
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
		typedef __HTIterator<K, T, KeyOfT, HashFunc> iterator;
		HashTable() = default; // 显示指定生成默认构造

		HashTable(const HashTable& ht)
		{
			_table.resize(ht._table.size());
			_n = ht._n;

			for (size_t i = 0; i < ht._table.size(); i++)
			{
				Node* cur = ht._table[i];

				while (nullptr != cur)
				{
					Node* copyNode = Node(cur->_data);
					copyNode->_next = _table[i];
					_table[i] = copyNode;
					
					cur = cur->_next;
				}
			}
		}

		HashTable& operator=(HashTable ht)
		{
			_table.swap(ht._table);

			return *this;
		}

		~HashTable(void)
		{
			for (size_t i = 0; i < _table.size(); i++)
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

		//迭代器
		iterator begin(void)
		{
			size_t i = 0;

			while (i < _table.size())
			{
				if (nullptr != _table[i])
				{
					return iterator(_table[i], this);
				}
					i++;
			}

			return iterator(nullptr, this);
		}

		iterator end(void)
		{
			return iterator(nullptr, this);
		}



		std::pair<iterator, bool>Insert(const T& data)
		{
			iterator ret = Find(KeyOfT()(data));
			if (end() != ret)
			{
				return std::make_pair(ret, false);
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
							size_t index = KeyOfT()(cur->_data);
							Node* next = cur->_next;

							cur->_next = newTable[i];
							newTable[i] = cur;

							cur = next;
						}
						_table[i] = nullptr;
					}
				}

				_table.swap(newTable);
			}

			size_t index = HashFunc()(KeyOfT()(data)) % _table.size();
			Node* newNode = new Node(data);

			newNode->_next = _table[index];
			_table[index] = newNode;
			++_n;

			return std::make_pair(iterator(newNode, this), true);
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
			Node* prev = nullptr;
			Node* cur = _table[index];

			while (nullptr != cur)
			{
				if (KeyOfT()(cur->_data) == key)
				{
					if (_table[index] == cur)
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
	};
}

#endif