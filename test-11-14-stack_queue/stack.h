#pragma once
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

namespace ls
{
	//ÈÝÆ÷ÊÊÅäÆ÷
	template <class T, class Container = std::vector<T>>
	class stack
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_back();
		}

		T top()
		{
			return _con.back();
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