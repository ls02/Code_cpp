#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>


int main(void)
{
	double t = 0;
	double p = 0;
	double q = 0;
	printf("����������ֵ:>");
	scanf("%lf%lf%lf", &t, &p, &q);

	double z = 0;
	double d = 0;
	if (p > 7)
	{
		z = 100 / (100 + 2.92 * pow((double)p,1.25));
	}
	else
	{
		//ѹ��С��5MPa���ɲ�ͼȡֵ����ͼ�õ�p=5MPaʱ��Z=0.786
		printf("������Z:>");
		scanf("%lf", &z);
	}

	d = sqrt((0.1 * t * z * q * pow(10.0, 4) / (86400 * 0.785 * 273 * p * 15) * 100));

	printf("d:%.3lf\n", d);
	printf("z:%.3lf\n", z);
	printf("���س�����");
	getchar();
	getchar();
	

	double D = 0.0;
	double o = 0.0;
	double Tc = 2.0;
	double Tch = 2.1;
	double T = 0.0;
	double d0 = 0.0;


	while (1)
	{
		system("cls");
		printf("�������׼�ܾ�D���ں�o:>");
		scanf("%lf%lf", &D, &o);

		d0 = D + (2 * o);

		T = (Tc + Tch + p * d0 / 2 / (245 * 1 + p * 0.4)) * (1 / (1 - 12.5 / 100));
		double T1 = D - (2 * o);

		if (T < o)
		{
			//U = 0.1 * T * Z * Qv * 10 ^ 4 / ��67824 * 273 * P * ����d0 - 2 * T1�� / 1000�� ^ 2��
			//double x = 67824 * 273 * p * ((d0 - 2 * T1) / 1000);
			double u = 0.1 * t * z * q * pow(10.0, 4) / pow((double)67824 * 273 * p * ((d0 - 2 * T1) / 1000), 2);

			if (u < 15)
			{
				printf("t:%.2lf\n", T);
				printf("u:%.2lf\n", u);

				break;
			}
			else
			{
				printf("u����15\n");
				Sleep(2000);
			}

		}
		else
		{
			printf("t����o\n");
			Sleep(2000);
		}
	}

	return 0;
}