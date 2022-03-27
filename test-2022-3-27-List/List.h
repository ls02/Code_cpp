#pragma once
#ifndef __LIST_H__
#define __LIST_H__
#include <iostream>

namespace ls
{
	template<class T>
	struct _list_node
	{
		T* _prev;
		T* _next;
		T _val;

		_list_node(const T& val = T())
			:prev(nullptr)
			,next(nullptr)
			,_val(val)
		{}
	};

	template<class T, class Ref, class Ptr>
	struct _list_iterator
	{
		typedef _list_node<T> node;
		typedef _list_iterator<T, T&, T*> self;
		node* _pNode;
		
		_list_iterator(node* pNode)
			:_pNode(pNode)
		{}

		Ref operator*(void)
		{
			return _pNode->_val;
		}

		//这里有两个->不过被编译器做过特殊处理，我们只需要一个->即可实际上是两个->，第一个是外面的拿到里面的数据，然后还有一个->是用来查找val的成员，因为val有可能是一个类。
		//Ptr operator->(void)
		//{
		//	return &_pNode->_val;
		//}
	};

	template<class T>
	class list
	{
	private:
		typedef _list_node<T> node;
		node* _pHead;

	public:
		//迭代器
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
		list()
		{
			_phead = new node;
			_phead->_next = _phead;
			_phead->_prev = _phead;
		}

		list(const list<T>& l)
		{
			
		}

	};

	void Test1(void)
	{
		list<int> l1;
	}
}

#endif
