#pragma once
#ifndef __RBTREE_H__
#define __RBTREE_H__
#include <iostream>
#include <utility>

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

		void RotatingR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			subL->_right = parent;
			Node* parentParent = parent->_parent;
			parent->_parent = subL;
			parent->_left = subLR;

			if (nullptr != subLR)
			{
				subLR->_parent = parent;
			}

			if (parent == _root)
			{
				_root = subL;
				_root->_parent = nullptr;
			}
			else
			{
				if (parentParent->_left = parent)
				{
					parentParent->_left = subL;
					subL->_parent = parentParent;
				}
				else
				{
					parentParent->_right = subL;
					subL->_parent = parentParent;
				}
			}
		}

		void RotatingL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;

			subR->_left = parent;
			Node* parentParent = parent->_parent;
			parent->_parent = subR;
			parent->_right = subRL;

			if (nullptr !- subRL)
			{
				subRL->_parent = parent;
			}

			if (_root == parent)
			{
				_root = subR;
				_root->_parent = nullptr;
			}
			else
			{
				if (parentParent->_left == parent)
				{
					parentParent->_left = subR;
					subR->_parent = parentParent;
				}
				else
				{
					parentParent->_right = subR;
					subR->_parent = parentParent;
				}
			}
		}

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

			//��ɫ����
			while (nullptr != parent || parent->_col == RED)
			{
				Node* grandfather = parent->_parent;

				if (parent == grandfather->_left)
				{
					Node* uncle = grandfather->_right;

					//���һ�����������Ϊ��
					if (nullptr != uncle && uncle->_col == RED)
					{
						parent->_col = uncle->_col = BLACK;
						grandfather->_col = RED;

						//�������ϴ���
						cur = grandfather;
						grandfather = cur->_parent;
					}
					//����������岻���ڻ����������Ϊ��ɫ��˵����Ҫ��ת����
					else
					{
						//�ҵ���
						if (cur == parent->_left)
						{
							RotatingR(grandfather);

							//��ɫ����
							parent->_col = BLACK;
							grandfather->_col = RED;
						}
						//����˫��
						else
						{
							RotatingL(parent);
							RotatingR(grandfather);

							cur->_col = BLACK;
							grandfather->_col = RED;
						}

						break;
					}
				}
				else//parent == grandfather->_right
				{
					Node* uncle = grandfather->_left;
					
					//���һ�����������Ϊ��
					if (nullptr != uncle && uncle->_col == RED)
					{
						parent->_col = uncle->_col = BLACK;
						grandfather->_col = RED;

						cur = grandfather;
						parent = cur->_parent;
					}
					//���������
					else
					{
						if (cur == parent->_right)
						{

						}
					}
				}
			}
		}
	};
}


#endif