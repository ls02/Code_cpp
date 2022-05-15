#pragma once
#ifndef __MAP_H__
#define __MAP_H__
#include "RBTree.h"
#include "Iterator.h"
namespace ls
{
	template <class K, class V>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const std::pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	private:
		RBTree<K, std::pair<const K, V>, MapKeyOfT> _t;

	public:
		typedef typename RBTree<K, std::pair<const K, V>, MapKeyOfT>::iterator iterator;
		typedef typename RBTree<K, std::pair<const K, V>, MapKeyOfT>::reverse_iterator reverse_iterator;

		reverse_iterator rbegin(void)
		{
			return _t.rbegin();
		}

		reverse_iterator rend(void)
		{
			return _t.rend();
		}

		iterator begin(void)
		{
			return _t.begin();
		}

		iterator end(void)
		{
			return _t.end();
		}

		std::pair<iterator, bool> Insert(const std::pair<const K, V>& kv)
		{
			return _t.Insert(kv);
		}

		V& operator[](const K& key)
		{
			std::pair<iterator, bool> ret = Insert(std::make_pair(key, V()));

			return ret.first->second;
		}
	};
}


#endif