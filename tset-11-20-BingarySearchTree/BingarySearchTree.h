#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using std::cout;
using std::endl;

namespace K
{
	template <class K>
	struct BSNode
	{
		BSNode<K>* _left;
		BSNode<K>* _right;
		K _key;
		
		BSNode(const K& key = K())
			:_left(nullptr)
			,_right(nullptr)
			,_key(key)
		{}
	};

	template <class K>
	class BSTree
	{
		typedef BSNode<K> Node;
	private:
		Node* _root;

		void _Order(const Node* root)
		{
			if (root == nullptr)
			{
				return;
			}

			_Order(root->_left);
			cout << root->_key << ' ';
			_Order(root->_right);
		}

		//��������
		Node* _Copy(Node* root)
		{
			if (root == nullptr)
			{
				return nullptr;
			}

			Node* copyNode = new Node(root->_key);
			copyNode->_left = _Copy(root->_left);
			copyNode->_right = _Copy(root->_right);

			return copyNode;
		}

		//���ٽڵ�
		void _Destroyed(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}

			_Destroyed(root->_left);
			_Destroyed(root->_right);

			delete root;
		}

		bool _EraseR(Node*& root, const K& key)
		{
			//���Ϊ��˵��û�п�ɾ�Ļ���û��key
			if (root == nullptr)
			{
				return false;
			}
			else if (root->_key > key)
			{
				return _EraseR(root->_left, key);
			}
			else if (root->_key < key)
			{
				return _EraseR(root->_right, key);
			}
			else//�ߵ���˵����һ�����ӻ����������ӻ���û�к���
			{
				//���û�к��ӻ��ڵ�һ��if��������
				//�������Ϊ�գ���ô����ֻ�������ұߣ��ͷ�Դ�ڵ�
				if (root->_left == nullptr)
				{
					//�洢ԭ�ڵ�
					Node* temp = root;
					//�����ҽڵ�
					root = root->_right;

					//�ͷ�ԭ�ڵ�
					delete temp;

					//ɾ���ɹ�������
					return true;
				}
				else if (root->_right == nullptr)//������ͬ��
				{
					Node* temp = root;
					root = root->_left;

					delete temp;

					return true;
				}
				else//������˵�����������ӣ���������������ȥ��߻��ұ���һ��ֵ��ȥ��������ֵ��ȥ�ұ�����Сֵ
				{
					Node* cur = root->_left;
					Node* parent = nullptr;

					//�ҵ����ֵ
					while (cur->_right != nullptr)
					{
						parent = cur;
						cur = cur->_right;
					}

					//�����ֵ��Ҫɾ�ڵ�
					root->_key = cur->_key;

					//�ж�cur�����ӻ����Һ���
					if (parent->_left == cur)
					{
						delete cur;
						parent->_left = nullptr;
					}
					else
					{
						delete cur;
						parent->_right = nullptr;
					}

					return true;
				}
			}
		}

		bool _InsertR(Node*& root, const K& key)
		{
			if (root == nullptr)//�ߵ���˵��Ҫ������
			{
				Node* newNode = new Node(key);

				root = newNode;

				return true;
			}
			else if (root->_key > key)
			{
				return _InsertR(root->_left, key);
			}
			else if (root->_key < key)
			{
				return _InsertR(root->_right, key);
			}
			else//������˵������
			{
				return false;
			}
		}

		Node* _FindR(Node* root, const K& key)
		{
			if (root == nullptr)
			{
				return nullptr;
			}
			else if (root->_key > key)
			{
				return _FindR(root->_left, key);
			}
			else if (root->_key < key)
			{
				return _FindR(root->_right, key);
			}
			else
			{
				return root;
			}
		}

	public:
		BSTree()
			:_root(nullptr)
		{}

		//�������죬���
		BSTree(const BSTree<K>& k)
		{
			//����_Copy������
			_root = _Copy(k._root);
		}

		//��ֵ����
		BSTree<K>& operator=(BSTree<K> k)
		{
			std::swap(_root, k._root);

			return *this;
		}

		//����
		~BSTree()
		{
			_Destroyed(_root);

			_root = nullptr;
		}

