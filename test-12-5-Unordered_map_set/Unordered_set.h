#pragma once
#include "OpenHash.h"

namespace ls
{
	template <class K>
	class Unordered_set
	{
		struct SetKeyOfT
		{
			int operator()(const K& key)
			{
				return key;
			}
		};

	public:
		typedef typename OpenHashTable::HashTable<K, K, SetKeyOfT>::iterator iterator;

		pair<iterator, bool> insert(const K key)
		{
			return _ht.Insert(key);
		}

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

	private:
		OpenHashTable::HashTable<K, K, SetKeyOfT> _ht;
	};
}