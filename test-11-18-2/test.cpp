#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

//class Book
//{
//public:
//	virtual void fun()
//	{
//		cout << "vip用户" << endl;
//	}
//};
//
//class A :public Book
//{
//public:
//	virtual void fun()
//	{
//		cout << "普通用户" << endl;
//	}
//};

class Book
{};

class A :public Book
{};

class B
{
public:
	virtual A* f()
	{
		cout << "普通用户" << endl;

		return new A;
	}
};

class C
{
public:
	virtual Book* f()
	{
		cout << "vip用户" << endl;

		return new Book;
	}
};


int main()
{
	Book bo;
	A a;

	B b;
	C c;

	b.f();
	c.f();

	//a.fun();
	//b.fun();

	return 0;
}