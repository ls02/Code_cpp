#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>

using namespace std;

class Book
{
public:
	Book(const string name = "�ٲ�԰")
		:_name(name)
	{}

	string _name;
};

class A :virtual public Book
{
public:
	A(int a = 1, const string name = "�ٲ�԰")
		:_a(a)
		,Book(name)
	{}

	int _a;
};

class B :virtual public Book
{
public:
	B(int b = 1, const string name = "�ٲ�԰")
		:_b(b)
		, Book(name)
	{}

	int _b;
};

class C :public A, public B
{
public:
	C(int c = 1, const string name = "�ٲ�԰")
		:_c(c)
	{}

	int _c;
};

int main()
{
	Book bo;
	A a;
	B b;
	C c;

	bo._name = "����";
	a._a = 1;
	b._b = 2;
	c._c = 3;

	return 0;
}