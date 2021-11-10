#pragma once
#include <iostream>
#include <assert.h>
#include <string>

using std::cout;
using std::cin;
using std::endl;

namespace ls
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		//Ĭ�Ϲ��캯��
		//�������캯��
		string(const string& s);
		//���캯��
		string(const char* str = "");
		string& operator=(string s);
		//��������
		~string();

		//��ȡ_str�ĵ�ַ
		const char* c_str();

		//this��s���������ڵ����г�Ա
		void swap(string& s);

		//��ȡsize
		size_t size();

		//����
		void reserve(size_t n);

		//����ַ���
		void clear();

		//�Ƚϴ�С
		bool operator>(const string& s)const;
		bool operator>=(const string& s)const;
		bool operator<(const string& s)const;
		bool operator<=(const string& s)const;
		bool operator==(const string& s)const;
		bool operator!=(const string& s)const;

		//���ӿ�
		void push_back(char ch);
		string& insert(size_t pos, const char* str);
		string& insert(size_t pos, size_t n, const char ch);
		void append(const char* str);
		string& operator+=(const string& s);
		string& operator+=(const char ch);
		string& operator+=(const char* str);

		//ɾ�ӿ�
		string& erase(size_t pos = 0, size_t len = npos);

		//��ӿ�
		size_t find(const char* str, size_t pos = 0)const;
		size_t find(const char ch, size_t pos = 0)const;
		//�����ӿ�
		size_t rfind(const char ch, size_t pos = npos)const;

		//������
		iterator begin();
		const const_iterator begin()const;
		iterator end();
		const const_iterator end()const;

		//�Ľӿ�
		char& operator[](size_t i);
		const char& operator[](size_t i)const;

		//���뺯��
		std::istream& getline(std::istream& in, string& s);

	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		static const size_t npos;
	};

	//���뺯��
	std::istream& operator>>(std::istream& in, string& s);

	//�������
	std::ostream& operator<<(std::ostream& out, const string& s);
}