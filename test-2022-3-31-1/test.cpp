#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
using namespace std;
#include "winsock2.h"
#pragma comment(lib,"ws2_32.lib")
void main()
{
	undefined
		//��ʼ��:�������ʼ�������´��뽫�޷�ִ��
		WSAData data;
	if (WSAStartup(MAKEWORD(1, 1), &data) != 0)
	{
		undefined
			cout << "��ʼ������,�޷���ȡ������Ϣ..." << endl;
	}

	char host[255];
	//��ȡ������:Ҳ����ʹ��GetComputerName()�������
	if (gethostname(host, sizeof(host)) == SOCKET_ERROR)
	{
		undefined
			cout << "�޷���ȡ������..." << endl;
	}
	else
	{
		undefined
			cout << "�����������Ϊ:" << host << endl;
	}

	//��ȡ�����IP:gethostbynameҲ��Ҫ��ʼ��(�����ѳ�ʼ��)
	struct hostent* p = gethostbyname(host);
	if (p == 0)
	{
		undefined
			cout << "�޷���ȡ�������������IP..." << endl;
	}
	else
	{
		undefined
			//��ȡ�����������
			//cout<<"�����������Ϊ:"<<p->h_name<<endl;

			//����IP:����ѭ��,�����������IP
			for (int i = 0; p->h_addr_list[i] != 0; i++)
			{
				undefined
					struct in_addr in;
				memcpy(&in, p->h_addr_list[i], sizeof(struct in_addr));
				cout << "��" << i + 1 << "��������IPΪ:" << inet_ntoa(in) << endl;
			}

	}

	WSACleanup();

	cin.get();
}