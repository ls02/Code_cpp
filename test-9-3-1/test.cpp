#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

class A1
{
public:
	A1(int a)
		:_a1(_a2)
		,_a2(a)
	{}

	void Printf() const
	{
		cout << _a1 << " " << _a2 << endl;
	}
	
private:
	int _a1;
	int _a2;
};

int main()
{
	A1 a(1);
	a.Printf();

	return 0;
}