		//��
		//�޵ݹ�ʵ��
		bool Insert(const K& key)
		{
			if (_root == nullptr)
			{
				_root = new Node(key);

				return true;
			}

			Node* parent = nullptr;
			Node* cur = _root;

			while (cur != nullptr)
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
				else //������˵��key���˲��ܲ���
				{
					return false;
				}
			}

			//��Ҷ�ӽڵ���룬�ж�key�����ӻ����Һ���
			if (parent->_key > key)
			{
				parent->_left = new Node(key);
			}
			else
			{
				parent->_right = new Node(key);
			}

			//����ɹ�������
			return true;
		}

		//�ݹ����
		bool InsertR(const K& key)
		{
			return _InsertR(_root, key);
		}

		//��
		//�ǵݹ�
		Node* Find(const K& key)
		{
			Node* cur = _root;

			while (cur != nullptr)
			{
				if (cur->_key > key)
				{
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					cur = cur->_right;
				}
				else //�ҵ���,�����ҵ��Ľڵ�
				{
					return cur;
				}
			}

			//�ߵ���˵��û�������
			return nullptr;
		}

		//�ݹ�
		Node* FindR(const K& key)
		{
			return _FindR(_root, key);
		}

		//ɾ
		//�ǵݹ�
		bool Erase(const K& key)
		{
			if (_root == nullptr)
			{
				return false;
			}

			Node* cur = _root;
			Node* parent = nullptr;

			while (cur != nullptr)
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
				else //����ҵ��ˣ���ô�������������1����ֻ��һ������ 2��������������
				{
					//������ֻ���Һ���
					if (cur->_left == nullptr)
					{
						//��ô����ֱ�������ĸ��ڵ�������Һ���
						//�������ӣ�Ȼ���ͷ�cur
						//���ж�cur�����ӻ����Һ���
						//�жϺ��˲�����ȷ��������
						if (parent->_key > cur->_key)
						{
							parent->_left = cur->_right;
							delete cur;

							return true;
						}
						else
						{
							parent->_right = cur->_right;
							delete cur;

							return true;
						}
					}
					else if (cur->_right == nullptr)//������ֻ������
					{
						//������ͬ��
						if (parent->_key > cur->_key)
						{
							parent->_left = cur->_left;
							delete cur;

							return true;
						}
						else
						{
							parent->_right = cur->_left;
							delete cur;
							cur = nullptr;

							return true;
						}
					}
					else //������˵�������������ӣ���ô���������ӣ�����ֻ��Ҫ���ȥ��һ�ߵĺ��������ң�ȥ�Һ��Ӿ�����Сֵ��ȥ���Ӿ������ֵ���Ϳ�����
						//��Ϊȥ��ߵĻ������ֵ���������������滻����Ϊ����ṹ���������ģ�ȥ�ұ�����Сֵͬ��������������ȥ����ߵĺ���
					{
						//ȥ�����
						Node* max = cur->_left;
						Node* maxParent = nullptr;

						while (max->_right != nullptr)
						{
							maxParent = max;
							max = max->_right;
						}

						//�ҵ����ֵ��
						cur->_key = max->_key;
						//�Ͽ����ͷŽڵ������
						maxParent->_right = nullptr;

						//�ͷ����ֵ�ڵ�
						delete max;

						return true;
					}
				}
			}
			//���û�����ֵ���ߵ���
			return false;
		}

		//�ݹ�汾
		bool EraseR(const K& key)
		{
			return _EraseR(_root, key);
		}

		//�������
		void Order()
		{
			_Order(_root);
			cout << endl;
		}
	};
}


namespace KV
{
	template <class K, class V>
	struct BSNode
	{
		BSNode<K, V>* _left;
		BSNode<K, V>* _right;
		K _key;
		V _value;

		BSNode(const K& key = K(), const V& value = V())
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
			, _value(value)
		{}
	};

	template <class K, class V>
	class BSTree
	{
		typedef BSNode<K, V> Node;
	private:
		Node* _root;

