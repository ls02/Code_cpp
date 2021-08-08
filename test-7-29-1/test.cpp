#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

inline int GetMothDay(int year, int month)
{
    int arr[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int day = arr[month];

    if (month == 2 && (!(year % 400)) && (year % 100) || !(year % 4))
    {
        day++;
    }

    return day;
}

int main()
{
    int m = 0;
    int year = 0;
    int month = 1;
    int day = 1;
    int n = 0;

    cin >> m;

    while (m--)
    {
        cin >> year >> month >> day >> n;

        day += n;
        while (day > GetMothDay(year, month))
        {
            day -= GetMothDay(year, month);
            month++;

            if (month > 12)
            {
                year++;
                month = 1;
            }
        }

        printf("%04d-%02d-%02d\n", year, month, day);

    }

    return 0;
}

