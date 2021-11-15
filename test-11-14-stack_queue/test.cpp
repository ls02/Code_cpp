#define _CRT_SECURE_NO_WARNINGS 1
#include "stack.h"
#include "queue.h"

void test_stack()
{
	ls::stack<int> s1;

	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);
	s1.push(5);
	
	while (!s1.empty())
	{
		cout << "stack:" << s1.top() << endl;
		s1.pop();
	}
}
void test_queue()
{
	ls::queue<int> q1;

	q1.push(1);
	q1.push(2);
	q1.push(3);
	q1.push(4);
	q1.push(5);

	while (!q1.empty())
	{
		cout << "queue:" << q1.front() << endl;
		q1.pop();
	}
}




//·Âº¯Êý
struct LessInt
{
	bool operator()(int l, int r)
	{
		return l < r;
	}
}


int main()
{
	//test_stack();
	test_queue();
	return 0;
}