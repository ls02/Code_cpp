#pragma once
#ifndef __AVLTREE_H__
#define __AVLTREE_T__

#include <iostream>
#include <assert.h>
#include <utility>

namespace ls
{
	template<class K, class V>
	struct AVLTreeNode
	{
		AVLTreeNode<K, V>* _left;
		AVLTreeNode<K, V>* _right;
		AVLTreeNode<K, V>* _parent;

		std::pair<K, V> _kv;

		//Æ½ºâÒò×Ó
		int _bf;

		AVLTreeNode(const std::pair<K, V>& kv)
			:_kv(kv)
			,_left(nullptr)
			,_right(nullptr)
			,_bf(0)
		{}
	};

	template<class K, class V>
	class AVLTree
	{
		typedef AVLTreeNode<K, V> Node;
	private:
		Node* _root;
	public:
		AVLTree(void)
			:_root(nullptr)
		{}

		Node* Insert(const std::pair<K, V>& kv)
		{
			if (nullptr == _root)
			{
				_root = new Node(kv);

				return _root;
			}

			Node* cur = _root;
			while (nullptr != cur)
			{

			}
		}
	};
}

#endif // !__AVLTREE_H__
