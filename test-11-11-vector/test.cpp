#define _CRT_SECURE_NO_WARNINGS 1
#include "vector.h"
#include <vector>
using namespace std;

int main()
{
	std::vector < int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);

	vector<int>::iterator pos = find(v1.begin(), v1.end(), 2);

	if (pos != v1.end())
	{
		v1.insert(pos, 20);
	}
	for (auto e : v1)
	{
		cout << e << ' ';
	}
	cout << endl;

	//v1.erase(pos);
	cout << *pos;
	//for (auto e : v1)
	//{
	//	cout << e << ' ';
	//}
	//cout << endl;

	return 0;
}