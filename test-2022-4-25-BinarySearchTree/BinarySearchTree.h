#pragma once
#ifndef __BINARYSEACHTREE_H__
#define __BINARYSEACHTREE_H__
#include <iostream>
//搜索二叉树K模型
namespace K
{
	template <class K>
	struct BSTreeNode
	{
		BSTreeNode<K>* _left;
		BSTreeNode<K>* _right;
		K _key;

		BSTreeNode(const K& key = 0)
			:_left(nullptr)
			,_right(nullptr)
			,_key(key)
		{}
	};

	template<class K>
	class BSTree
	{
		typedef BSTreeNode<K> Node;
	private:
		BSTreeNode<K>* _root;

		void _Destroy(Node* root)
		{
			if (nullptr == root)
			{
				return;
			}

			_Destroy(root->_left);
			_Destroy(root->_right);

			delete root;
		}

		Node* _Copy(Node* root)
		{
			if (nullptr == root)
			{
				return nullptr;
			}

			Node* copyNode = new Node(root->_key);
			copyNode->_left = _Copy(root->_left);
			copyNode->_right = _Copy(root->_right);

			return copyNode;
		}

	public:
		//默认构造
		BSTree()
			:_root(nullptr)
		{}

		//拷贝构造
		BSTree(const BSTree<K>& t)
		{
			_root = _Copy(t._root);
		}

		//复制重载
		BSTree<K>& operator=(BSTree<K> t)
		{
			std::swap(_root, t._root);

			return *this;
		}

		//清空
		void Destroy(void)
		{
			_Destroy(_root);
		}

		~BSTree()
		{
			Destroy();
			_root = nullptr;
		}

		bool Insert(const K& key)
		{
			if (nullptr == _root)
			{
				_root = new Node(key);

				return true;
			}
			else
			{
				Node* cur = _root;
				Node* parent = nullptr;
				//找到合适的空节点
				while (nullptr != cur)
				{
					if (cur->_key < key)
					{
						parent = cur;
						cur = cur->_right;
					}
					else if (cur->_key > key)
					{
						parent = cur;
						cur = cur->_left;
					}
					else
					{
						return false;
					}
				}

				//插入节点
				cur = new Node(key);
				//确定是左孩子还是右孩子
				if (parent->_key > key)
				{
					parent->_left = cur;
				}
				else
				{
					parent->_right = cur;
				}

				return true;
			}
		}

		bool Erase(const K& key)
		{
			Node* cur = _root;
			Node* parent = nullptr;

			//先找要删节点
			while (nullptr != cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				//找到了，开始执行删除操作一共分两种大情况
				//1、要删节点只有一个孩子或没有孩子
				//2、要删节点有两个孩子
				else
				{
					if (nullptr == cur->_right)
					{
						//确定要删节点是否为根节点
						if (cur == _root)
						{
							_root = cur->_left;
						}
						else
						{
							//确定要删节点是那个孩子
							if (parent->_left == cur)
							{
								parent->_left = cur->_left;
							}
							else
							{
								parent->_right = cur->_left;
							}
						}

						delete cur;

						return true;
					}//if ((nullptr == cur->_right)end......
					else if (nullptr == cur->_left)
					{
						//确定要删节点是否为根节点
						if (cur == _root)
						{
							_root = cur->_right;
						}
						else
						{
							//确定要删节点是那个孩子
							if (parent->_left == cur)
							{
								parent->_left = cur->_right;
							}
							else
							{
								parent->_right = cur->_right;
							}
						}

						delete cur;

						return true;
					}//else if (nullptr == cur->_left)end......
					else
					{
						Node* maxParent = cur;
						Node* maxLeft = cur->_left;

						//找到左边最大
						while (nullptr != maxLeft->_right)
						{
							maxParent = maxLeft;
							maxLeft = maxLeft->_right;
						}

						//替换数据
						cur->_key = maxLeft->_key;

						//替换节点
						if (maxParent->_left == maxLeft)
						{
							maxParent->_left = maxLeft->_left;
						}
						else
						{
							maxParent->_right = maxLeft->_left;
						}

						delete maxLeft;

						return true;
					}//else end.......
				}//else end......

			}//while (nullptr != cur) end......

			return false;
		}

		Node* Find(const K& key)
		{
			Node* cur = _root;

			while (nullptr != cur)
			{
				if (cur->_key > key)
				{
					cur = cur->_left;
				}
				else if (cur->_key < key)
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

		void _InOrder(Node* root)
		{
			if (nullptr == root)
			{
				return;
			}

			_InOrder(root->_left);
			std::cout << root->_key << " ";
			_InOrder(root->_right);
		}

		void InOrder(void)
		{
			_InOrder(_root);
			std::cout << std::endl;
		}
	};
}


#endif