#pragma once
#include <iostream>
#include "Iterator.h"

using std::pair;
using std::make_pair;
using std::cout;
using std::endl;

enum colour
{
	RED,
	BLACK
};

template <class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	
	T _data;

	colour _col;

	RBTreeNode(const T& data)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_data(data)
		,_col(RED)
	{}
};

template <class T, class Ref, class Ptr>
struct __TreeIterator
{
	typedef Ref reference;
	typedef Ptr pointer;

	typedef RBTreeNode<T> Node;
	typedef __TreeIterator<T, Ref, Ptr> Self;

	Node* _node;

	__TreeIterator(Node* node)
		:_node(node)
	{}

	bool operator!=(const Self& s)const
	{
		return _node != s._node;
	}

	bool operator==(const Self& s)const
	{
		return _node == s._node;
	}


	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &_node->_data;
	}

	Self& operator++()
	{
		//如果当前位置++的话说明左边是去过，或者为空的。
		//那么我们只需要给他右子树的最左节点那么就是它的中序的下一个
		Node* left = _node->_right;

		if (nullptr != left)
		{
			//如果我的左边为空，那么我就是最左节点
			while (nullptr != left->_left)
			{
				left = left->_left;
			}

			_node = left;
		}
		else
		{
			//如果_node的右为空说明_node的所有节点访问完了
			//我们需要往上找，而cur在parent的右边的话，就要继续往上找他们的公共祖先
			//如果不为parent的右的话说明，parent->_parent就是我们要找的下一个节点

			Node* cur = _node;
			Node* parent = cur->_parent;

			while (nullptr != parent && parent->_right == cur)
			{
				cur = parent;
				parent = parent->_parent;
			}

			_node = parent;
		}

		return *this;
	}

	Self operator++(int)
	{
		//如果当前位置++的话说明左边是去过，或者为空的。
		//那么我们只需要给他右子树的最左节点那么就是它的中序的下一个
		Node* temp = _node;
		Node* left = _node->_right;

		if (nullptr != left)
		{
			//如果我的左边为空，那么我就是最左节点
			while (nullptr != left->_left)
			{
				left = left->_left;
			}

			_node = left;
		}
		else
		{
			//如果_node的右为空说明_node的所有节点访问完了
			//我们需要往上找，而cur在parent的右边的话，就要继续往上找他们的公共祖先
			//如果不为parent的右的话说明，parent->_parent就是我们要找的下一个节点

			Node* cur = _node;
			Node* parent = cur->_parent;

			while (nullptr != parent && parent->_right == cur)
			{
				cur = parent;
				parent = parent->_parent;
			}

			_node = parent;
		}

		return temp;
	}

	Self& operator--()
	{
		Node* right = _node->_left;

		//如果不为空，那么它的最右节点就是它的上一个节点
		if (nullptr != right)
		{
			while (nullptr != right->_right)
			{
				right = right->_right;
			}

			_node = right;
		}
		//为空，有两种情况，情况1：cur在左， 情况2：cur在右
		//情况1：需要找到它的公共祖先，公共祖先就是它上一个节点
		//情况2：父节点就是它上一个节点
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;

			while (nullptr != parent && parent->_left == cur)
			{
				cur = parent;
				parent = parent->_parent;
			}

			_node = parent;
		}
		
		return *this;
	}

	Self operator--(int)
	{
		Node* right = _node->_left;
		Node* temp = _node;

		//如果不为空，那么它的最右节点就是它的上一个节点
		if (nullptr != right)
		{
			while (nullptr != right->_right)
			{
				right = right->_right;
			}

			_node = right;
		}
		//为空，有两种情况，情况1：cur在左， 情况2：cur在右
		//情况1：需要找到它的公共祖先，公共祖先就是它上一个节点
		//情况2：父节点就是它上一个节点
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;

			while (nullptr != parent && parent->_left == cur)
			{
				cur = parent;
				parent = parent->_parent;
			}

			_node = parent;
		}

		return temp;
	}
};

template <class K, class T, class KeyOfT>
class RBTree
{
	typedef RBTreeNode<T> Node;
private:
	Node* _root;

	bool _CheckBlance(Node* root,int count, int blackNum)
	{
		if (nullptr == root)
		{
			if (count != blackNum)
			{
				cout << "黑色节点不相等!" << endl;

				return false;
			}

			return true;
		}

		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout << "存在连续的红色节点！" << endl;

			return false;
		}

		if (root->_col == BLACK)
		{
			count++;
		}

		return _CheckBlance(root->_left, count, blackNum)
			&& _CheckBlance(root->_right, count, blackNum);
	}

	Node* _Copy(const Node* root)
	{
		if (nullptr == root)
		{
			return nullptr;
		}

		Node* copyNode = new Node(root->_data);

		copyNode->_left = _Copy(root->_left);
		copyNode->_right = _Copy(root->_right);

		if (nullptr != copyNode->_left)
		{
			copyNode->_left->_parent = copyNode;
		}

		if (nullptr != copyNode->_right)
		{
			copyNode->_right->_parent = copyNode;
		}

		return copyNode;
	}
