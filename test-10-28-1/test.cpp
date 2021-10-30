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

*˼·��

* 1. Ҫ����������

* 2. Ҫ���������Ƿ����

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

            flag = 1;//���str[i]Ϊ'+'��str[i]˳����ƣ������־flagΪ1����ʾΪ����   

        }

        else if (cstr[i] == '-')

        {

            i++;

            flag = -1;//���str[i]Ϊ'-'��str[i]˳����ƣ������־flagΪ-1����ʾΪ����   

        }

        long long num = 0;

        while (cstr[i] != '\0')

        {

            if (cstr[i] >= '0' && cstr[i] <= '9')

            {

                //ÿ����һ����0-9����ַ����ͽ������뵽num��       

                num = num * 10 + (cstr[i] - '0');//��һ�����뵽num��ʱҪ������һ��*10�Ľ��������һ�ε�������һλ��ʮ�����£� 



                //�������������򷵻�0

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

*˼·��

* 1. ���Դ�Сд��ֻ������ĸ

* 2. ͨ����β�Ƚϵķ�ʽ���ж����Ƿ�Ϊ����

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

            s[i] = tolower(s[i]); //���Դ�Сд      

        }



        int left = 0;

        int right = s.size() - 1;

        while (left < right)

        {

            //�ҵ���ߵ�һ��δ�Ƚϵ���ĸ

            while (left < right && !isDigtalOrWord(s[left]))

                left++;

            //�ҵ��ұߵ�һ��δ�Ƚϵ���ĸ
            //: "A man, a plan, a canal: Panama"
            while (left < right && !isDigtalOrWord(s[right]))

                right--;

            //����������ĸ������ȣ����ǻ���

            if (s[left] != s[right])

                return false;

            left++;

            right--;

        }

        return true;

    }

};