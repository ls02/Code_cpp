#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
	vector<int> v{ 1, 2, 3, 4, 5 };
	auto pos = find(v.begin(), v.end(), 3);
	v.reserve(100);
	*pos = 30;

	return 0;
}

//int main()
//{
//	vector<int> v{ 1, 2, 3, 4, 5 };
//
//	auto it = v.begin();
//	while (it != v.end())
//	{
//		if (!(*it % 2))
//		{
//			v.erase(it);
//		}
//
//		++it;
//	}
//
//
//	return 0;
//}
