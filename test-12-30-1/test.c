#define _CRT_SECURE_NO_WARNINGS 1
#include "vector.h"


void TestVector1()
{
	Vector v1 = InitVector(4);

	PushBankVector(&v1, 10);
	PushBankVector(&v1, 20);
	PushBankVector(&v1, 30);
	PushBankVector(&v1, 40);
	PushBankVector(&v1, 50);
	InsertVector(&v1, 0, 2);
}

int main()
{
	TestVector1();

	return 0;
}