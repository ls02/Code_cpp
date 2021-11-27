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
		cout << root->_kv.first << "��" << root->_kv.second << endl;
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
				cout << "��ɫ�ڵ����������ȣ�" << endl;

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

		//�ҵ�Ҷ��
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
				//����ֵͬ��֧�ֲ��룬���ص�ǰ�ڵ�
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

		//������ڵ㲻Ϊ����Ϊ��ɫ˵��������ڵ㻹��Ҫ����
		while (nullptr != parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;

			if (parent->_col == RED && grandfather != nullptr)
			{
				Node* uncle = nullptr;

				//����root��������
				if (grandfather->_left == parent)
				{
					uncle = grandfather->_right;

					//���1����������Ϊ�죬���ǽ��б�ɫ������u��p��Ϊ��ɫ��g��Ϊ��ɫ��
					//���g��root���Ҳû��ϵ������������root���б�ڴ���
					//���������Ľ���������Ľڵ���һ��һ��
					if (nullptr != uncle && uncle->_col == RED)
					{
						uncle->_col = parent->_col = BLACK;
						grandfather->_col = RED;

						//�������ϴ���ֱ�����нڵ㶼���Ϲ���
						cur = grandfather;
						parent = cur->_parent;
					}
					//���2����������Ϊ��
					//���3��������
					//���������2�������3����ֻ��Ҫȷ��cur������������������
					//���������͵���������������˫��
					else
					{
						if (parent->_left == cur)
						{
							//�ҵ���
							RotateR(grandfather);
							grandfather->_col = RED;
							parent->_col = BLACK;
						}
						else //����˫��
						{
							RotateL(parent);
							RotateR(grandfather);
							grandfather->_col = RED;
							cur->_col = BLACK;
						}

						break;
					}
				}
				//����root��������
				else
				{
					uncle = grandfather->_left;

					//���1����������Ϊ��
					if (nullptr != uncle && uncle->_col == RED)
					{
						uncle->_col = parent->_col = BLACK;
						grandfather->_col = RED;

						//�������ϴ���ֱ�����нڵ㶼���Ϲ���
						cur = grandfather;
						parent = cur->_parent;
					}
					else
					{
						//���2����������Ϊ��
						//���3��û����
						//��ʱ��ֻ��Ҫȷ�������ڵ���������
						//���Ҿ�������
						//�����������˫��

						//����
						if (parent->_right == cur)
						{
							RotateL(grandfather);
							grandfather->_col = RED;
							parent->_col = BLACK;
						}
						else//����˫��
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
				//���ڵ㲻Ϊ�����账����Ϊ�������ӽڵ�Ĭ��Ϊ��
				//�½ڵ�ĸ��ڵ㲻Ϊ�죬������������ѭ��
				//���Ϊ�����ĺ��ӱ����Ǻڣ������ͻ��ƻ��ṹ
				break;
			}
		}

		//��ֹ���ڵ㱻��ɺ�ɫ��������ڵ��Ǻ�ɫ��ô����ƺ�����Ĺ���������Ͳ��Ǻ������
		_root->_col = BLACK;

		return make_pair(newNode, true);
	}

	//����
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;

		//�����Ϊ����Ҫ���¸��ڵ�
		if (nullptr != subRL)
		{
			subRL->_parent = parent;
		}

		Node* parentParent = parent->_parent;

		//���parent�Ƿ�Ϊ���ڵ�
		if (parent == _root)
		{
			subR->_left = parent;
			parent->_parent = subR;
			subR->_parent = nullptr;
			_root = subR;
		}
		else
		{
			//���游�ڵ�
			parentParent = parent->_parent;
			subR->_left = parent;
			parent->_parent = subR;
			subR->_parent = parentParent;

			//���parnet��parentParent������������������
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
		//��Ϊ����Ҫ������subLR�ĸ��ڵ�
		if (nullptr != subLR)
		{
			subLR->_parent = parent;
		}

		Node* parentParent = nullptr;
		
		//���parent�Ƿ�Ϊ���ڵ�
		//����Ǹ�����ô�Ͳ���Ҫ�������ĸ�
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

			//�ҳ�parent��panretParent������������������
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
			cout << "���ڵ��Ǻ�ɫ��" << endl;
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