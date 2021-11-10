#define _CRT_SECURE_NO_WARNINGS 1
#include "string.h"

const size_t ls::string::npos = -1;


ls::string::string(const string& s)
	//初始化列表是必要的，因为不初始化成nullptr，到时候交换的时候空间
	//自动销毁的时候会出问题
	:_str(nullptr)
	,_size(0)
	,_capacity(0)
{
	//通过构造函数来完成对象的初始化，此时的temp是this想要的
	string temp(s);
	//一交换即可达到目的，而空给temp，temp是局部变量一出函数会在自动销毁
	swap(temp);
}

ls::string::string(const char* str)
{
	if (str == nullptr)
	{
		assert(false);

		return;
	}
	//计算出str的大小
	_size = std::strlen(str);
	_capacity = _size;
	//开_size加1的空间，因为要给'\0'预留位置，而size显示的是可用空间
	_str = new char[_size + 1];
	//拷贝str的内容到_str
	std::strcpy(_str, str);
}

ls::string::~string()
{
	delete[] _str;
	_str = nullptr;
	_size = _capacity = 0;
}

void ls::string::swap(string& s)
{
	std::swap(_str, s._str);
	std::swap(_size, s._size);
	std::swap(_capacity, s._capacity);
}

ls::string &ls::string:: operator=(string s)
{
	swap(s);

	return *this;
}

const char* ls::string:: c_str()
{
	return _str;
}

void ls::string::reserve(size_t n)
{
	//如果不大于_capacity我们就不增容
	if (n > _capacity)
	{
		char* temp = new char[n];
		std::strcpy(temp, _str);
		delete[] _str;
		_str = temp;
		_capacity = n;
	}
}

void ls::string::push_back(char ch)
{
	//先判断是否需要扩容
	if (_capacity == _size)
	{
		reserve(_capacity == 0 ? 4 : 2 * _capacity);
	}

	_str[_size] = ch;
	_str[_size + 1] = '\0';
	_size++;
}

ls::string& ls::string::insert(size_t pos, size_t n,  const char ch)
{
	assert(pos <= _size);
	if (_size == _capacity)
	{
		reserve(_capacity == 0 ? 4 : 2 * _capacity);
	}

	char* end = _str + _size;

	while (end >= _str + pos)
	{
		*(end + n) = *end;
		end--;
	}

	for (size_t i = 0; i < n; i++)
	{
		_str[pos + i] = ch;
	}

	_size += n;
	if (_size == _capacity)
	{
		reserve(_capacity == 0 ? 4 : 2 * _capacity);
	}

	return *this;
}

ls::string& ls::string::insert(size_t pos, const char* str)
{
	assert(pos <= _size);

	size_t len = std::strlen(str);
	if (_size + len >= _capacity)
	{
		reserve(_capacity == 0 ? 4 : 2 * _capacity);
	}

	char* end = _str + _size;

	while (end >= _str + pos)
	{
		*(end + len) = *end;
		end--;
	}

	std::strncpy(_str + pos, str, len);
	_size += len;

	return *this;
}

void ls::string::append(const char* str)
{
	size_t len = std::strlen(str);

	if (_size == _capacity)
	{
		reserve(_capacity == 0 ? 4 : 2 * _capacity);
	}

	std::strcpy(_str + _size, str);
	_size += len;
}

size_t ls::string::size()
{
	return _size;
}

ls::string& ls::string::operator+=(const char ch)
{
	push_back(ch);
	
	return *this;
}
ls::string& ls::string::operator+=(const string& s)
{
	append(s._str);

	return *this;
}
ls::string& ls::string::operator+=(const char* str)
{
	append(str);

	return *this;
}

ls::string& ls::string::erase(size_t pos, size_t len)
{
	if (len > _size)
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

size_t ls::string::find(const char ch, size_t pos)const
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

size_t ls::string::find(const char* str, size_t pos)const
{
	assert(pos < _size);
	char* ret = strstr(_str, str);

	if (ret)
	{
		return ret - _str;
	}
	else
	{
		return npos;
	}
}

size_t ls::string::rfind(const char ch, size_t pos)const
{
	assert(pos < _size);
	int left = 0;
	int right = _size - 1;

	while (left < right)
	{
		std::swap(_str[left], _str[right]);
		left++;
		right--;
	}

	return _size - 1 - find(ch, _size - 1 - pos);
}

ls::string::iterator ls::string::begin()
{
	return _str;
}

const ls::string::const_iterator ls::string::begin()const
{
	return _str;
}

ls::string::iterator ls::string::end()
{
	return _str + _size;
}

const ls::string::const_iterator ls::string::end()const
{
	return _str + _size;
}

void ls::string::clear()
{
	_str[0] = 0;
	_size = 0;
}


std::istream& ls::string::getline(std::istream& in, string& s)
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

bool ls::string::operator>(const string& s)const
{
	return std::strcmp(_str, s._str) > 0;
}

bool ls::string::operator>=(const string& s)const
{
	return *this > s || *this == s;
}
bool ls::string::operator<(const string& s)const
{
	return !(*this >= s);
}
bool ls::string::operator<=(const string& s)const
{
	return !(*this > s);
}
bool ls::string::operator==(const string& s)const
{
	return std::strcmp(_str, s._str) == 0;
}
bool ls::string::operator!=(const string& s)const
{
	return !(*this == s);
}

std::istream& ls::operator>>(std::istream& in, ls::string& s)
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

std::ostream& ls::operator<<(std::ostream& out, const ls::string& s)
{
	for (auto ch : s)
	{
		out << ch;
	}

	return out;
}

char& ls::string::operator[](size_t i)
{
	assert(i < _size);

	return _str[i];
}

const char& ls::string::operator[](size_t i)const
{
	assert(i < _size);

	return _str[i];
}