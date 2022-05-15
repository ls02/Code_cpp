#pragma once
#ifndef __ITERATOR_H__
#define __ITERATOR_H__
#include "RBTree.h"

// 反向迭代器--迭代器适配器
template<class Iterator>
struct ReverseIterator
{
	typedef typename Iterator::reference Ref;
	typedef typename Iterator::pointer Ptr;
	typedef ReverseIterator<Iterator> Self;
	Iterator _it;

	ReverseIterator(Iterator it)
		:_it(it)
	{}

	Ref operator*()
	{
		return *_it;
	}

	Ptr operator->()
	{
		return _it.operator->();
	}

	Self& operator++()
	{
		--_it;
		return *this;
	}

	Self& operator--()
	{
		++_it;
		return* this;
	}

	bool operator!=(const Self& s) const
	{
		return _it != s._it;
	}

	bool operator==(const Self& s) const
	{
		return _it == s._it;
	}
};

#endif