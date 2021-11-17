#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>

using namespace std;

//基类
class book
{
public:
	book(const string& name = "百草园")
		:_name(name)
	{}
	void func()
	{
		cout << "book:func();" << endl;
	}

	book& operator=(book& b)
	{
		_name = b._name;

		return *this;
	}
private:
	string _name;
};

//派生类
class A :public book
{
public:
	A(int a = 1, const string name = "百草园")
		:_a(a)
		,book(name)
	{}

	A& operator=(book& b)
	{
		book::operator=(b);

		return *this;
	}

	void func()
	{
		cout << "A:func();" << endl;
	}
private:
	int _a;
};

void test1()
{
	A a;
	book b("三味书屋");
	b = a;
}

int main()
{
	test1();
	//A a(1, "百草园");

	return 0;
}