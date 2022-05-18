#pragma once
#ifndef __UNORDERED_MAP_H__
#define __UNORDERED_MAP_H__
#include "HashTable.h"

namespace ls
{
	template<class K, class V>
	class unordered_map
	{
		struct MapKeyOfT
		{
			size_t operator()(const std::pair<K, V> kv)
			{
				return kv.first;
			}
		};

	private:
		HashTable<K, std::pair<K, V>, MapKeyOfT> _ht;
	public:
		typedef typename HashTable<K, std::pair<K, V>, MapKeyOfT>::iterator iterator;

		std::pair<iterator, bool> Insert(const std::pair<K, V>& kv)
		{
			return _ht.Insert(kv);
		}

		V& operator[](const K& key)
		{
			std::pair<iterator, bool> ret = _ht.Insert(std::make_pair(key, V()));

			return ret.first->second;
		}

		iterator begin(void)
		{
			return _ht.begin();
		}

		iterator end(void)
		{
			return _ht.end();
		}
	};
}
#endif