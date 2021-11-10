#define _CRT_SECURE_NO_WARNINGS 1
#include "string.h"

void test_string1()
{
	ls::string s1("Hello world");
	ls::string s2("Hello world");

	//cout << "s1:" << s1.c_str() << endl;

	//s1.push_back('!');
	//cout << "s1:" << s1.c_str() << endl;

	//s1.insert(s1.size(), 'c');
	//cout << "s1:" << s1.c_str() << endl;

	s1.insert(s1.size(), "!!!");
	cout << "s1:" << s1.c_str() << endl;

	s1.append("hello");
	cout << "s1:" << s1.c_str() << endl;

	//s1.erase();
	//cout << "s1:" << s1.c_str() << endl;


	cout << "s1:" << s1.c_str() << endl;
}

void test_string2()
{
	//ls::string s1("ac");
	//ls::string s2("ae");

	//cout << (s1 <= s2);

	ls::string s1("abc");

	s1.insert(3, 2, 'x');
	cout << s1.c_str() << endl;
}

//int main()
//{
//	//std::string s3;
//	//ls::string s1("hello world");
//	//ls::string s2("a");
//	//ls::string s4;
//
//	//cout << s1.c_str() << endl;
//	//cout << s2.c_str() << endl;
//
//	//test_string1();
//	test_string2();
//
//	return 0;
//}

int main()
{
	std::string s1("hello world");

	s1.insert(0, 10, 'x');
	cout << s1.c_str() << endl;


	return 0;
}