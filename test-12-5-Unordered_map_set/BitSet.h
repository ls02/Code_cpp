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

		//��xӳ���λ��ǳ�1�������������,�˴���������vector�Ĳ���
		void Set(size_t x)
		{
			//���xӳ���λ�ڵڼ�������
			//���xӳ���λ����������ĵڼ���λ
			size_t i = x / 32;//����ڵڼ�������
			size_t j = x % 32;//����ڵڼ����ֽ�
			
			_bits[i] |= (1 << j);
		}

		//ɾ��
		void Reset(size_t x)
		{
			size_t i = x / 32;
			size_t j = x % 32;

			_bits[i] &= (~(1 << j));
		}

		//���x�Ƿ����
		bool Test(size_t x)
		{
			size_t i = x / 32;
			size_t j = x % 32;

			// �����jλ��1������Ƿ�0����0������
			// �����jΪ��0�������0��0���Ǽ�
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