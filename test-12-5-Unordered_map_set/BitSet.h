#pragma once
#include <iostream>
#include <vector>

using namespace std;

namespace ls
{
	template <size_t N>
	class BitSet
	{
	public:
		BitSet()
		{
			_bits.resize(N / 32 + 1, 0);
		}

		//把x映射的位标记成1，代表有这个数,此处可以理解成vector的插入
		void Set(size_t x)
		{
			//算出x映射的位在第几个整数
			//算出x映射的位在这个整数的第几个位
			size_t i = x / 32;//算出在第几个整数
			size_t j = x % 32;//算出在第几个字节
			
			_bits[i] |= (1 << j);
		}

		//删除
		void Reset(size_t x)
		{
			size_t i = x / 32;
			size_t j = x % 32;

			_bits[i] &= (~(1 << j));
		}

		//检查x是否存在
		bool Test(size_t x)
		{
			size_t i = x / 32;
			size_t j = x % 32;

			// 如果第j位是1，结果是非0，非0就是真
			// 如果第j为是0，结果是0，0就是假
			return _bits[i] & (1 << j);
		}

		size_t size()
		{
			size_t i = 0;
			size_t j = 0;
			size_t count = 0;

			for (i = 0; i < _bits.size(); i++)
			{
				for (j = 0; j < 32; j++)
				{
					if (_bits[i] & (1 << j))
					{
						count++;
					}
				}
			}

			return count;
		}

	private:
		vector<int> _bits;
	};
}