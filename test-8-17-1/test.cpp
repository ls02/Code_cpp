//#define _CRT_SECURE_NO_WARNINGS 1
//
//#include <iostream>
//using namespace std;
//
//class Date
//{
//public:
//	void Init(int year, int month, int day)
//	{
//		this->year = year;
//		this->month = month;
//		this->day = day;
//	}
//
//private:
//	int year;
//	int month;
//	int day;
//};
//int main()
//{
//	Date d1;
//	d1.Init(2021, 2, 3);
//
//	return 0;
//}
//
////class Date
////{
////public:
////	void Init(int year, int month, int day)
////	{
////		_year = year;
////		_month = month;
////		_day = day;
////	}
////
////private:
////	int _year;
////	int _month;
////	int _day;
////};
////
////int main()
////{
////	Date d1;
////	d1.Init(2021, 2, 3);
////
////	return 0;
////}
//
////class Date
////{
////public:
////	void Init(int year, int month, int day)
////	{
////		Date::year = year;
////		Date::month = month;
////		Date::day = day;
////	}
////
////private:
////	int year;
////	int month;
////	int day;
////};
////
////int main()
////{
////	Date d1;
////	d1.Init(2021, 2, 3);
////
////	return 0;
////}
//
////void f(int p)
////{
////    cout << "(int)p" << endl;
////}
////
////void f(void* p)
////{
////    cout << "(void*)p" << endl;
////}
////
////
////
////int main()
////{
////    f(0);
////    f(NULL);
////    f(nullptr);
////
////    return 0;
////}
////int main()
//
////{
////    int arr[] = { 1, 2, 3, 4 };
////
////    for (auto& i : arr)
////    {
////        i *= 2;
////    }
////
////    for (auto i : arr)
////    {
////        cout << i << endl;
////    }
////
////    return 0;
////}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int input = 0;
	int arr[2] = { 0 };
	printf("%d\n", arr[0]);

	do
	{
		printf("***1,�ӷ���2������***\n");
		printf("***3,�˷���4������***\n");
		printf("***5,������ ***\n");
		printf("***  0. �˳����� ***\n");

		printf(" ��ү����>:");
		scanf("%d", &input);
		int a = 0;
		int b = 0;
		scanf("%d%d", &a, &b);
		switch (input)

		{
		case 1:

			printf("%d\n", a + b);
			arr[0] = a + b;
			break;
		case 2:
			printf("%d\n", a - b);
			arr[1] = a - b;
			break;
		case 3:
			printf("%d\n", a * b);
			arr[0] = a * b;
			break;
		case 4:
			printf("%d\n", a / b);
			arr[1] = a / b;
			break;
		case 5:
			//printf("%d %d\n", arr[0], arr[1]);
			printf("1");
			break;
		case 0:
			printf("��ү��\n");
			break;
		default:
			printf("ɵ�ƣ�����˲�֪����\n");

		}
	} while (input);

	return 0;
}