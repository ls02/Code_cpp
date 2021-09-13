#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>

using namespace std;

void Swap(char* p1, char* p2)
{
    char temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int main()
{
    char arr[20] = { 0 };
    int i = 0;
    int j = 0;
    int len = 0;

    gets_s(arr);

    //for (i = 0; i < 20; i++)
    //{
    //    if (arr[i] > arr[i + 1])
    //    {
    //        Swap(&arr + i, &arr);
    //    }
    //}

    len = strlen(arr);

    for (i = 0; i < len - 1; i++)
    {
        for (j = 0; j < len - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                Swap(arr + j, arr + j + 1);
            }
        }

    }

    //int left = 0;
    //int right = len - 1;

    //while (left < right)
    //{
    //    if (arr[left] > arr[right])
    //    {
    //        Swap(arr + left, arr + right);
    //    }

    //    left++;
    //    right--;
    //}

    puts(arr);

    return 0;
}