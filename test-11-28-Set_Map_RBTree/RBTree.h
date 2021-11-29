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
		//�����ǰλ��++�Ļ�˵�������ȥ��������Ϊ�յġ�
		//��ô����ֻ��Ҫ����������������ڵ���ô���������������һ��
		Node* left = _node->_right;

		if (nullptr != left)
		{
			//����ҵ����Ϊ�գ���ô�Ҿ�������ڵ�
			while (nullptr != left->_left)
			{
				left = left->_left;
			}

			_node = left;
		}
		else
		{
			//���_node����Ϊ��˵��_node�����нڵ��������
			//������Ҫ�����ң���cur��parent���ұߵĻ�����Ҫ�������������ǵĹ�������
			//�����Ϊparent���ҵĻ�˵����parent->_parent��������Ҫ�ҵ���һ���ڵ�

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
		//�����ǰλ��++�Ļ�˵�������ȥ��������Ϊ�յġ�
		//��ô����ֻ��Ҫ����������������ڵ���ô���������������һ��
		Node* temp = _node;
		Node* left = _node->_right;

		if (nullptr != left)
		{
			//����ҵ����Ϊ�գ���ô�Ҿ�������ڵ�
			while (nullptr != left->_left)
			{
				left = left->_left;
			}

			_node = left;
		}
		else
		{
			//���_node����Ϊ��˵��_node�����нڵ��������
			//������Ҫ�����ң���cur��parent���ұߵĻ�����Ҫ�������������ǵĹ�������
			//�����Ϊparent���ҵĻ�˵����parent->_parent��������Ҫ�ҵ���һ���ڵ�

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

		//�����Ϊ�գ���ô�������ҽڵ����������һ���ڵ�
		if (nullptr != right)
		{
			while (nullptr != right->_right)
			{
				right = right->_right;
			}

			_node = right;
		}
		//Ϊ�գ���������������1��cur���� ���2��cur����
		//���1����Ҫ�ҵ����Ĺ������ȣ��������Ⱦ�������һ���ڵ�
		//���2�����ڵ��������һ���ڵ�
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

		//�����Ϊ�գ���ô�������ҽڵ����������һ���ڵ�
		if (nullptr != right)
		{
			while (nullptr != right->_right)
			{
				right = right->_right;
			}

			_node = right;
		}
		//Ϊ�գ���������������1��cur���� ���2��cur����
		//���1����Ҫ�ҵ����Ĺ������ȣ��������Ⱦ�������һ���ڵ�
		//���2�����ڵ��������һ���ڵ�
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
				cout << "��ɫ�ڵ㲻���!" << endl;

				return false;
			}

			return true;
		}

		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout << "���������ĺ�ɫ�ڵ㣡" << endl;

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

	//�˰汾�Ŀ������������ȷ�ģ������汾�Ŀ������������⣬��Ҫ�����Ǹ��ڵ�û����
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

		//��Ҷ�ӽڵ�
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

			//����������
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;

				//���1�����������Ϊ��
				if (nullptr != uncle && uncle->_col == RED)
				{
					//���Ƕ�����͸��ڵ���б�ڴ���
					uncle->_col = parent->_col = BLACK;
					//���游���б�촦��
					grandfather->_col = RED;

					//�������������������游�ڵ�
					cur = grandfather;
					parent = cur->_parent;
				}
				else//���2+���3,uncle������Ϊ�ڣ���uncle������
				{
					//�ҵ���
					if (cur == parent->_left)
					{
						RotateR(grandfather);

						grandfather->_col = RED;
						parent->_col = BLACK;
					}
					else//����˫��
					{
						RotateL(parent);
						RotateR(grandfather);

						grandfather->_col = RED;
						cur->_col = BLACK;
					}

					//��ת���˾Ͳ��ô�����ֱ�ӽ�������
					break;
				}
			}
			else//����������
			{
				Node* uncle = grandfather->_left;

				//���1�����������Ϊ��
				if (nullptr != uncle && uncle->_col == RED)
				{
					//ͬ�����
					uncle->_col = parent->_col = BLACK;
					//�游���
					grandfather->_col = RED;

					//�������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//����
					if (parent->_right == cur)
					{
						RotateL(grandfather);

						grandfather->_col = RED;
						parent->_col = BLACK;
					}
					//����˫��
					else
					{
						RotateR(parent);
						RotateL(grandfather);

						grandfather->_col = RED;
						cur->_col = BLACK;
					}

					//��ת���˾Ͳ��ô�����ֱ�ӽ�������
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
			cout << "���ڵ�Ϊ��ɫ��" << endl;

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