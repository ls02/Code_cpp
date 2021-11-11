#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	//vector<int> v1;
	//v1.push_back(1);
	//v1.push_back(2);
	//v1.push_back(3);
	//v1.push_back(4);
	//v1.push_back(5);

	//for (auto& v : v1)
	//{
	//	v ^= v + 1;
	//	cout << v << endl;
	//}

	vector<vector<int>> vv;

	vv.resize(5);

	for (size_t i = 0; i < vv.size(); i++)
	{
		vv[i].resize(i + 1);
	}

	for (size_t i = 0; i < vv.size(); i++)
	{
		vv[i][0] = vv[i][vv[i].size() - 1] = 1;
	}

	for (size_t i = 0; i < vv.size(); i++)
	{
		for (size_t j = 0; j < vv[i].size(); i++)
		{
			if (vv[i][j] == 0)
			{
				vv[i][j] = vv[i - 1][j - 1] + vv[i - 1][j];
			}
		}
	}

	return 0;
}

class Solution

{

public:

	// 核心思想：找出杨辉三角的规律，发现每一行头尾都是1，中间第[j]个数等于上一行[j-1]+[j]

	vector<vector<int>> generate(int numRows)

	{

		vector<vector<int>> vv;

		// 先开辟杨辉三角的空间

		vv.resize(numRows);

		for (int i = 1; i <= numRows; ++i)

		{

			vv[i - 1].resize(i, 0);

			// 每一行的第一个和最后一个都是1

			vv[i - 1][0] = 1;

			vv[i - 1][i - 1] = 1;

		}

		for (size_t i = 0; i < vv.size(); ++i)

		{

			for (size_t j = 0; j < vv[i].size(); ++j)

			{

				if (vv[i][j] == 0)

				{

					vv[i][j] = vv[i - 1][j - 1] + vv[i - 1][j];

				}

			}

		}

		return vv;

	}

};


/*方二:时间复杂度为O(N)

*思路：

* 1. 由于数据是排序好的，通过查询每一个数据的重复区间

* 2. 将重复区间进行删除，只保留一个数据即可

*/

int removeDuplicates(int* nums, int numsSize)

{

	int src1 = 0, src2 = 1;

	int dst = 0;

	// 跟上题的思路一致，相同的数只保留一个，依次往前放

	while (src2 < numsSize)
	{
		nums[dst] = nums[src1];

		++dst;

		//如果两个指针指向的元素不重复，则指针同时向后移动

		if (nums[src1] != nums[src2])

		{

			++src1;

			++src2;

		}
		else

		{
			//如果重复，找到第一个不重复的元素

			while (src2 < numsSize && nums[src1] == nums[src2])

			{

				++src2;

			}

			//更新指针

			src1 = src2;

			++src2;

		}

	}

	if (src1 < numsSize)

	{

		nums[dst] = nums[src1];

		++dst;

	}

	return dst;

}
