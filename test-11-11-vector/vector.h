#pragma once
#include <iostream>
#include <algorithm>
#include <assert.h>

using std::cout;
using std::cin;
using std::endl;

namespace ls
{
	template <class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		//迭代器
		iterator begin()
		{
			return _start;
		}

		const_iterator begin()const
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator end()const
		{
			return _finish;
		}

		//初始化
		//构造函数
		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{}

		vector(size_t n, const T& val = T())
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{
			reserve(n);

			while (n--)
			{
				push_back(val);
			}
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			reserve(last - first);

			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		
		//拷贝构造
		vector(const vector<T>& v)
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{
			reserve(v.capacity());

			for (auto i : v)
			{
				push_back(i);
			}
			_finish = _start + v.size();
		}

		//析构函数
		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _endofstorage = nullptr;
			}
		}

		//容量
		size_t size()const
		{
			return _finish - _start;
		}

		size_t capacity()const
		{
			return _endofstorage - _start;
		}

		//扩容
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				T* temp = new T[n];
				size_t sz = size();

				for (size_t i = 0; i < sz; i++)
				{
					temp[i] = _start[i];
				}

				delete[] _start;
				_start = temp;
				_endofstorage = _start + n;
				_finish = _start + sz;
			}
		}

		//缺省给的是匿名，这样默认就是初始化0
		void resize(size_t n, T val = T())
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				if (n > capacit())
				{
					reserve(n);
				}

				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
		}

		//判断是否为空
		bool empty()const
		{
			return _start == _finish;
		}

		//运算符重载
		T& operator[](const size_t i)
		{
			assert(i < size());
			return _start[i];
		}

		const T& operator[](const size_t i)const
		{
			assert(i < size());
			return _start[i];
		}

		//增容
		void push_back(const T& val)
		{
			if (_finish == _endofstorage)
			{
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			}

			*_finish = val;
			++_finish;
		}

		void insert(iterator pos, const T& val)
		{
			if (_finish == _endofstorage)
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				//更新pos解决迭代器失效问题
				pos = _start + len;
			}

			T* end = _finish;

			while (end >= pos)
			{
				*end = *(end - 1);
				end--;
			}
			*pos = val;
			_finish++;
		}

		//删除
		iterator erase(iterator pos)
		{
			iterator it = pos + 1;

			while (it != _finish)
			{
				*(it - 1) = *it;
				it++;
			}

			_finish--;

			return pos;
		}

		void pop_back()
		{
			assert(!(empty()));
			_finish--;
		}

	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};

	template <class V>
	void PrintVector(const V& v)
	{
		typename V::const_iterator it = v.begin();

		while (it != v.end())
		{
			cout << *it << ' ';
			it++;
		}

		cout << endl;
	}

	void test_vector1()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);

		vector<int>::iterator it = v1.begin();

		//while (it != v1.end())
		//{
		//	cout << *it << ' ';
		//	it++;
		//}
		PrintVector(v1);

		vector<int> v2(v1);
		PrintVector(v2);

		vector<int> v3;
		v3 = v2;
		PrintVector(v3);

		it = std::find(v1.begin(), v1.end(), 3);
		v1.insert(it, 30);
		PrintVector(v1);
	}
}
