#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

//class Book
//{
//public:
//	virtual void fun()
//	{
//		cout << "vip�û�" << endl;
//	}
//};
//
//class A :public Book
//{
//public:
//	virtual void fun()
//	{
//		cout << "��ͨ�û�" << endl;
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
		cout << "��ͨ�û�" << endl;

		return new A;
	}
};

class C
{
public:
	virtual Book* f()
	{
		cout << "vip�û�" << endl;

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