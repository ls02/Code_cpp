#include <iostream>

using namespace std;

int main()
{
	int a = 10;
	const int& b = a;

	return 0;
}




//int Add(int x, int y = 40)
//{
//	return x + y;
//}
//
//int main()
//{
//	int a = 50;
//	int& ra = a;
//
//	cout << "ra��" << ra << endl;
//	cout << "a��" << a << endl;
//
//	ra = 100;
//	cout << "ra��" << ra << endl;
//	cout << "a��" << a << endl;
//
//	return 0;
//}

//int main()
//{
//	int x = 100;
//	int y = 30;
//
//	cout << Add(x, y) << endl;//��ʵ�β�ʹ��ȱʡ����
//	cout << Add(x) << endl;//����ʵ��ʹ��Ĭ��ֵ
//
//	return 0;
//}

//int main()
//{
//	int x = 100;
//	int y = 30;
//
//	cout << Add(x, y) << endl;//��ʵ�β�ʹ��ȱʡ����
//	cout << Add() << endl;//����ʵ��ʹ��Ĭ��ֵ
//
//	return 0;
//}

//namespace ls
//{
//	int a = 30;//ls�ռ���
//}
//
//int a = 100;//ȫ����
//
//int main()
//{
//	int a = 200;//�ֲ���
//
//	cout << a << endl;//�����ָ���ռ�����ôʹ�õ��Ǿֲ�����Ϊ�ֲ�����
//	cout << ::a << endl;//ָ������������ʹ��ȫ����
//	cout << ls::a << endl;//ָ��ʹ��ĳ���ռ���
//
//	return 0;
//}