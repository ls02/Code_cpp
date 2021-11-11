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

	// ����˼�룺�ҳ�������ǵĹ��ɣ�����ÿһ��ͷβ����1���м��[j]����������һ��[j-1]+[j]

	vector<vector<int>> generate(int numRows)

	{

		vector<vector<int>> vv;

		// �ȿ���������ǵĿռ�

		vv.resize(numRows);

		for (int i = 1; i <= numRows; ++i)

		{

			vv[i - 1].resize(i, 0);

			// ÿһ�еĵ�һ�������һ������1

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


/*����:ʱ�临�Ӷ�ΪO(N)

*˼·��

* 1. ��������������õģ�ͨ����ѯÿһ�����ݵ��ظ�����

* 2. ���ظ��������ɾ����ֻ����һ�����ݼ���

*/

int removeDuplicates(int* nums, int numsSize)

{

	int src1 = 0, src2 = 1;

	int dst = 0;

	// �������˼·һ�£���ͬ����ֻ����һ����������ǰ��

	while (src2 < numsSize)
	{
		nums[dst] = nums[src1];

		++dst;

		//�������ָ��ָ���Ԫ�ز��ظ�����ָ��ͬʱ����ƶ�

		if (nums[src1] != nums[src2])

		{

			++src1;

			++src2;

		}
		else

		{
			//����ظ����ҵ���һ�����ظ���Ԫ��

			while (src2 < numsSize && nums[src1] == nums[src2])

			{

				++src2;

			}

			//����ָ��

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
