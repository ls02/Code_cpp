#include <stdio.h>

//����(���ࣩ
class A
{
private:
	int _a = 1;
};

//B�̳�A���̳з�ʽ�ǹ��м̳�
//B�������ࣨ���ࣩ
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