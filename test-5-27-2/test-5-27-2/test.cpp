#include <iostream>

using namespace std;

inline int add(int& a, int& b)
{
	return a + b;
}

int main()
{
	int a = 10;
	int b = 20;
	int ret = 0;

	ret = add(a, b);

	return 0;
}