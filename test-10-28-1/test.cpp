#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>

using namespace std;

int main()
{
	std::string s1;
	std::string s2("abcd");

	std::cout << s1.length() << std::endl;
	std::cout << s2.length() << std::endl;


	std::string::iterator it = s2.begin();
	while (it != s2.end())
	{
		std::cout << *it << " ";
		it++;
	}

	std::cout << std::endl;

	std::string::reverse_iterator rit = s2.rbegin();
	while (rit != s2.rend())
	{
		std::cout << *rit << " ";
		rit++;
	}

	std::cout << std::endl;

	return 0;
}

/*

*思路：

* 1. 要考虑正负数

* 2. 要考虑数据是否溢出

*/

class Solution {

public:



    int StrToInt(string str)

    {

        int len = str.size();

        int flag = 1;

        if (len == 0)

            return 0;

        const char* cstr = str.c_str();

        if (cstr == NULL)

            return 0;

        int i = 0;

        if (cstr[i] == '+')

        {

            i++;

            flag = 1;//如果str[i]为'+'，str[i]顺序后移，并令标志flag为1，表示为正数   

        }

        else if (cstr[i] == '-')

        {

            i++;

            flag = -1;//如果str[i]为'-'，str[i]顺序后移，并令标志flag为-1，表示为负数   

        }

        long long num = 0;

        while (cstr[i] != '\0')

        {

            if (cstr[i] >= '0' && cstr[i] <= '9')

            {

                //每遍历一个在0-9间的字符，就将其输入到num中       

                num = num * 10 + (cstr[i] - '0');//下一次输入到num中时要加上上一次*10的结果，即上一次的数左移一位（十进制下） 



                //如果数据溢出，则返回0

                if ((flag > 0 && num > 0x7fffffff) || (flag < 0 && num>0x80000000))

                    return 0;

                i++;

            }

            else

            {

                return 0;

            }

        }

        if (flag < 0)

            num = num * -1;

        return (int)num;

    }

};

/*

*思路：

* 1. 忽略大小写，只考虑字母

* 2. 通过首尾比较的方式，判断其是否为回文

*/

class Solution {

public:

    bool isDigtalOrWord(char ch)

    {

        if ((ch >= '0' && ch <= '9')

            || (ch >= 'A' && ch <= 'Z')

            || (ch >= 'a' && ch <= 'z'))

            return true;

        return false;

    }

    bool isPalindrome(string s)

    {

        if (s.empty())

            return true;



        for (int i = 0; i < s.size(); ++i)

        {

            s[i] = tolower(s[i]); //忽略大小写      

        }



        int left = 0;

        int right = s.size() - 1;

        while (left < right)

        {

            //找到左边第一个未比较的字母

            while (left < right && !isDigtalOrWord(s[left]))

                left++;

            //找到右边第一个未比较的字母
            //: "A man, a plan, a canal: Panama"
            while (left < right && !isDigtalOrWord(s[right]))

                right--;

            //左右两边字母若不相等，则不是回文

            if (s[left] != s[right])

                return false;

            left++;

            right--;

        }

        return true;

    }

};