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
		cout << root->_kv.first << "��" << root->_kv.second << endl;
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

		//���״��ڣ�����ɫΪ�����Ҫ����
		while (nullptr != parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;

			//�ؼ�������
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;

				// ���1�����������Ϊ��
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					//�������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
				else//���2+3��uncle�����ڻ�uncle������Ϊ��
				{
					if (cur == parent->_left) 
					{
						//���2������
						RotateR(grandfather);
						grandfather->_col = RED;
						parent->_col = BLACK;
					}
					else//���3��˫��
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

				//���1��
				if (uncle && uncle->_col == RED)
				{
					uncle->_col = parent->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else//���2 + ���3��
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

					//�������
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
				cout << "��ɫ�ڵ�����������" << endl;

				return false;
			}
			return true;
		}

		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout << "���������ĺ�ɫ�ڵ�" << endl;

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
			cout << "���ڵ��Ǻ�ɫ" << endl;
			
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

	//����
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		//�����Ϊ��˵����Ҫ���¸��ڵ�
		if (nullptr != subRL)
		{
			subRL->_parent = parent;
		}

		//����parent�ĸ��ڵ�
		Node* parentParent = parent->_parent;
		//��ת
		subR->_left = parent;
		parent->_parent = subR;

		//�������parent���ڵ�,��ô��ת֮��Ĺ�ϵ�ᷢ�������Ҫ��parentParent��subR�����µĸ��ӹ�ϵ
		//����ȷ����parent����ڵ㻹���ҽڵ�
		if (parent == _root)
		{
			_root = subR;
			_root->_parent = nullptr;
		}
		else
		{
			//ȷ����ǰparent����ڵ㻹���ҽڵ�
			if (parentParent->_left == parent)
			{
				parentParent->_left = subR;
			}
			else
			{
				parentParent->_right = subR;
			}

			//subR�滻�ɵĸ��ڵ�
			subR->_parent = parentParent;
		}
	}

	//�ҵ���
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		//��Ϊ��˵����Ҫ���¸��ڵ�
		if (nullptr != subLR)
		{
			subLR->_parent = parent;
		}

		//����ǰ���ڵ�ָ��
		Node* parentParent = parent->_parent;
		//��ת
		subL->_right = parent;
		parent->_parent = subL;

		//������Ǹ��ڵ�˵����Ҫ����ǰ���ڵ�(parent)����subL��Ϊ�µĸ��ڵ�
		//����ȷ����parent��parentParent����ڵ㻹���ҽڵ�
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

			//subL�滻�ɵĸ��ڵ�
			subL->_parent = parentParent;
		}
	}

	void InOrder()
	{
		_InOrder(_root);
	}
};