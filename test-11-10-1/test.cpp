#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	v1.push_back(6);

	auto it = v1.begin();

	while (it != v1.end())
	{
		if (*it % 2 == 0)
		{
			it = v1.erase(it);
		}
		else
		{
			it++;
		}
	}

	it = v1.begin();

	while (it != v1.end())
	{
		cout << *it << ' ';
		it++;
	}

	cout << '\n';

	return 0;
}