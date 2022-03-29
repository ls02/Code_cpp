#pragma once
#ifndef __LIST_H__
#define __LIST_H__
#include <iostream>
#include <assert.h>
#include <algorithm>

//
namespace ls
{
	template<class T>
	struct _list_node
	{
		_list_node<T>* _prev;
		_list_node<T>* _next;
		T _val;
		
		//Ĭ�Ϲ��캯��
		_list_node(const T& val = T())
			:_prev(nullptr)
			,_next(nullptr)
			,_val(val)
		{}
	};

	template<class T, class Ref, class Ptr>
	struct _list_iterator
	{
		typedef _list_node<T> node;
		typedef _list_iterator<T, Ref, Ptr> self;
		node* _pNode;
		
		//���캯��
		_list_iterator(node* pNode)
			:_pNode(pNode)
		{}

		Ref operator*(void)
		{
			return _pNode->_val;
		}

		//����������->�������������������⴦������ֻ��Ҫһ��->����ʵ����������->����һ����������õ���������ݣ�Ȼ����һ��->����������val�ĳ�Ա����Ϊval�п�����һ���ࡣ
		Ptr operator->(void)
		{
			return &_pNode->_val;
		}

		bool operator!=(const self& s)const
		{
			return _pNode != s._pNode;
		}

		bool operator==(const self& s)const
		{
			return _pNode == s._pNode;
		}

		self& operator++(void)
		{
			_pNode = _pNode->_next;

			return *this;
		}

		self operator++(int)
		{
			self temp(*this);
			_pNode = _pNode->_next;

			return temp;
		}

		self& operator--(void)
		{
			_pNode = _pNode->_prev;

			return *this;
		}

		self operator--(int) const
		{
			self temp(*this);
			_pNode = _pNode->_next;

			return temp;
		}
	};

	template<class T>
	class list
	{
	private:
		typedef _list_node<T> node;
		node* _pHead;

	public:
		//������
		typedef _list_iterator<T, T&, T*> iterator;
		typedef _list_iterator<T, const T&, const T*> const_iterator;

		iterator begin(void)
		{
			return iterator(_pHead->_next);
		}

		iterator end(void)
		{
			return iterator(_pHead);
		}

		const_iterator begin(void)const
		{
			return const_iterator(_pHead->_next);
		}

		const_iterator end(void)const
		{
			return const_iterator(_pHead);
		}

		//Ĭ�Ϲ���
		list()
		{
			_pHead = new node;
			_pHead->_next = _pHead;
			_pHead->_prev = _pHead;
		}

		//��������
		list(const list<T>& l)
		{
			_pHead = new node;
			_pHead->_next = _pHead;
			_pHead->_prev = _pHead;

			const_iterator it = l.begin();
			while (it != l.end())
			{
				push_back(*it);
				it++;
			}
			//for (auto& e : l)
			//{
			//	push_back(e);
			//}
		}

		//��ֵ����
		list<T>& operator=(list<T> l)
		{
			std::swap(l._pHead, _pHead);

			return *this;
		}

		//��������
		~list(void)
		{
			clear();
			delete _pHead;
			_pHead = nullptr;
		}

		//���ӿ�
		//����λ�ò���
		void insert(iterator pos, const T& val)
		{
			assert(nullptr != pos._pNode);

			node* cur = pos._pNode;
			node* prev = cur->_prev;
			node* newNode = new node(val);

			newNode->_next = cur;
			newNode->_prev = prev;
			cur->_prev = newNode;
			prev->_next = newNode;

		}

		//β��
		void push_back(const T& val)
		{
			insert(end(), val);
		}

		//ͷ��
		void push_front(const T& val)
		{
			insert(begin(), val);
		}

		//ɾ�ӿ�
		//����λ��ɾ��
		iterator erase(iterator pos)
		{
			assert(nullptr != pos._pNode);
			assert(pos != end());

			node* prev = pos._pNode->_prev;
			node* next = pos._pNode->_next;

			delete pos._pNode;
			prev->_next = next;
			next->_prev = prev;

			return iterator(next);
		}

		//β��
		void pop_push(void)
		{
			erase(end());
		}

		//ͷɾ
		void pop_front(void)
		{
			erase(begin());
		}

		void clear(void)
		{
			iterator it = begin();
			while (it != end())
			{
				erase(it++);
			}
		}

		void empty(void)const
		{
			return begin() == end();
		}

		size_t size(void)const
		{
			size_t count = 0;

			const_iterator it = begin();
			while (it != end())
			{
				count++;
				it++;
			}

			return count;
		}
	};

	template<class Con>
	void Print(const Con& c)
	{
		typename Con::const_iterator it = c.begin();
		while (it != c.end())
		{
			std::cout << *it << ' ';
			++it;
		}

		std::cout << std::endl;
	}

	void Test1(void)
	{
		list<int> l1;

		l1.push_back(1);
		l1.push_back(2);
		l1.push_back(3);
		l1.push_back(4);

		Print(l1);

		list<int> l2(l1);

		list<int>::iterator pos = nullptr;
		list<int>::iterator it = l2.begin();
		while (it != l2.end())
		{
			if (*it == 2)
			{
				pos = it;
			}

			it++;
		}

		//std::cout << *pos << std::endl;
		pos = l2.erase(pos);
		l2.insert(pos, 400);
		l2.push_front(111);
		l2.push_front(112);
		l2.push_front(113);
		l2.pop_front();
		l2.pop_front();
		l2.pop_front();

		l2.clear();
		
		Print(l2);
		list<int> l3;
		l3 = l1;
		Print(l3);
		std::cout << l3.size() << std::endl;
	}

}

#endif
