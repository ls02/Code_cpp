#pragma once
#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;
using std::pair;
using std::make_pair;

template <class K, class V>
struct AVLTreeNode
{
	AVLTreeNode* _left;
	AVLTreeNode* _right;
	AVLTreeNode* _parent;

	//平衡因子
	int _bf;

	pair<K, V> _kv;

	AVLTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_bf(0)
		,_kv(kv)
	{}
};

template <class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
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

	int _Height(Node* root)
	{
		if (nullptr == root)
		{
			return 0;
		}

		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);

		return rightHeight > leftHeight ? rightHeight + 1 : leftHeight + 1;
	}

	bool _IsBalance(Node* root)
	{
		if (nullptr == root)
		{
			return true;
		}

		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);


		//右子树与左子树差不和平衡因子相等说明这颗树已经不是平衡二叉树了
		if (rightHeight - leftHeight != root->_bf)
		{
			cout << "平衡因子异常！" << endl;

			return false;
		}

		return rightHeight - leftHeight < 2
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);
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

	Node* _Copy(const Node* root)
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
	AVLTree()
		:_root(nullptr)
	{}

	AVLTree(const AVLTree<K, V>& kv)
	{
		_root = _Copy(kv._root);
	}

	~AVLTree()
	{
		_Destory(_root);
		_root = nullptr;
	}

	AVLTree<K, V>& operator=(AVLTree<K, V> kv)
	{
		std::swap(_root, kv._root);

		return *this;
	}

	V& operator[](const K& key)
	{
		pair<Node*, bool> ret = Insert(make_pair(key, V()));

		return ret.first->_kv.second;
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

	pair<Node*, bool> Insert(const pair<K, V>& kv)
	{
		//空树
		if (nullptr == _root)
		{

			_root = new Node(kv);

			return make_pair(_root, true);
		}

		Node* cur = _root;
		Node* parent = nullptr;

		//找合适的位置
		while (cur != nullptr)
		{
			//根据平衡树的规则来找到合适的空节点
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
			else //说明有在这类节点不支持插入，但会返回当前节点的位置
			{
				return make_pair(cur, true);
			}
		}

		cur = new Node(kv);
		//记录新节点
		Node* newNode = cur;

		//在合适的位置插入cur
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		//更新因子
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

			//如果为0说明正常
			if (!parent->_bf)
			{
				break;
			}
			//如果不是0，那么这些数值会影响到它的父节点，所以要对他的父节点进行++或--
			else if (1 == parent->_bf || -1 == parent->_bf)
			{
				cur = parent;
				parent = parent->_parent;
			}
			//当父节点等于2或-2说明这已经不是平衡树了
			//为了保证它符合平衡树的规则，我们在这里对它进行旋转处理
			else if (2 == parent->_bf || -2 == parent->_bf)
			{
				//如果是2那么就进行左旋
				if (2 == parent->_bf)
				{
					//cur是-1说明是右左双旋
					if (-1 == cur->_bf)
					{
						RotateRL(parent);
					}
					//左单旋
					else
					{
						RotateL(parent);
					}
				}
				else
				{
					//cur是1说明是左右双旋
					if (1 == cur->_bf)
					{
						RotateLR(parent);
					}
					//右单旋
					else
					{
						RotateR(parent);
					}
				}

				//旋转完了，直接跳出
				break;
			}
			else
			{
				//正常情况走不到这，走到这说明你这已经不是平衡树了
				assert(false);
			}
		}

		return make_pair(newNode, true);
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

		//因为已经完成旋转了，已经平衡了，所以平衡因子恢复正常
		subR->_bf = parent->_bf = 0;
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

		//因子更新为0
		subL->_bf = parent->_bf = 0;
	}

	//左右双旋
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		// 平衡因子调节
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

	//右左双旋
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
		else //不可能走到这，走到这说明你已经不是平衡二叉树了
		{
			assert(false);
		}
	}

	//中序遍历
	void InOrder()
	{
		_InOrder(_root);
	}

	bool IsAVLTree()
	{
		return _IsBalance(_root);
	}
};
