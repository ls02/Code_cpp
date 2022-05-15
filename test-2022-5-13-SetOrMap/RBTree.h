#pragma once
#ifndef __RBTREE_H__
#define __RBTREE_H__
#include <iostream>
#include <utility>
#include <algorithm>
#include "Iterator.h"

namespace ls
{
	enum color
	{
		RED,
		BLACK
	};

	template<class T>
	struct RBTreeNode
	{
		RBTreeNode<T>* _left;
		RBTreeNode<T>* _right;
		RBTreeNode<T>* _parent;

		color _col;
		std::pair<T, T> __data;

		RBTreeNode(const T& data)
			: _left(nullptr)
			, _right(nullptr)
			, _parent(nullptr)
			, __data(data)
			, _col(RED)
		{}
	};

	template <class T, class Ref, class Ptr>
	struct __TreeIterator
	{
		typedef RBTreeNode<T> Node;
		typedef __TreeIterator<T, Ref, Ptr> Self;
		Node* _node;

		__TreeIterator(Node* node)
			:_node(node)
		{}

		Ref operator*(void)
		{
			return _node->__data;
		}

		Ptr operator->(void)
		{
			return &_node->__data;
		}

		bool operator!=(const Self& s) const
		{
			return _node != s._node;
		}

		bool operator==(const Self& s)const
		{
			return _node == s._node;
		}
		Self& operator++()
		{
			if (_node->_right)
			{
				// 下一个访问就是右树中，中序的第一个节点
				Node* left = _node->_right;
				while (left->_left)
				{
					left = left->_left;
				}

				_node = left;
			}
			else
			{
				// 找祖先里面还是不是父亲的右的那个
				// 因为 cur 右为空，说明cur所在的子树已经访问完了
				// cur是parent的右的，说明parent也访问完了，继续往上去找
				Node* cur = _node;
				Node* parent = cur->_parent;
				while (parent && cur == parent->_right)
				{
					cur = cur->_parent;
					parent = parent->_parent;
				}

				_node = parent;
			}

			return *this;
		}

		Self& operator--()
		{
			if (_node->_left)
			{
				// 左子树的最右节点
				Node* right = _node->_left;
				while (right->_right)
				{
					right = right->_right;
				}

				_node = right;
			}
			else
			{
				Node* cur = _node;
				Node* parent = cur->_parent;
				while (parent && cur == parent->_left)
				{
					cur = parent;
					parent = parent->_parent;
				}

				_node = parent;
			}

			return *this;
		}
	};

	template<class K, class T, class KeyOfT>
	class RBTree
	{
		typedef RBTreeNode<T> Node;

	private:
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

			std::cout << root->__data.first << "：" << root->__data.second << std::endl;
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

			Node* Copy = new Node(root->__data);

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

		typedef __TreeIterator < T, T&, T* > iterator;
		typedef __TreeIterator < T, const T&, const T* > const_iterator;
		typedef ReverseIterator<iterator> reverse_iterator;

		reverse_iterator rbegin()
		{
			Node* right = _root;
			while (right && right->_right)
			{
				right = right->_right;
			}
			return reverse_iterator(iterator(right));
		}

		reverse_iterator rend()
		{
			return reverse_iterator(iterator(nullptr));
		}

		iterator begin()
		{
			Node* left = _root;
			while (left && left->_left)
			{
				left = left->_left;
			}

			return iterator(left);
		}

		iterator end()
		{
			return iterator(nullptr);
		}

		RBTree()
			:_root(nullptr)
		{}

		RBTree(const RBTree<K, T, KeyOfT>& t)
		{
			_root = _CopyNode(t._root);
		}

		RBTree<K, T, KeyOfT>& operator=(RBTree<K, T, KeyOfT> t)
		{
			std::swap(_root, t._root);

			return *this;
		}

		~RBTree(void)
		{
			_Destroy(_root);
			_root = nullptr;
		}

		std::pair<iterator, bool> Insert(const T& data)
		{
			if (nullptr == _root)
			{
				_root = new Node(data);
				_root->_col = BLACK;

				return std::make_pair(iterator(_root), true);
			}

			Node* cur = _root;
			Node* parent = nullptr;
			while (nullptr != cur)
			{
				if (KeyOfT(cur->__data) > data)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (KeyOfT(cur->__data) < data)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return std::make_pair(iterator(cur), false);
				}
			}

			Node* newNode = new Node(data);

			if (KeyOfT(parent->__data) > data)
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
				if (KeyOfT(cur->__data) > key)
				{
					cur = cur->_left;
				}
				else if (KeyOfT(cur->__data) < key)
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