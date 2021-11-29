#pragma once
#include "RBTree.h"

namespace ls
{
	template <class K, class V>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<const K, V>& kv)
			{
				return kv.first;
			}
		};
	private:
		RBTree<K, pair<const K, V>, MapKeyOfT> _t;

	public:
		typedef typename RBTree<K, pair<const K, V>, MapKeyOfT>::iterator iterator;
		typedef typename RBTree<K, pair<const K, V>, MapKeyOfT>::iterator const_iterator;
		typedef typename RBTree<K, pair<const K, V>, MapKeyOfT>::reverse_iterator reverse_iterator;

		bool CheckBlance()
		{
			return _t.CheckBlance();
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = insert(make_pair(key, V()));

			return ret.first->second;
		}

		pair<iterator, bool> insert(const pair<const K, V>& kv)
		{
			return _t.Insert(kv);
		}

		iterator begin()
		{
			return _t.begin();
		}

		iterator begin()const
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		iterator end()const
		{
			return _t.end();
		}

		reverse_iterator rbegin()
		{
			return _t.rbegin();
		}

		reverse_iterator rbegin()const
		{
			return _t.rbegin();
		}

		reverse_iterator rend()
		{
			return _t.rend();
		}

		reverse_iterator rend()const
		{
			return _t.rend();
		}
	};
}