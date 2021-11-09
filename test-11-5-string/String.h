#pragma once
#include <iostream>
#include <assert.h>
//#include <string>


namespace ls
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		const const_iterator begin()const
		{
			return _str;
		}

		const const_iterator end()const
		{
			return _str + _size;
		}

		string(const char* str = "")
		{
			_size = std::strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		//传统写法
		//string(const string& s)
		//	:_str(new char[std::strlen(s._str) + 1])
		//{
		//	strcpy(_str, s._str);
		//}

		//string& operator=(const string& s)
		//{
		//	if (this != &s)
		//	{
		//		delete[] _str;
		//		_str = new char[std::strlen(s._str) + 1];
		//		strcpy(_str, s._str);
		//	}

		//	return *this;
		//}

		//现代写法
		string(const string& s)
			:_str(nullptr)
			,_size(0)
			,_capacity(0)
		{
			string temp(s._str);
			swap(temp);
		}

		string& operator=(string s)
		{
			swap(s);
			return *this;
		}

		//遍历
		const char& operator[](size_t i) const
		{
			assert(i < _size);

			return _str[i];
		}

		char& operator[](size_t i)
		{
			assert(i < _size);

			return _str[i];
		}

		size_t size() const
		{
			return _size;
		}

		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}

		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* temp = new char[n + 1];
				std::strncpy(temp, _str, _size + 1);
				delete[] _str;
				_str = temp;
				_capacity = n;
			}
		}

		void resize(size_t n, char val = '\0')
		{
			if (n < _size)
			{
				_str[n] = val;
			}
			else
			{
				if (n > _capacity)
				{
					reserve(n);
				}

				for (size_t i = _size; i < n; i++)
				{
					_str[i] = val;
				}

				_size = n;
				_str[n] = '\0';
			}
		}

		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}

			_str[_size] = ch;
			_str[_size + 1] = '\0';
			++_size;
		}

		void append(const char* str)
		{
			size_t len = _size + std::strlen(str);

			if (len > _capacity)
			{
				reserve(len);
			}
			std::strcpy(_str + _size, str);
			_size = len;
		}

		string& insert(size_t pos, char ch)
		{
			assert(pos <= _size);

			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}

			size_t end = _size + 1;

			while (end > pos)
			{
				_str[end] = _str[end - 1];
				--end;
			}
			_str[pos] = ch;
			_size++;
			
			return *this;
		}

		string& insert(size_t pos, const char* str)
		{
			assert(pos <= _size);
			
			//计算str的长度
			int len = std::strlen(str);

			//判断是否需要扩容
			if (_size + len >= _capacity)
			{
				reserve(_size + len);
			}

			char* end = _str + _size;

			while (end >= _str + pos)
			{
				*(end + len) = *end;
				--end;
			}

			std::strncpy(_str + pos, str, len);
			_size += len;

			return *this;
		}

		string& erase(size_t pos, size_t len = npos)
		{
			assert(pos <= _size);

			//leftlen是存储个删除字符的个数
			size_t leftlen = _size - pos;
			//如果len大于或等于leftlen说明是全删除
			if (len >= leftlen)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				std::strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}

			return *this;
		}

		size_t find(const char ch, size_t pos = 0)
		{
			assert(pos < _size);

			for (size_t i = pos; i < _size; i++)
			{
				if (_str[i] == ch)
				{
					return i;
				}
			}

			return npos;
		}

		size_t find(const char* str, size_t pos = 0)const
		{
			assert(pos < _size);

			const char* ret = std::strstr(_str + pos, str);

			if (ret)
			{
				return ret - _str;
			}
			else
			{
				return npos;
			}
		}

		//size_t rfind(const char ch, size_t pos = npos)const
		//{
		//	if (pos >= _size)
		//	{
		//		pos = _size - 1;
		//	}

		//	string temp(_str);
		//	int left = 0;
		//	int right = _size - 1;

		//	while (left < right)
		//	{
		//		std::swap(temp[left], temp[right]);

		//		left++;
		//		right--;
		//	}


		//	return _size - 1 - temp.find(ch, _size - pos - 1);
		//}

		size_t rfind(const char ch, size_t pos = npos)const
		{
			if (pos >= _size)
			{
				pos = _size - 1;
			}

			char* end = _str + pos;

			while (*end != ch)
			{
				--end;
			}

			return end - _str;
		}


		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}

		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}

		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}

		std::istream& getline(std::istream& in, string& s)
		{
			s.clear();
			char ch = 0;
			ch = in.get();

			while (ch != '\n')
			{
				s += ch;
				ch = in.get();
			}

			return in;
		}


		inline bool operator>(const string& s) const
		{
			return  std::strcmp(_str, s._str) > 0;
		}
		inline bool operator>=(const string& s) const
		{
			return *this > s || (*this == s);
		}
		inline bool operator<(const string& s) const
		{
			return !(*this >= s);
		}
		inline bool operator<=(const string& s) const
		{
			return !(*this > s);
		}
		inline bool operator==(const string& s) const
		{
			return std::strcmp(_str, s._str) == 0;

		}
		inline bool operator!=(const string& s) const
		{
			return !(*this == s);
		}

		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		const char* c_str()
		{
			return _str;
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		static const size_t npos; 
	};

	const size_t string::npos = -1;


	std::ostream& operator<<(std::ostream& out, const string& s)
	{
		for (auto ch : s)
		{
			out << ch;
		}

		return out;
	}

	std::istream& operator>>(std::istream& in, string& s)
	{
		s.clear();
		char ch = 0;
		ch = in.get();

		while (ch != ' ' && ch != '\n')
		{
			s += ch;
			ch = in.get();
		}

		return in;
	}

	void test_string1()
	{
		ls::string s1("Hello world");
		ls::string s2;
		s2 = s1;


		std::cout << s1.c_str() << std::endl;
		std::cout << s2.c_str() << std::endl;
		
	}


	void test_string2()
	{
		string s1("Hello world");
		//s1[1] = 'c';
		size_t i = 0;

		s1[0] = 'c';
		for (i = 0; i < s1.size(); i++)
		{
			std::cout << s1[i];
		}

		//std::cout << s1.c_str() << std::endl;
	}

	void test_string3()
	{
		string s1("Hello world");
		string::iterator it = s1.begin();

		while (it != s1.end())
		{
			std::cout << *it << ' ';
			++it;
		}
	}

	void test_string4()
	{
		string s1("hello");
		s1 += " wolrd";
		s1.push_back('#');

		std::cout << s1.c_str() << std::endl;
	}

	void test_string5()
	{
		string s1("ac");
		string s2("ab");
		
		std::cout << (s1 != s2) << std::endl;;
	}

	void test_string6()
	{
		string s1("ab");

		s1.resize(5, 'c');

		std::cout << s1.c_str();
	}

	void test_string7()
	{
		string s1("hello world hello");
		std::string s2("hello world hello");
		//char a[] = "aaa";

		//s1.insert(0, "ddd");
		//s1.erase(2);


		//std::cout << s1.c_str();

		//size_t i = s1.find("llo");

		//std::cout << i;

		//std::cout << s1;

		//size_t ret = s1.rfind('o', 2);
		size_t ret1 = s1.rfind("hello");
		size_t ret2 = s2.rfind("hello");

		//size_t ret1 = s1.rfind('o', 4);
		//size_t ret2 = s2.rfind('o', 4);

		std::cout << "ret1" << ':' <<  ret1 << std::endl;
		std::cout << "ret2" << ':' << ret2 << std::endl;

		std::cout << "s1[ret1]" << ':' << s1[ret1] << std::endl;
		std::cout << "s1[ret2]" << ':' << s1[ret2] << std::endl;
	}
}