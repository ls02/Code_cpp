#include <iostream>

int main(void)
{
	int arr[]{ 2, 3, 4, 5 };
	int a{ 3 };
	const int& r1 = 30;
	int&& r2 = std::move(a);

	for (auto e : arr)
	{
		std::cout << e << std::endl;
	}

	std::cout << a << std::endl;
	std::cout << r1;

	return 0;

}