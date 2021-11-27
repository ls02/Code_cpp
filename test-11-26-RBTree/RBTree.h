#pragma once
#include <iostream>

using std::cout;
using std::endl;
using std::pair;
using std::make_pair;

enum colour
{
	BLACK,
	RED
};

template <class K, class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	
	pair<K, V> _kv;
	colour _col;

	RBTreeNode(const pair<K, V> kv)
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

	void _Destory(Node*& root)
	{
		if (nullptr == root)
		{
			return;
		}

		_Destory(root->_left);
		_Destory(root->_right);

		delete root;
	}

	bool _CheckBlance(Node* root, int blackNum, int count)
	{
		if (nullptr == root)
		{
			if (blackNum != count)
			{
				cout << "黑色节点的数量不相等！" << endl;

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

		return _CheckBlance(root->_left, blackNum, count)
			&& _CheckBlance(root->_right, blackNum, count);
	}

	Node* _Copy(Node* root)
	{
		if (nullptr == root)
		{
			return nullptr;
		}

		Node* copyNode = new Node(root->_kv);
		copyNode->_left = _Copy(root->_left);
		copyNode->_right = _Copy(root->_right);

		return copyNode;
	}

public:
	RBTree()
		:_root(nullptr)
	{}

	RBTree(RBTree<K, V>& root)
	{
		_root = Copy(root._root);
	}

	RBTree<K, V>& operator=(RBTree<K, V> root)
	{
		std::swap(_root, root._root);

		return *this;
	}

	V& operator[](const K& key)
	{
		pair<Node*, bool> ret = Insert(make_pair(key, V()));

		return ret.first->_kv.second;
	}

	~RBTree()
	{
		Destroy(_root);

		_root = nullptr;
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

	void Destroy(Node*& root)
	{
		return _Destory(root);
	}


	Node* Copy(Node*& root)
	{
		return _Copy(root);
	}

	pair<Node*, bool> Insert(const pair<K, V> kv)
	{
		if (nullptr == _root)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			_root->_parent = nullptr;

			return make_pair(_root, true);
		}

		Node* cur = _root;
		Node* parent = nullptr;

		//找到叶子
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
				//有相同值不支持插入，返回当前节点
				return make_pair(cur, false);
			}
		}

		Node* newNode = new Node(kv);
		newNode->_col = RED;

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

		//如果父节点不为空且为红色说明这个父节点还需要处理
		while (nullptr != parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;

			if (parent->_col == RED && grandfather != nullptr)
			{
				Node* uncle = nullptr;

				//处理root的左子树
				if (grandfather->_left == parent)
				{
					uncle = grandfather->_right;

					//情况1：有叔叔且为红，我们进行变色处理，把u和p变为黑色，g变为红色。
					//如果g是root变红也没关系，插入结束会对root进行变黑处理
					//这样操作的结果就是树的节点是一黑一红
					if (nullptr != uncle && uncle->_col == RED)
					{
						uncle->_col = parent->_col = BLACK;
						grandfather->_col = RED;

						//接着往上处理，直到所有节点都符合规则
						cur = grandfather;
						parent = cur->_parent;
					}
					//情况2：有叔叔且为黑
					//情况3：无叔叔
					//不管是情况2或者情况3我们只需要确定cur是左子树还是右子树
					//是左子树就单旋，是右子树就双旋
					else
					{
						if (parent->_left == cur)
						{
							//右单旋
							RotateR(grandfather);
							grandfather->_col = RED;
							parent->_col = BLACK;
						}
						else //左右双旋
						{
							RotateL(parent);
							RotateR(grandfather);
							grandfather->_col = RED;
							cur->_col = BLACK;
						}

						break;
					}
				}
				//处理root的右子树
				else
				{
					uncle = grandfather->_left;

					//情况1：有叔叔且为红
					if (nullptr != uncle && uncle->_col == RED)
					{
						uncle->_col = parent->_col = BLACK;
						grandfather->_col = RED;

						//接着往上处理，直到所有节点都符合规则
						cur = grandfather;
						parent = cur->_parent;
					}
					else
					{
						//情况2：有叔叔且为黑
						//情况3：没叔叔
						//这时候只需要确定新增节点在左还是右
						//在右就是左单旋
						//在左就是右左双旋

						//左单旋
						if (parent->_right == cur)
						{
							RotateL(grandfather);
							grandfather->_col = RED;
							parent->_col = BLACK;
						}
						else//右左双旋
						{
							RotateR(parent);
							RotateL(grandfather);

							grandfather->_col = RED;
							cur->_col = BLACK;
						}

						break;
					}
				}
			}
			else
			{
				//父节点不为红无需处理，因为它的新子节点默认为红
				//新节点的父节点不为红，满足条件跳出循环
				//如果为红它的孩子必须是黑，这样就会破话结构
				break;
			}
		}

		//防止根节点被变成红色，如果根节点是红色那么会打破红黑树的规则，这个树就不是红黑树了
		_root->_col = BLACK;

		return make_pair(newNode, true);
	}

	//左单旋
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;

		//如果不为空需要更新父节点
		if (nullptr != subRL)
		{
			subRL->_parent = parent;
		}

		Node* parentParent = parent->_parent;

		//检查parent是否为根节点
		if (parent == _root)
		{
			subR->_left = parent;
			parent->_parent = subR;
			subR->_parent = nullptr;
			_root = subR;
		}
		else
		{
			//保存父节点
			parentParent = parent->_parent;
			subR->_left = parent;
			parent->_parent = subR;
			subR->_parent = parentParent;

			//检查parnet是parentParent的左子树还是右子树
			if (parentParent->_left == parent)
			{
				parentParent->_left = subR;
			}
			else
			{
				parentParent->_right = subR;
			}
		}
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		//不为空需要更新下subLR的父节点
		if (nullptr != subLR)
		{
			subLR->_parent = parent;
		}

		Node* parentParent = nullptr;
		
		//检查parent是否为根节点
		//如果是根，那么就不需要保存它的父
		if (parent == _root)
		{
			subL->_right = parent;
			parent->_parent = subL;
			subL->_parent = nullptr;
			_root = subL;
		}
		else
		{
			parentParent = parent->_parent;
			subL->_right = parent;
			parent->_parent = subL;
			subL->_parent = parentParent;

			//找出parent是panretParent的左子树还是右子树
			if (parentParent->_left == parent)
			{
				parentParent->_left = subL;
			}
			else
			{
				parentParent->_right = subL;
			}
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
			cout << "根节点是红色！" << endl;
		}

		Node* left = _root;
		int blackNum = 0;

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

	void InOrder()
	{
		_InOrder(_root);
	}
};