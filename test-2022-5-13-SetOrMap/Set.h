#pragma once
#ifndef __SET_H__
#define __SET_H__
#include "RBTree.h"
#include "Iterator.h"

namespace ls
{
	template <class K>
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

		typedef typename RBTree<K, K, SetKeyOfT>::reverse_iterator reverse_iterator;

		reverse_iterator rbegin()
		{
			return _t.rbegin();
		}

		reverse_iterator rend()
		{
			return _t.rend();
		}


		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		std::pair<iterator, bool> Insert(const K& k)
		{
			return _t.Insert(k);
		}
	};
}

#endif