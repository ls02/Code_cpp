#pragma once
#ifndef __BITSET_H__
#define __BITSET_H__
#include <iostream>
#include <vector>
#include <assert.h>
#include <string>

namespace ls
{
	template<size_t N>
	class BitSet
	{
	private:
		std::vector<int> _bs;

	public:

		BitSet(void)
		{
			_bs.resize(N / 32 + 1, 0);
		}
		void Set(size_t x)
		{
			assert(x < N);

			size_t i = x / 32;
			size_t j = x % 32;

			_bs[i] |= (1 << j);
		}

		void RSet(size_t x)
		{
			assert(x < N);

			size_t i = x / 32;
			size_t j = x % 32;

			_bs[i] &= (~(1 << j));
		}

		bool Test(size_t x)
		{
			assert(x < N);

			size_t i = x / 32;
			size_t j = x % 32;

			return _bs[i] & (1 << j);
		}
	};
}

#endif