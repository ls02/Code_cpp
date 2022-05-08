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

		//ƽ������
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
		//�ҵ���
		void RotateR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			parent->_right = subLR;
			subL->_right = parent;
			parent->_parent = subL;

			if (nullptr != subLR)
			{

			}
		}

		void RotateL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* sbRL = subR->_left;

			parent->_left = subRL;
			subR->_left = parent;
			Node* parentParent = parent->_parent;
			parent->_parent = subR;

			if (nullptr != subRL)
			{
				subRL->_parent = parent;
			}

			if (parent != _root)
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
			else
			{
				_root = subR;
				_root->_parent = nullptr;
			}

			parent->_bf = surR->_bf = 0;
		}
	public:
		AVLTree(void)
			:_root(nullptr)
		{}

		std::pair<Node*, bool> Insert(const std::pair<K, V>& kv)
		{
			if (nullptr == _root)
			{
				_root = new Node(kv);

				return std::make_pair(_root, true);
			}

			Node* cur = _root;
			Node* parent = nullptr;
			//�ҵ�Ҫ����λ��
			while (nullptr != cur)
			{
				parent = cur;
				if (cur->_kv.first > kv.first)
				{
					cur = cur->_left;
				}
				else if (cur->_kv.first < kv.first)
				{
					cur = cur->_right;
				}
				else
				{
					return std::make_pair(cur, false);
				}
			}

			cur = new Node(kv);
			Node* newNode = cur;
			//�����½ڵ�
			if (parent->_kv.first > kv.first)
			{
				parent->_left = cur;
				cur->_parent = parent;
			}
			else
			{
				parent->_right = cur;
				cur->_parent = parent;
			}

			//����ƽ������
			while (cur != _root)	
			{
				if (parent->_left == cur)
				{
					parent->_bf--;
				}
				else
				{
					parent->_bf++;
				}

				//��ǰƽ�����Ӳ���Ӱ�쵽�������Բ��ü������ϸ�����
				if (!parent->_bf)
				{
					break;
				}
				//��Ҫ�������Ƚڵ��ƽ������
				else if (parent->_bf == -1 || parent->_bf == 1)
				{
					cur = parent;
					parent = parent->_parent;
				}
				//˵���Ѿ�����ƽ�����ˣ���Ҫ��ת�����ƽ��
				else if (parent->_bf == -2 || parent->_bf == 2)
				{
					if (parent->_bf == -2)
					{
						//�ҵ���
						if (cur->_bf == -1)
						{
							RotateR(parent);
						}
						//��������ҵ�����˵��������˫��
						else//cur->_bf == 1
						{

						}
					}
					else//parent->_bf == 2
					{
						//����
						if (cur->_bf == 1)
						{
							RotateL(parent);
						}
						//������������Ǿ���������
						else//cur->_bf == -1
						{
							RotateRL(parent);
						}
					}
				}//else if (parent->_bf == -2 || parent->_bf == 2) end...
				else
				{
					assert(false);
				}
			}//while (cur != _root) end...

			return std::make_pair(newNode, true);
		}
	};
}

#endif // !__AVLTREE_H__
