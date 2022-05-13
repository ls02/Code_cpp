#pragma once
#ifndef __RBTREE_H__
#define __RBTREE_H__
#include <iostream>
#include <utility>
#include <algorithm>

namespace ls
{
	enum color
	{
		RED,
		BLACK
	};

	template<class K, class V>
	struct RBTreeNode
	{
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

		void RotateL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;

			parent->_right = subRL;
			if (subRL)
			{
				subRL->_parent = parent;
			}

			subR->_left = parent;
			Node* parentParent = parent->_parent;
			parent->_parent = subR;

			if (parent == _root)
			{
				_root = subR;
				_root->_parent = nullptr;
			}
			else
			{
				if (parentParent->_left == parent)
				{
					parentParent->_left = subR;
				}
				else
				{
					parentParent->_right = subR;
				}
				subR->_parent = parentParent;
			}
		}

		void RotateR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			parent->_left = subLR;
			if (subLR)
				subLR->_parent = parent;

			subL->_right = parent;
			Node* parentParent = parent->_parent;
			parent->_parent = subL;

			if (parent == _root)
			{
				_root = subL;
				_root->_parent = nullptr;
			}
			else
			{
				if (parentParent->_left == parent)
					parentParent->_left = subL;
				else
					parentParent->_right = subL;

				subL->_parent = parentParent;
			}
		}

		void _Inorder(Node* root)
		{
			if (nullptr == root)
			{
				return;
			}

			_Inorder(root->_left);

			std::cout << root->_kv.first << "：" << root->_kv.second << std::endl;
			_Inorder(root->_right);
		}

		bool _IsRBTree(Node* root, int blackCount, int count)
		{
			if (nullptr == root)
			{
				if (count != blackCount)
				{
					std::cout << "黑色节点数量不相等" << std::endl;

					return false;
				}
				return true;
			}

			if (root->_col == RED && root->_parent->_col == RED)
			{
				std::cout << "存在连续的红色节点" << std::endl;

				return false;
			}

			if (root->_col == BLACK)
			{
				count++;
			}

			return _IsRBTree(root->_left, blackCount, count)
				&& _IsRBTree(root->_right, blackCount, count);
		}

		Node* _CopyNode(Node* root)
		{
			if (nullptr == root)
			{
				return nullptr;
			}

			Node* Copy= new Node(root->_kv);

			Copy->_left = _CopyNode(root->_left);
			Copy->_right = _CopyNode(root->_right);

			return Copy;
		}

		void _Destroy(Node* root)
		{
			if (nullptr == root)
			{
				return;
			}

			Node* cur = root;

			_Destroy(root->_left);
			_Destroy(root->_right);

			delete cur;
		}

	public:
		RBTree()
			:_root(nullptr)
		{}

		RBTree(const RBTree<K, V>& t)
		{
			_root = _CopyNode(t._root);
		}

		RBTree<K, V>& operator=(RBTree<K, V> t)
		{
			std::swap(_root, t._root);

			return *this;
		}

		~RBTree(void)
		{
			_Destroy(_root);
			_root = nullptr;
		}

		std::pair<Node*, bool> Insert(std::pair<K, V> kv)
		{
			if (nullptr == _root)
			{
				_root = new Node(kv);
				_root->_col = BLACK;

				return std::make_pair(_root, true);
			}

			Node* cur = _root;
			Node* parent = nullptr;
			while (nullptr != cur)
			{
				if (cur->_kv.first > kv.first)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_kv.first < kv.first)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return std::make_pair(cur, false);
				}
			}

			Node* newNode = new Node(kv);

			if (parent->_kv.first > kv.first)
			{
				parent->_left = newNode;
				newNode->_parent = parent;

			}
			else
			{
				parent->_right = newNode;
				newNode->_parent = parent;
			}

			cur = newNode;

			//变色处理
			while (nullptr != parent && parent->_col == RED)
			{
				Node* grandfather = parent->_parent;

				if (parent == grandfather->_left)
				{
					Node* uncle = grandfather->_right;

					//情况一：叔叔存在且为红
					if (nullptr != uncle && uncle->_col == RED)
					{
						parent->_col = uncle->_col = BLACK;
						grandfather->_col = RED;

						//接着往上处理
						cur = grandfather;
						parent = cur->_parent;
					}
					//情况二：叔叔不存在或叔叔存在且为黑色，说明需要旋转处理
					else
					{
						//右单炫
						if (cur == parent->_left)
						{
							RotateR(grandfather);

							//变色处理
							parent->_col = BLACK;
							grandfather->_col = RED;
						}
						//左右双旋
						else
						{
							RotateL(parent);
							RotateR(grandfather);

							cur->_col = BLACK;
							grandfather->_col = RED;
						}

						break;
					}
				}
				else//parent == grandfather->_right
				{
					Node* uncle = grandfather->_left;
					
					//情况一：叔叔存在且为红
					if (nullptr != uncle && uncle->_col == RED)
					{
						parent->_col = uncle->_col = BLACK;
						grandfather->_col = RED;

						cur = grandfather;
						parent = cur->_parent;
					}
					//情况二和三
					else
					{
						//单旋
						if (cur == parent->_right)
						{
							RotateL(grandfather);
							parent->_col = BLACK;
							grandfather->_col = RED;
						}
						//双旋
						else
						{
							RotateR(parent);
							RotateL(grandfather);

							cur->_col = BLACK;
							grandfather->_col = RED;
						}

						break;
					}
				}//parent == grandfather->_right end....
			}//nullptr != parent || parent->_col == RED end...

			_root->_col = BLACK;

			return std::make_pair(newNode, true);
		}

		Node* Find(const K& key)
		{
			Node* cur = _root;

			while (nullptr != cur)
			{
				if (cur->_kv.first > key)
				{
					cur = cur->_left;
				}
				else if (cur->_kv.first < key)
				{
					cur = cur->_right;
				}
				else
				{
					return cur;
				}
			}

			return nullptr;
		}

		bool IsRBTree(void)
		{
			if (nullptr == _root)
			{
				return true;
			}

			if (_root->_col == RED)
			{
				std::cout << "根节点为红色" << std::endl;

				return false;
			}

			Node* left = _root;
			int blackCount = 0;
			while (nullptr != left)
			{
				if (left->_col == BLACK)
				{
					blackCount++;
				}

				left = left->_left;
			}

			int count = 0;

			return _IsRBTree(_root, blackCount, count);
		}

		void Inorder(void)
		{
			_Inorder(_root);
		}
	};
}


#endif