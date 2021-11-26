#pragma once
#include <iostream>

using std::endl;
using std::cout;
using std::pair;
using std::make_pair;

enum Colour
{
	RED,
	BLACK,
};

template <class K, class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	pair<K, V> _kv;
	Colour _col;

	RBTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_kv(kv)
		,_col(RED)
	{}
};

template <class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
private:
	Node* _root;

	void _InOrder(Node* root)
	{
		if (nullptr == root)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_kv.first << "：" << root->_kv.second << endl;
		_InOrder(root->_right);
	}


public:
	RBTree()
		:_root(nullptr)
	{}

	void Destory(Node* root)
	{
		if (nullptr == root)
		{
			return;
		}

		Destory(root->_left);
		Destory(root->_right);

		delete root;
	}

	~RBTree()
	{
		Destory(_root);
		_root = nullptr;
	}

	Node* Find(const K& key)
	{
		Node* cur = _root;

		while (cur)
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

	pair<Node*, bool> Insert(const pair<K, V>& kv)
	{
		if (nullptr == _root)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return make_pair(_root, true);
		}

		Node* parent = nullptr;
		Node* cur = _root;

		while (nullptr != cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return make_pair(cur, false);
			}
		}

		Node* newNode= new Node(kv);
		newNode->_col = RED;
		
		if (parent->_kv.first < kv.first)
		{
			parent->_right = newNode;
			newNode->_parent = parent;
		}
		else
		{
			parent->_left = newNode;
			newNode->_parent = parent;
		}

		cur = newNode;

		//父亲存在，且颜色为红就需要处理
		while (nullptr != parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;

			//关键看叔叔
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;

				// 情况1：叔叔存在且为红
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					//继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else//情况2+3：uncle不存在或uncle存在且为黑
				{
					if (cur == parent->_left) 
					{
						//情况2：单旋
						RotateR(grandfather);
						grandfather->_col = RED;
						parent->_col = BLACK;
					}
					else//情况3：双旋
					{
						RotateL(parent);
						RotateR(grandfather);

						cur->_col = BLACK;
						grandfather->_col = RED;
					}

					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;

				//情况1：
				if (uncle && uncle->_col == RED)
				{
					uncle->_col = parent->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else//情况2 + 情况3：
				{
					if (cur == parent->_right)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						RotateR(parent);
						RotateL(grandfather);

						cur->_col = BLACK;
						grandfather->_col = RED;
					}

					//插入结束
					break;
				}
			}
		}

		_root->_col = BLACK;

		return make_pair(newNode, true);
	}

	bool _CheckBlance(Node* root, int blackNum, int count)
	{
		if (nullptr == root)
		{
			if (count != blackNum)
			{
				cout << "黑色节点的数量不相等" << endl;

				return false;
			}
			return true;
		}

		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout << "存在连续的红色节点" << endl;

			return false;
		}

		if (root->_col == BLACK)
		{
			count++;
		}

		return _CheckBlance(root->_left, blackNum, count)
			&& _CheckBlance(root->_right, blackNum, count);
	}

	bool CheckBlance()
	{
		if (nullptr == _root)
		{
			return true;
		}

		if (_root->_col == RED)
		{
			cout << "根节点是红色" << endl;
			
			return false;
		}

		int blackNum = 0;
		Node* left = _root;

		while (nullptr != left)
		{
			if (left->_col == BLACK)
			{
				blackNum++;
			}

			left = left->_left;
		}

		int count = 0;
		return _CheckBlance(_root, blackNum, count);
	}

	//左单旋
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		//如果不为空说明需要更新父节点
		if (nullptr != subRL)
		{
			subRL->_parent = parent;
		}

		//保存parent的父节点
		Node* parentParent = parent->_parent;
		//旋转
		subR->_left = parent;
		parent->_parent = subR;

		//如果不是parent根节点,那么旋转之后的关系会发生变会需要让parentParent和subR建立新的父子关系
		//并且确定出parent是左节点还是右节点
		if (parent == _root)
		{
			_root = subR;
			_root->_parent = nullptr;
		}
		else
		{
			//确定出前parent是左节点还是右节点
			if (parentParent->_left == parent)
			{
				parentParent->_left = subR;
			}
			else
			{
				parentParent->_right = subR;
			}

			//subR替换旧的父节点
			subR->_parent = parentParent;
		}
	}

	//右单旋
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		//不为空说明需要更新父节点
		if (nullptr != subLR)
		{
			subLR->_parent = parent;
		}

		//保存前父节点指针
		Node* parentParent = parent->_parent;
		//旋转
		subL->_right = parent;
		parent->_parent = subL;

		//如果不是根节点说明需要更新前父节点(parent)，让subL成为新的父节点
		//并且确定出parent是parentParent的左节点还是右节点
		if (parent == _root)
		{
			_root = subL;
			_root->_parent = nullptr;
		}
		else
		{
			if (parentParent->_left == parent)
			{
				parentParent->_left = subL;
			}
			else
			{
				parentParent->_right = subL;
			}

			//subL替换旧的父节点
			subL->_parent = parentParent;
		}
	}

	void InOrder()
	{
		_InOrder(_root);
	}
};