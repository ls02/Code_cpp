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

	//ƽ������
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
		
		cout << root->_kv.first << "��" << root->_kv.second << endl;

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


		//�����������������ƽ���������˵��������Ѿ�����ƽ���������
		if (rightHeight - leftHeight != root->_bf)
		{
			cout << "ƽ�������쳣��" << endl;

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
		//����
		if (nullptr == _root)
		{

			_root = new Node(kv);

			return make_pair(_root, true);
		}

		Node* cur = _root;
		Node* parent = nullptr;

		//�Һ��ʵ�λ��
		while (cur != nullptr)
		{
			//����ƽ�����Ĺ������ҵ����ʵĿսڵ�
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
			else //˵����������ڵ㲻֧�ֲ��룬���᷵�ص�ǰ�ڵ��λ��
			{
				return make_pair(cur, true);
			}
		}

		cur = new Node(kv);
		//��¼�½ڵ�
		Node* newNode = cur;

		//�ں��ʵ�λ�ò���cur
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

		//��������
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

			//���Ϊ0˵������
			if (!parent->_bf)
			{
				break;
			}
			//�������0����ô��Щ��ֵ��Ӱ�쵽���ĸ��ڵ㣬����Ҫ�����ĸ��ڵ����++��--
			else if (1 == parent->_bf || -1 == parent->_bf)
			{
				cur = parent;
				parent = parent->_parent;
			}
			//�����ڵ����2��-2˵�����Ѿ�����ƽ������
			//Ϊ�˱�֤������ƽ�����Ĺ����������������������ת����
			else if (2 == parent->_bf || -2 == parent->_bf)
			{
				//�����2��ô�ͽ�������
				if (2 == parent->_bf)
				{
					//cur��-1˵��������˫��
					if (-1 == cur->_bf)
					{
						RotateRL(parent);
					}
					//����
					else
					{
						RotateL(parent);
					}
				}
				else
				{
					//cur��1˵��������˫��
					if (1 == cur->_bf)
					{
						RotateLR(parent);
					}
					//�ҵ���
					else
					{
						RotateR(parent);
					}
				}

				//��ת���ˣ�ֱ������
				break;
			}
			else
			{
				//��������߲����⣬�ߵ���˵�������Ѿ�����ƽ������
				assert(false);
			}
		}

		return make_pair(newNode, true);
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

		//��Ϊ�Ѿ������ת�ˣ��Ѿ�ƽ���ˣ�����ƽ�����ӻָ�����
		subR->_bf = parent->_bf = 0;
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

		//���Ӹ���Ϊ0
		subL->_bf = parent->_bf = 0;
	}

	//����˫��
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		// ƽ�����ӵ���
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

	//����˫��
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(parent->_right);
		RotateL(parent);

		// ƽ�����Ӹ���
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
		else //�������ߵ��⣬�ߵ���˵�����Ѿ�����ƽ���������
		{
			assert(false);
		}
	}

	//�������
	void InOrder()
	{
		_InOrder(_root);
	}

	bool IsAVLTree()
	{
		return _IsBalance(_root);
	}
};
