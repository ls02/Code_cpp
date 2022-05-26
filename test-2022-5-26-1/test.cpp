#include <iostream>

int main(void)
{
	int a = 5;
	int b = 2;
	auto f1 = [](int& a, int& b)->void
	{
		int temp = a;
		a = b;
		b = temp;
	};

	auto f2 = [&a, &b]
	{
		auto temp = a;
		a = b;
		b = temp;
	};

	f1(a, b);
	f2();

	auto f3 = [&]
	{
		auto temp = a;
		a = b;
		b = temp;
	};

	f3();

	std::cout << a << " " << b << std::endl;

	return 0;
}