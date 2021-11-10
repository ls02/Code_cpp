#pragma once
#include <iostream>
#include <assert.h>
#include <string>

using std::cout;
using std::cin;
using std::endl;

namespace ls
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		//默认构造函数
		//拷贝构造函数
		string(const string& s);
		//构造函数
		string(const char* str = "");
		string& operator=(string s);
		//析构函数
		~string();

		//获取_str的地址
		const char* c_str();

		//this和s交换对象内的所有成员
		void swap(string& s);

		//获取size
		size_t size();

		//扩容
		void reserve(size_t n);

		//清空字符串
		void clear();

		//比较大小
		bool operator>(const string& s)const;
		bool operator>=(const string& s)const;
		bool operator<(const string& s)const;
		bool operator<=(const string& s)const;
		bool operator==(const string& s)const;
		bool operator!=(const string& s)const;

		//增接口
		void push_back(char ch);
		string& insert(size_t pos, const char* str);
		string& insert(size_t pos, size_t n, const char ch);
		void append(const char* str);
		string& operator+=(const string& s);
		string& operator+=(const char ch);
		string& operator+=(const char* str);

		//删接口
		string& erase(size_t pos = 0, size_t len = npos);

		//查接口
		size_t find(const char* str, size_t pos = 0)const;
		size_t find(const char ch, size_t pos = 0)const;
		//反向查接口
		size_t rfind(const char ch, size_t pos = npos)const;

		//迭代器
		iterator begin();
		const const_iterator begin()const;
		iterator end();
		const const_iterator end()const;

		//改接口
		char& operator[](size_t i);
		const char& operator[](size_t i)const;

		//输入函数
		std::istream& getline(std::istream& in, string& s);

	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		static const size_t npos;
	};

	//输入函数
	std::istream& operator>>(std::istream& in, string& s);

	//输出函数
	std::ostream& operator<<(std::ostream& out, const string& s);
}