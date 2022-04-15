#include <iostream>
#include <string>

class A
{
public:
	virtual void Test(void) = 0
	{
		std::cout << "A" << std::endl;
	}
};

class B : public A
{
public:
	virtual void Test(void)
	{
		std::cout << "B" << std::endl;
	}
};

int main(void)
{
	A* pb = new B;
	pb->Test();

	return 0;
}

//class A
//{
//public:
//	virtual ~A(void)
//	{
//		std::cout << "~A" << std::endl;
//	}
//};
//
//class B : public A
//{
//public:
//	virtual ~B(void)
//	{
//		std::cout << "B" << std::endl;
//	}
//};
//
//int main(void)
//{
//	A* pa = new A;
//	A* pb = new B;
//
//	delete pa;
//	delete pb;
//
//	return 0;
//}

//class A
//{
//public:
//	virtual A& Func(void)
//	{
//		std::cout << "A" << std::endl;
//
//		return *this;
//	}
//};
//
//class B : public A
//{
//public:
//	virtual B& Func(void)
//	{
//		std::cout << "B" << std::endl;
//
//		return *this;
//	}
//};
//
//void Test(A& a)
//{
//	a.Func();
//}
//
//int main(void)
//{
//	A a;
//	B b;
//
//	Test(a);
//	Test(b);
//
//	return 0;
//}

//class People
//{
//public:
//	//虚函数的定义
//	virtual void Func(void)
//	{
//		std::cout << "普通人——全价票" << std::endl;
//	}
//private:
//	std::string sex;
//	short age;
//};
//
//class Students : public People
//{
//public:
//	//子类重写父类的虚函数
//	virtual void Func(void)
//	{
//		std::cout << "学生——半价票" << std::endl;
//	}
//};
//
//
//class Soldier : public People
//{
//public:
//	//子类重写父类的虚函数
//	virtual void Func(void)
//	{
//		std::cout << "军人——优先购票" << std::endl;
//	}
//};
//
//void Test1(People& rp)
//{
//	rp.Func();
//}
//
//int main(void)
//{
//	People p;
//	Students s;
//	Soldier so;
//
//	Test1(p);
//	Test1(s);
//	Test1(so);
//
//	return 0;
//}

//class A
//{
//public:
//	//A(int a = 10)
//	//{
//	//	_a = a;
//	//}
//private:
//	int _a = 1;
//};
//
//class B : virtual public A
//{
//public:
//	//B(int b = 20)
//	//	:A::A(100)
//	//{
//	//	_b = b;
//	//}
//private:
//	int _b = 2;
//};
//
//class C : virtual public A 
//{
//private:
//	int _c = 3;
//};
//
//class D : public B, public C
//{
//private:
//	int _d = 4;
//};
//
//void Test1(void)
//{
//	A a;
//	B b;
//	a = b;
//	A* pa = &b;
//	A& ra = b;
//}
//
//void Test2(void)
//{
//	D d;
//}
//
//int main(void)
//{
//	Test2();
//	//Test1();
//
//
//	return 0;
//}