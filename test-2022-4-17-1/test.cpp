
//#include <stdio.h>
//#include <conio.h>
//#include <windows.h>
//
///*ddsf
//����һ�����������Ȼ��û�п������������ʲô����������Ҿ����������ʹ������̨��һЩ���ԣ�
//���˾���������ǾͿ��Զ���Щ���Խ��в���
//*/
//HANDLE hout;
//
//char get_input(void);	//��ȡ�û�����
//
//int main()
//{
//	char ch;
//
//	hout = GetStdHandle(STD_OUTPUT_HANDLE);		//��ȡ��׼����豸�ľ��
//
//	while (1)
//	{
//		ch = get_input();
//		printf("%c", ch);//��������ַ�
//	}
//}
//
////��������ÿ�������ļ�ֵ
//char get_input(void)
//{
//	int ch;			//�����ַ���
//
//	COORD coord;	//������Ļ�ϵ�����
//	CONSOLE_SCREEN_BUFFER_INFO csbi;	//����̨��Ļ��������Ϣ
//
//	coord.X = 10;	//���ù������
//	coord.Y = 10;
//
//	ch = _getch();	//�������ԣ�����Ҫ���س�����getchһ����΢��Ѻ���ͳһΪ���»��߿�ͷ��
//
//	//0X0D��ʾ�س��ļ��룬0XE0��ʾ�������Ҽ��ļ���
//	while (ch == 0XE0 || ch == 0X0D)
//	{
//		GetConsoleScreenBufferInfo(hout, &csbi);	//��ȡ��Ļ����Ĺ��λ��,Ȼ��ѵ�ǰ���λ�ø���COORD
//		coord.X = csbi.dwCursorPosition.X;			//�õ�����x��ֵ
//		coord.Y = csbi.dwCursorPosition.Y;			//yֵ
//
//		if (ch == 0X0D)//�س�
//		{
//			coord.X = 0;
//			coord.Y++;
//			SetConsoleCursorPosition(hout, coord);	//������豸�϶�λ���
//			break;
//		}
//
//		ch = _getch();	//�س�������֮����Լ������룬�����������ľ��Ƿ�����Ļ������ͻᱻ����
//
//		if (ch == 0x48)//��
//		{
//			if (coord.Y != 0)
//				coord.Y--;
//		}
//		else if (ch == 0x50)//��
//		{
//			coord.Y++;
//		}
//		else if (ch == 0x4b)//��
//		{
//			if (coord.X != 0)
//				coord.X--;
//		}
//		else if (ch == 0x4d)//��
//		{
//			if (coord.X != 79)//����д79���ֻ���
//				coord.X++;
//			else
//			{
//				coord.X = 0;
//				coord.Y++;
//			}
//		}
//
//		SetConsoleCursorPosition(hout, coord);//��λ���
//		ch = _getch();	//��������,��ֹ����while������������ֵ��Ӧ���ַ�
//	}
//	return ch;	//��ͨ�����ͷ��ؼ�ֵ�������Ӧ���ַ�
//}

//#include <iostream>
//#include <string>
//#include <Conio.h>
//#include <windows.h>
//
//int main(void)
//{
//	std::string passwd;
//	std::string s;
//	int ch;
//
//	std::cout << "����������>��";
//	while (1)
//	{
//		ch = _getch();
//
//		if (ch == '\r')
//		{
//			break;
//		}
//		system("cls");
//		passwd.push_back(ch);
//		s += '*';
//		printf("����������>��%s\r", s.c_str());
//	}
//
//	printf("\n");
//
//	std::cout << passwd << std::endl;
//
//	return 0;
//}