#include "HashTable.h"

int main()
{
	int a[] = { 1, 5, 10, 100000, 100, 18, 15, 7 };

	for (auto e : a)
	{
		ht.Insert(make_pair(e, e));
	}

	ht.Erase(1);

	auto ret = ht.Find(1);

	if (nullptr != ret)
	{
		cout << "�ҵ���" << endl;
	}
	else
	{
		cout << "û�ҵ�" << endl;
	}

	return 0;
}