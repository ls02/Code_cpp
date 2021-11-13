#pragma once
#include <iostream>
#include <assert.h>
#include <algorithm>

using std::cout;
using std::endl;
using std::cin;

namespace ls
{
	template<class T>
	
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{}

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

		vector(size_t n, T& v)
		{

		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		//传统写法
		//vector<T>& operator=(const vector<T>& v)
		//{
		//	if (this != &v)
		//	{
		//		delete[] _start;
		//		_start = new T[v.capacity()];
		//		std::memcpy(_start, v._start, sizeof(T) * v.size());
		//		_finish = _start + v.size();
		//		_endofstorage = _start + v.capacity();
		//	}

		//	return *this;
		//}


		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}

		//现代写法
		vector<T>& operator=(vector<T> v)
		{
			swap(v);

			return *this;
		}


		~vector()
		{
			if (_start)
			{
				delete[] _start;
			}

			_start = _finish = _endofstorage = nullptr;
		}

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

		size_t capacity()const
		{
			return _endofstorage - _start;
		}

		size_t size()const
		{
			return _finish - _start;
		}

		T& operator[](size_t i)
		{
			assert(i < size());

			return _start[i];
		}

		const T& operator[](size_t i)const
		{
			assert(i < size());

			return _start[i];
		}

		bool empty()const
		{
			return _start == _finish;
		}

		void pop_back()
		{
			assert(!empty());

			--_finish;
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				T* tmp = new T[n];
				size_t sz = size();

				if (_start)
				{
					//std::memcpy(tmp, _start, sz * sizeof(T));
					for (size_t i = 0; i < sz; i++)
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
				}
				_start = tmp;
				_finish = _start + sz;
				_endofstorage = _start + n;
			}
		}

		//这里的缺省参数是匿名对象，匿名对象如果是int类型就会默认生成0
		void rsize(size_t n, T val = T())
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				if (n > capacity())
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


		void push_back(const T& x)
		{
			if (_finish == _endofstorage)
			{
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
			}
			*_finish = x;
			++_finish;
		}

		void insert(iterator pos, const T& x)
		{
			if (_finish == _endofstorage)
			{
				size_t len = pos - _start;
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);

				//更新pos解决增容后pos失效的问题
				pos = len + _start;
			}

			iterator end = _finish - 1;

			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = x;
			++_finish;

		}

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

	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};

	template<class Con>
	void Printfvector(const Con& v)
	{
		typename Con::const_iterator it = v.begin();

		while (it != v.end())
		{
			cout << *it << ' ';
			++it;
		}

		cout << '\n';
	}

	void test_vector1()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);

		vector<int>::iterator it = v1.begin();

		while (it != v1.end())
		{
			cout << *it << ' ';
			++it;
		}
	}

	void test_vector2()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);

		v1.rsize(2);
		Printfvector(v1);

		v1.rsize(6);
		Printfvector(v1);

		v1.rsize(10);
		Printfvector(v1);
	}

	void test_vector3()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);
		v1.push_back(6);
		v1.push_back(7);
		Printfvector(v1);

		vector<int>::iterator pos = std::find(v1.begin(), v1.end(), 3);
		v1.insert(pos, 30);
		Printfvector(v1);
	}

	void test_vector4()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		Printfvector(v1);

		vector<int> v2(v1);
		Printfvector(v2);

		vector<int> v3;
		//v3.swap(v1);
		v3 = v2;
		Printfvector(v3);
	}

	void test_vector5()
	{
		vector<std::string> v1;
		v1.push_back("11111");
		v1.push_back("22222222");
		v1.push_back("33333333333");
		//vector<int> v1;
		//v1.push_back(1);
		//v1.push_back(2);
		//v1.push_back(3);

		Printfvector(v1);

		//vector<std::string>::iterator it = v1.begin();
		//while (it != v1.end())
		//{
		//	cout << *it << ' ';
		//	it++;
		//}

	}
}
