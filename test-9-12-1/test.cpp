#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

//int main()
//{
//	int* p1 = (int*)malloc(sizeof(int) * 4);
//	int* p2 = new int[4]{ 1, 2, 3, 4 };
//
//	int* p3 = (int*)malloc(sizeof(int));
//	int* p4 = new int(4);
//
//	return 0;
//}
//
//struct ListNode
//{
//	int* _next;
//	int* _prev;
//	int val;
//
//	ListNode()
//		:_next(nullptr),
//		_prev(nullptr),
//		val(0)
//	{}
//};
//
//int main()
//{
//	struct ListNode* p1 = (struct ListNode*)malloc(sizeof(struct ListNode));
//	struct ListNode* p2 = new struct ListNode;
//	int x = 0;
//	int y = 0;
//	y = ++x, ++x, ++x;
//
//	cout << x << endl;
//
//	return 0;
//}

//template<class T>
//void Swap(T& left, T& right)
//{
//	T temp = left;
//	left = right;
//	right = temp;
//}
//
//template<class A>
//A Add(const A& left, const A& right)
//{
//	return left + right;
//}
//
//int Add(const int left, const int right)
//{
//	return left + right;
//}
//
//int main()
//{
//	int a = 1;
//	int b = 1;
//	double c = 1.1;
//	double d = 2.2;
//
//	//������ͨ����ʵ�ε�����T��Ϊint��double
//	//���ַ�ʽ����ʽʵ����
//	cout << Add(a, b) << endl;
//	//��Ϊ�����Ǳ������ƣ����������ֲ�ͬ���ͱ������ֲ�����Ҫ���Ǹ�
//	//�������������ģ��Ϳ����ƣ�����ᱨ��
//	//cout << Add(a, c) << endl;
//
//	//���ñ�������������,��ʾָ������
//	//���ַ���������ʾʵ����
//	cout << Add<int>(a, b) << endl;
//
//	cout << Add<double>(a, c) << endl;
//
//	return 0;
//}

class ls
{
public:
	template<class T>
	class vector
	{
	public:
		vector()
			:_a(nullptr)
			, _size(0)
			, _capacity(0)
		{}

		void Push_Back(const T& val)
		{
			if (_size == _capacity)
			{
				int newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				T* tmp = new T[newcapacity];
				
				if (_a)
				{
					memcpy(tmp, _a, sizeof(T) * _size);
					delete[] _a;
				}
				_a = tmp;
				_capacity = newcapacity;
			}

			_a[_size] = val;
			_size++;
		}

		T& operator[](size_t pos)
		{
			return _a[pos];
		}
		
		size_t size()
		{
			return _size;
		}

		~vector()
		{
			delete[] _a;
			_a = nullptr;
			_size = _capacity = 0;
		}

	private:
		T* _a;
		size_t _size;
		size_t _capacity;
	};
};

int main()
{
	ls::vector<int> v1;
	v1.Push_Back(1);
	v1.Push_Back(2);
	v1.Push_Back(3);
	v1.Push_Back(4);
	v1.Push_Back(5);
	v1.Push_Back(6);

	for (size_t i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << ' ';
	}

	for (size_t i = 0; i < v1.size(); i++)
	{
		v1[i] *= 2;
	}

	putchar('\n');
	for (size_t i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << ' ';
	}

	return 0;
}