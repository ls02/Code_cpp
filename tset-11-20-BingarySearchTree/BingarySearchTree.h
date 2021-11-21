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

		//拷贝函数
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

		//销毁节点
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
			//如果为空说明没有可删的或者没有key
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
			else//走到这说明有一个孩子或者两个孩子或者没有孩子
			{
				//如果没有孩子会在第一个if里面解决掉
				//假设左边为空，那么我们只需连接右边，释放源节点
				if (root->_left == nullptr)
				{
					//存储原节点
					Node* temp = root;
					//连接右节点
					root = root->_right;

					//释放原节点
					delete temp;

					//删除成功返回真
					return true;
				}
				else if (root->_right == nullptr)//和上面同理
				{
					Node* temp = root;
					root = root->_left;

					delete temp;

					return true;
				}
				else//到这里说明有两个孩子，有两个孩子我们去左边或右边找一个值，去左边找最大值，去右边找最小值
				{
					Node* cur = root->_left;
					Node* parent = nullptr;

					//找到最大值
					while (cur->_right != nullptr)
					{
						parent = cur;
						cur = cur->_right;
					}

					//把最大值给要删节点
					root->_key = cur->_key;

					//判断cur是左孩子还是右孩子
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
			if (root == nullptr)//走到空说明要插入了
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
			else//如果相等说明有了
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

		//拷贝构造，深拷贝
		BSTree(const BSTree<K>& k)
		{
			//借助_Copy完成深拷贝
			_root = _Copy(k._root);
		}

		//赋值重载
		BSTree<K>& operator=(BSTree<K> k)
		{
			std::swap(_root, k._root);

			return *this;
		}

		//析构
		~BSTree()
		{
			_Destroyed(_root);

			_root = nullptr;
		}

		//增
		//无递归实现
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
				else //如果相等说明key有了不能插入
				{
					return false;
				}
			}

			//在叶子节点插入，判断key是左孩子还是右孩子
			if (parent->_key > key)
			{
				parent->_left = new Node(key);
			}
			else
			{
				parent->_right = new Node(key);
			}

			//插入成功返回真
			return true;
		}

		//递归插入
		bool InsertR(const K& key)
		{
			return _InsertR(_root, key);
		}

		//查
		//非递归
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
				else //找到了,返回找到的节点
				{
					return cur;
				}
			}

			//走到这说明没有这个数
			return nullptr;
		}

		//递归
		Node* FindR(const K& key)
		{
			return _FindR(_root, key);
		}

		//删
		//非递归
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
				else //如果找到了，那么会有两种情况，1、它只有一个孩子 2、或者两个孩子
				{
					//假设它只有右孩子
					if (cur->_left == nullptr)
					{
						//那么我们直接用它的父节点对它的右孩子
						//进行连接，然后释放cur
						//先判断cur是左孩子还是右孩子
						//判断好了才能正确的连接上
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
					else if (cur->_right == nullptr)//假设它只有左孩子
					{
						//和上面同理
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
					else //到这里说明它有两个孩子，那么有两个孩子，我们只需要随便去它一边的孩子里面找（去右孩子就找最小值、去左孩子就找最大值）就可以了
						//因为去左边的话找最大值，这样才能满足替换，因为这个结构就是这样的，去右边找最小值同理，假设我们这里去它左边的孩子
					{
						//去左边找
						Node* max = cur->_left;
						Node* maxParent = nullptr;

						while (max->_right != nullptr)
						{
							maxParent = max;
							max = max->_right;
						}

						//找到最大值了
						cur->_key = max->_key;
						//断开被释放节点的连接
						maxParent->_right = nullptr;

						//释放最大值节点
						delete max;

						return true;
					}
				}
			}
			//如果没有这个值会走到这
			return false;
		}

		//递归版本
		bool EraseR(const K& key)
		{
			return _EraseR(_root, key);
		}

		//中序遍历
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

		//拷贝函数
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

		//销毁节点
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
			//如果为空说明没有可删的或者没有key
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
			else//走到这说明有一个孩子或者两个孩子或者没有孩子
			{
				//如果没有孩子会在第一个if里面解决掉
				//假设左边为空，那么我们只需连接右边，释放源节点
				if (root->_left == nullptr)
				{
					//存储原节点
					Node* temp = root;
					//连接右节点
					root = root->_right;

					//释放原节点
					delete temp;

					//删除成功返回真
					return true;
				}
				else if (root->_right == nullptr)//和上面同理
				{
					Node* temp = root;
					root = root->_left;

					delete temp;

					return true;
				}
				else//到这里说明有两个孩子，有两个孩子我们去左边或右边找一个值，去左边找最大值，去右边找最小值
				{
					Node* cur = root->_left;
					Node* parent = nullptr;

					//找到最大值
					while (cur->_right != nullptr)
					{
						parent = cur;
						cur = cur->_right;
					}

					//把最大值给要删节点
					root->_key = cur->_key;

					//判断cur是左孩子还是右孩子
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
			if (root == nullptr)//走到空说明要插入了
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
			else//如果相等说明有了
			{
				return false;
			}
		}

	public:
		BSTree()
			:_root(nullptr)
		{}

		//拷贝构造，深拷贝
		BSTree(const BSTree<K, V>& k)
		{
			//借助_Copy完成深拷贝
			_root = _Copy(k._root);
		}

		//赋值重载
		BSTree<K, V>& operator=(BSTree<K, V> k)
		{
			std::swap(_root, k._root);

			return *this;
		}

		//析构
		~BSTree()
		{
			_Destroyed(_root);

			_root = nullptr;
		}

		//递归插入
		bool InsertR(const K& key, const V& value)
		{
			return _InsertR(_root, key, value);
		}

		//删
		//递归版本
		bool EraseR(const K& key)
		{
			return _EraseR(_root, key);
		}

		//递归
		Node* FindR(const K& key)
		{
			return _FindR(_root, key);
		}

		//删
		//中序遍历
		void Order()
		{
			_Order(_root);
			cout << endl;
		}
	};
}