public:
	typedef __TreeIterator<T, T&, T*> iterator;
	typedef __TreeIterator<T, const T&, const T*> const_iterator;
	typedef ReverseIterator<iterator> reverse_iterator;
	
	reverse_iterator rbegin()
	{
		Node* right = _root;

		while (nullptr != right && nullptr != right->_right)
		{
			right = right->_right;
		}

		return reverse_iterator(iterator(right));
	}

	reverse_iterator rbegin()const
	{
		Node* right = _root;

		while (nullptr != right && nullptr != right->_right)
		{
			right = right->_right;
		}

		return reverse_iterator(iterator(right));
	}

	reverse_iterator rend()
	{
		return reverse_iterator(iterator(nullptr));
	}

	reverse_iterator rend()const
	{
		return reverse_iterator(iterator(nullptr));
	}

	iterator begin()
	{
		Node* left = _root;

		while (nullptr != left && nullptr != left->_left)
		{
			left = left->_left;
		}

		return iterator(left);
	}

	iterator begin()const
	{
		Node* left = _root;

		while (nullptr != left && nullptr != left->_left)
		{
			left = left->_left;
		}

		return iterator(left);
	}


	iterator end()
	{
		return iterator(nullptr);
	}

	iterator end()const
	{
		return iterator(nullptr);
	}

	RBTree()
		:_root(nullptr)
	{}

	//此版本的拷贝构造才是正确的，其它版本的拷贝构造有问题，主要问题是父节点没更新
	RBTree(const RBTree<K, T, KeyOfT>& k)
	{
		_root = _Copy(k._root);
	}

	~RBTree()
	{
		Destroy(_root);
		_root = nullptr;
	}

	RBTree<K, T, KeyOfT>& operator=(RBTree<K, T, KeyOfT> k)
	{
		std::swap(_root, k._root);

		return *this;
	}

	void Destroy(Node* root)
	{
		if (nullptr == root)
		{
			return;
		}

		Destroy(root->_left);
		Destroy(root->_right);

		delete root;
	}

	pair<iterator, bool> Insert(const T& data)
	{
		if (nullptr == _root)
		{
			_root = new Node(data);
			_root->_col = BLACK;

			return make_pair(iterator(_root), true);
		}

		Node* cur = _root;
		Node* parent = nullptr;
		KeyOfT kot;

		//找叶子节点
		while (nullptr != cur)
		{
			if (kot(cur->_data) > kot(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (kot(cur->_data) < kot(data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return make_pair(iterator(cur), false);
			}
		}

		Node* newNode = new Node(data);
		cur = newNode;

		if (kot(parent->_data) > kot(data))
		{
			parent->_left = newNode;
			newNode->_parent = parent;
		}
		else
		{
			parent->_right = newNode;
			newNode->_parent = parent;
		}

		while (nullptr != parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;

			//处理左子树
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;

				//情况1：叔叔存在且为红
				if (nullptr != uncle && uncle->_col == RED)
				{
					//我们对叔叔和父节点进行变黑处理
					uncle->_col = parent->_col = BLACK;
					//对祖父进行变红处理
					grandfather->_col = RED;

					//处理完继续处理上面的祖父节点
					cur = grandfather;
					parent = cur->_parent;
				}
				else//情况2+情况3,uncle存在且为黑，或uncle不存在
				{
					//右单旋
					if (cur == parent->_left)
					{
						RotateR(grandfather);

						grandfather->_col = RED;
						parent->_col = BLACK;
					}
					else//左右双旋
					{
						RotateL(parent);
						RotateR(grandfather);

						grandfather->_col = RED;
						cur->_col = BLACK;
					}

					//旋转完了就不用处理了直接结束插入
					break;
				}
			}
			else//处理右子树
			{
				Node* uncle = grandfather->_left;

				//情况1：叔叔存在且为红
				if (nullptr != uncle && uncle->_col == RED)
				{
					//同辈变黑
					uncle->_col = parent->_col = BLACK;
					//祖父变红
					grandfather->_col = RED;

					//继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//左旋
					if (parent->_right == cur)
					{
						RotateL(grandfather);

						grandfather->_col = RED;
						parent->_col = BLACK;
					}
					//右左双旋
					else
					{
						RotateR(parent);
						RotateL(grandfather);

						grandfather->_col = RED;
						cur->_col = BLACK;
					}

					//旋转完了就不用处理了直接结束插入
					break;
				}
			}

		}

		_root->_col = BLACK;

		return make_pair(iterator(newNode), true);
	}

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

	bool CheckBlance()
	{
		if (nullptr == _root)
		{
			return true;
		}

		if (_root->_col == RED)
		{
			cout << "根节点为红色！" << endl;

			return false;
		}

		int blackNum = 0;
		int count = 0;
		Node* left = _root;

		while (nullptr != left)
		{
			if (left->_col == BLACK)
			{
				blackNum++;
			}
			
			left = left->_left;
		}

		return _CheckBlance(_root, count, blackNum);
	}

	Node* Find(const K& key)
	{
		KeyOfT kot;

		Node* cur = _root;

		while (nullptr != cur)
		{
			if (kot(cur->_data) > kot(key))
			{
				cur = cur->_left;
			}
			else if (kot(cur->_data) < kot(key))
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
};