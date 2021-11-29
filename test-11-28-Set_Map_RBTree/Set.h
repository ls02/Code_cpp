#pragma once
#include "RBTree.h"

namespace ls
{
	template <class K, class V>
	class set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	private:
		RBTree<K, K, SetKeyOfT> _t;
	public:
		typedef typename RBTree<K, K, SetKeyOfT>::iterator iterator;
		typedef typename RBTree<K, K, SetKeyOfT>::iterator cosnt_iterator;
		typedef typename RBTree<K, K, SetKeyOfT>::reverse_iterator reverse_iterator;

		bool CheckBlance()
		{
			return _t.CheckBlance();
		}

		pair<iterator, bool> insert(const K& k)
		{
			return _t.Insert(k);
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