#include <iostream>

int gcd(int a, int b)
{
    if (a % b == 0) return b;
    else return gcd(b, a % b);
}
int x, y;
int main() {

    std::cin >> x >> y;
    std::cout << gcd(x, y);

    return 0;
}

//int main(void)
//{
//	//std::cout << "hello" << std::endl;
//	int flag = 1;
//	double ret = 0.0;
//
//	for (int i = 1; i <= 100; i++)
//	{
//		ret += (double)flag / i;
//		flag *= -1;
//	}
//
//
//	std::cout << ret;
//
//	return 0;
//}