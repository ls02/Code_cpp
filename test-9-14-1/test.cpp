#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
/*

*˼·��

* 1. Ҫ����������

* 2. Ҫ���������Ƿ����

*/

class Solution {

public:



    int StrToInt(std::string str)

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