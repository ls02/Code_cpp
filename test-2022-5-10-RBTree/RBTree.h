#pragma once
#ifndef __RBTREE_H__
#define __RBTREE_H__
#include <iostream>
#include <utility>

namespace ls
{
	template<class K, class V>
	struct RBTreeNode
	{
		enum color
		{
			RED,
			BLACK
		};
		RBTreeNode<K, V>* _left;
		RBTreeNode<K, V>* _right;
		RBTreeNode<K, V>* _parent;

		color _col;
		std::pair<K, V> _kv;

		RBTreeNode(std::pair<K, V> kv)
			: _left(nullptr)
			,_right(nullptr)
			,_parent(nullptr)
			,_kv(kv)
			,_col(RED)
		{}
	};

	template<class K, class V>
	class RBTree
	{
	private:
		typedef RBTreeNode<K, V> Node;
		Node* _root;

	public:
		RBTree()
			:_root(nullptr)
		{}

		std::pair<Node*, bool> Insert(std::pair<K, V> kv)
		{
			if (nullptr == _root)
			{
				_root = new Node(kv);

				return std::make_pair(_root, true);
			}


		}
	};
}


#endif