		void _Order(const Node* root)
		{
			if (root == nullptr)
			{
				return;
			}

			_Order(root->_left);
			cout << "key:" << root->_key << ' ' << "value:" << root->_value << ' ';
			_Order(root->_right);
		}

		//��������
		Node* _Copy(Node* root)
		{
			if (root == nullptr)
			{
				return nullptr;
			}

			Node* copyNode = new Node(root->_key, root->_value);
			copyNode->_left = _Copy(root->_left);
			copyNode->_right = _Copy(root->_right);

			return copyNode;
		}

		//���ٽڵ�
		void _Destroyed(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}

			_Destroyed(root->_left);
			_Destroyed(root->_right);

			delete root;
		}

		bool _EraseR(Node*& root, const K& key)
		{
			//���Ϊ��˵��û�п�ɾ�Ļ���û��key
			if (root == nullptr)
			{
				return false;
			}
			else if (root->_key > key)
			{
				return _EraseR(root->_left, key);
			}
			else if (root->_key < key)
			{
				return _EraseR(root->_right, key);
			}
			else//�ߵ���˵����һ�����ӻ����������ӻ���û�к���
			{
				//���û�к��ӻ��ڵ�һ��if��������
				//�������Ϊ�գ���ô����ֻ�������ұߣ��ͷ�Դ�ڵ�
				if (root->_left == nullptr)
				{
					//�洢ԭ�ڵ�
					Node* temp = root;
					//�����ҽڵ�
					root = root->_right;

					//�ͷ�ԭ�ڵ�
					delete temp;

					//ɾ���ɹ�������
					return true;
				}
				else if (root->_right == nullptr)//������ͬ��
				{
					Node* temp = root;
					root = root->_left;

					delete temp;

					return true;
				}
				else//������˵�����������ӣ���������������ȥ��߻��ұ���һ��ֵ��ȥ��������ֵ��ȥ�ұ�����Сֵ
				{
					Node* cur = root->_left;
					Node* parent = nullptr;

					//�ҵ����ֵ
					while (cur->_right != nullptr)
					{
						parent = cur;
						cur = cur->_right;
					}

					//�����ֵ��Ҫɾ�ڵ�
					root->_key = cur->_key;

					//�ж�cur�����ӻ����Һ���
					if (parent->_left == cur)
					{
						delete cur;
						parent->_left = nullptr;
					}
					else
					{
						delete cur;
						parent->_right = nullptr;
					}

					return true;
				}
			}
		}

		Node* _FindR(Node* root, const K& key)
		{
			if (root == nullptr)
			{
				return nullptr;
			}
			else if (root->_key > key)
			{
				return _FindR(root->_left, key);
			}
			else if (root->_key < key)
			{
				return _FindR(root->_right, key);
			}
			else
			{
				return root;
			}
		}

		bool _InsertR(Node*& root, const K& key, const V& value)
		{
			if (root == nullptr)//�ߵ���˵��Ҫ������
			{
				Node* newNode = new Node(key, value);

				root = newNode;

				return true;
			}
			else if (root->_key > key)
			{
				return _InsertR(root->_left, key, value);
			}
			else if (root->_key < key)
			{
				return _InsertR(root->_right, key, value);
			}
			else//������˵������
			{
				return false;
			}
		}

	public:
		BSTree()
			:_root(nullptr)
		{}

		//�������죬���
		BSTree(const BSTree<K, V>& k)
		{
			//����_Copy������
			_root = _Copy(k._root);
		}

		//��ֵ����
		BSTree<K, V>& operator=(BSTree<K, V> k)
		{
			std::swap(_root, k._root);

			return *this;
		}

		//����
		~BSTree()
		{
			_Destroyed(_root);

			_root = nullptr;
		}

		//�ݹ����
		bool InsertR(const K& key, const V& value)
		{
			return _InsertR(_root, key, value);
		}

		//ɾ
		//�ݹ�汾
		bool EraseR(const K& key)
		{
			return _EraseR(_root, key);
		}

		//�ݹ�
		Node* FindR(const K& key)
		{
			return _FindR(_root, key);
		}

		//ɾ
		//�������
		void Order()
		{
			_Order(_root);
			cout << endl;
		}
	};
}