#pragma once
#include <iostream>
#include <vector>
#include <functional>

using std::cout;
using std::endl;


namespace ls
{
	//·Âº¯Êý
	template <class T>
	struct lees
	{
		bool operator()(const T& l, const T& r)
		{
			return l < r;
		}
	};

	template <class T>
	struct greater
	{
		bool operator()(const T& l, const T& r)
		{
			return l > r;
		}
	};

	template <class T, class Container = std::vector<int>, class Compare = lees<T>>
	class priority_queue
	{
	public:
		void AdjustUp(size_t child)
		{
			Compare com;
			size_t parent = (child - 1) / 2;

			while (child > 0)
			{
				//if (_con[parent] > _con[child])
				if(com(_con[parent], _con[child]))
				{
					std::swap(_con[parent], _con[child]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}

		void AdjustDwon(int parent)
		{
			Compare com;
			size_t child = parent * 2 + 1;

			while (child < _con.size())
			{
				//if (child + 1 < _con.size() && _con[child] > _con[child + 1])
				if (child + 1 < _con.size() && com(_con[child], _con[child + 1]))
				{
					++child;
				}

				//if (_con[parent] > _con[child])
				if (com(_con[child], _con[child + 1]))
				{
					std::swap(_con[parent], _con[child]);
					parent  = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}

		void push(const T& x)
		{
			_con.push_back(x);
			
			AdjustUp(_con.size() - 1);
		}

		void pop()
		{
			std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			AdjustDwon(0);
		}

		T front()
		{
			return _con[0];
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}
	private:
		Container _con;
	};
}