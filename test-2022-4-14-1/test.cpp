#include <stdio.h>

//基类(父类）
class A
{
private:
	int _a = 1;
};

//B继承A，继承方式是共有继承
//B是派生类（子类）
class B : public A
{
private:
	int _b = 2;
};

void Test1(void)
{
	A a;
	B b;
}

int main(void)
{
	Test1();

	return 0;
}