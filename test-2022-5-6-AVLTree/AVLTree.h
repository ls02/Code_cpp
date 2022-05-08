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

		//平衡因子
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
		//右单炫
		void RotateR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			parent->_left = subLR;
			subL->_right = parent;
			Node* parentParent = parent->_parent;
			parent->_parent = subL;

			if (nullptr != subLR)
			{
				subLR->_parent = parent;
			}

			if (parent != _root)
			{
				if (parentParent->_left == parent)
				{
					parentParent->_left = subL;
				}
				else
				{
					parentParent->_right = subL;
				}

				subL->_parent = parentParent;
			}
			else
			{
				_root = subL;
				_root->_parent = nullptr;
			}

			subL->_bf = parent->_bf = 0;
		}

		void RotateL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;

			parent->_right = subRL;
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

			parent->_bf = subR->_bf = 0;
		}

		void RotateLR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;
			int bf = parent->_bf;

			RotateL(parent->_left);
			RotateR(parent);

			if (bf == -1)
			{
				subL->_bf = 0;
				parent->_bf = 1;
				subLR->_bf = 0;
			}
			else if (bf == 1)
			{
				parent->_bf = 0;
				subL->_bf = -1;
				subLR->_bf = 0;
			}
			else if (bf == 0)
			{
				parent->_bf = 0;
				subL->_bf = 0;
				subLR->_bf = 0;
			}
			else
			{
				assert(false);
			}
		}

		void RotateRL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;
			int bf = subRL->_bf;

			RotateR(parent->_right);
			RotateL(parent);

			// 平衡因子更新
			if (bf == 1)
			{
				subR->_bf = 0;
				parent->_bf = -1;
				subRL->_bf = 0;
			}
			else if (bf == -1)
			{
				parent->_bf = 0;
				subR->_bf = 1;
				subRL->_bf = 0;
			}
			else if (bf == 0)
			{
				parent->_bf = 0;
				subR->_bf = 0;
				subRL->_bf = 0;
			}
			else
			{
				assert(false);
			}
		}

		void _InOrder(Node* root)
		{
			if (nullptr == root)
			{
				return;
			}

			_InOrder(root->_left);
			std::cout << root->_kv.first << ":" << root->_kv.second << std::endl;
			_InOrder(root->_right);
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
			//找到要插入位置
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
			//插入新节点
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

			//更新平衡因子
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

				//当前平衡因子不会影响到祖先所以不用继续往上更新了
				if (!parent->_bf)
				{
					break;
				}
				//需要更新祖先节点的平衡因子
				else if (parent->_bf == -1 || parent->_bf == 1)
				{
					cur = parent;
					parent = parent->_parent;
				}
				//说明已经不是平衡树了，需要旋转来完成平衡
				else if (parent->_bf == -2 || parent->_bf == 2)
				{
					if (parent->_bf == -2)
					{
						//右单旋
						if (cur->_bf == -1)
						{
							RotateR(parent);
						}
						//如果不是右单旋，说明是左右双旋
						else//cur->_bf == 1
						{
							RotateLR(parent);
						}
					}
					else//parent->_bf == 2
					{
						//左单旋
						if (cur->_bf == 1)
						{
							RotateL(parent);
						}
						//如果不是左单旋那就是右左单旋
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

		void InOrder(void)
		{
			_InOrder(_root);
		}
	};
}

#endif // !__AVLTREE_H__
