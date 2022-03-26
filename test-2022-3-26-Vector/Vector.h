#pragma once
#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <iostream>
#include <assert.h>
#include <algorithm>

namespace ls
{
	template <class T>
	class vector
	{
	private:
		T* _start;
		T* _finish;
		T* _endOfStorage;

	public:
		//迭代器
		typedef T* iterator;
		typedef const T* const_iterator;

		iterator begin(void)
		{
			return _start;
		}

		const_iterator begin(void)const
		{
			return _start;
		}

		iterator end(void)
		{
			return _finish;
		}

		const_iterator end(void)const
		{
			return _finish;
		}

		//构造函数
		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_endOfStorage(nullptr)
		{}

		//构造函数重载
		vector(size_t n, const T& value = T())
			:_start(nullptr)
			,_finish(nullptr)
			,_endOfStorage(nullptr)
		{
			reserve(n);

			while (n--)
			{
				push_bakck(value);
			}
		}

		//拷贝构造
		vector(vector<T>& v)
			:_start(nullptr)
			,_finish(nullptr)
			,_endOfStorage(nullptr)
		{
			_start = new T[v.capacity()];

			for (size_t i = 0; i < v.size(); i++)
			{
				_start[i] = v._start[i];
			}

			_finish = _start + v.size();
			_endOfStorage = _start + v.capacity();
		}

		//析构函数
		~vector(void)
		{
			if (nullptr != _start)
			{
				delete[] _start;
			}

			_start = _finish = _endOfStorage = nullptr;
		}

		//赋值重载
		vector<T>& operator=(vector<T> v)
		{
			//利用拷贝构造完成
			swap(v);

			return *this;
		}

		//[]重载
		T& operator[](const size_t i)
		{
			return _start[i];
		}

		const T& operator[](const size_t i)const
		{
			return _start[i];
		}

		//增接口
		//尾插一个值
		void push_back(const T& value)
		{
			//检查空间是否满了
			if (_finish >= _endOfStorage)
			{
				size_t newCapacity = capacity() ? capacity() * 2 : 4;
				reserve(newCapacity);
			}

			*_finish = value;
			_finish++;
		}

		//任意位置插入
		void insert(iterator pos, size_t value)
		{
			//检查是否需要扩容
			if (_finish >= _endOfStorage)
			{
				//记录迭代器所在下标
				size_t len = pos - _start;
				size_t newCapacity = capacity() ? capacity() * 2 : 4;
				reserve(newCapacity);
				//更新迭代器位置，防止迭代器失效
				pos = _start + len;
			}

			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				end--;
			}
			
			*pos = value;
			_finish++;
		}

		//删接口
		//任意位置删除
		iterator erase(iterator pos)
		{
			iterator it = pos + 1;
			while (it != _finish)
			{
				*(it - 1) = *it;
				++it;
			}

			--_finish;

			return pos;
		}

		//尾删
		void pop_back(void)
		{
			--_finish;
		}

		//扩容
		void reserve(size_t n)
		{
			if (n > size())
			{
				size_t sz = size();
				T* temp = new T[n];
				
				//是否需要拷贝数据
				if (nullptr != _start)
				{
					for (size_t i = 0; i < sz; i++)
					{
						temp[i] = _start[i];
					}
				}

				delete[] _start;
				_start = temp;
				_finish = _start + sz;
				_endOfStorage = _start + n;
			}
		}

		//调整大小
		void resize(size_t n, const T& value = T())
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				if (n >= capacity())
				{
					reserve(n);
				}

				while (_start + n > _finish)
				{
					*_finish = value;
					++_finish;
				}
			}
		}

		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endOfStorage, v._endOfStorage);
		}

		size_t size(void)const
		{
			return _finish - _start;
		}

		size_t capacity(void)const
		{
			return _endOfStorage - _start;
		}

		void clear(void)
		{
			_finish = _start;
		}
	};


	template <class Con>
	void Print(const Con& v)
	{
		typename Con::const_iterator it = v.begin();
		while (it != v.end())
		{
			std::cout << *it << ' ';
			++it;
		}

		std::cout << std::endl;
	}

	void Test1(void)
	{
		vector<int> v1;
		//v1.resize(100, 2);
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		//v1.push_back(5);
		vector<int>::iterator pos = std::find(v1.begin(), v1.end(), 2);
		//v1.insert(pos, 50);
		v1.erase(pos);

		Print(v1);

		vector<int> v2(v1);
		v2[1] = 20;
		v2.clear();
		Print(v2);

		std::cout << v1.size() << std::endl;
		std::cout << v1.capacity() << std::endl;
	}
}

#endif