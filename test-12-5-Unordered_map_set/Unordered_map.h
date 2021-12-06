#pragma once
#include "OpenHash.h"

namespace ls
{
	template <class K, class V>
	class Unordered_map
	{
		struct MapKeyOfT
		{
			int operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};

	public:
		typedef typename OpenHashTable::HashTable<K, pair<K, V>, MapKeyOfT>::iterator iterator;

		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _ht.Insert(kv);
		}

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		V& operator[](const K key)
		{
			pair<iterator, bool> ret = _ht.Insert(make_pair(key, V()));

			return ret.first->second;
		}

	private:
		OpenHashTable::HashTable<K, pair<K, V>, MapKeyOfT> _ht;
	};
}