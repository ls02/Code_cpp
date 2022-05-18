#pragma once
#ifndef __UNORDERED_SET_H__
#define __UNORDERED_SET_H__
#include "HashTable.h"

namespace ls
{
	template<class K>
	class unordered_set
	{
		struct SetKeyOfT
		{
			size_t operator()(const K& key)
			{
				return key;
			}
		};
	private:
		HashTable<K, K, SetKeyOfT> _ht;

	public:
		typedef typename HashTable<K, K, SetKeyOfT>::iterator iterator;

		std::pair<iterator, bool> Insert(const K& k)
		{
			return _ht.Insert(k);
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