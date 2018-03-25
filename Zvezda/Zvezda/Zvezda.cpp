// Zvezda.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "iostream"
#include "windows.h"
using namespace std;

char Pole[25][25];
void K1();
void K2();
void K3();
void K4();
void print();
int T = 0;
int X1 = 24, Y1 = 12;
int Xc = 12, Yc = 24;
int X3 = 0, Y3 = 12;
int X4 = 12, Y4 = 0;
int chek = 0;

int main()
{
	for (int i = 0; i < 25; i++)
	{
		for (int o = 0; o < 25; o++)
		{
			Pole[i][o] = ' ';
		}
	}
	//
	Pole[12][12] = '*';
	//
	Pole[0][12] = '*';
	Pole[12][12] = '*';
	Pole[12][0] = '*';
	Pole[24][12] = '*';

	for (;;)
	{
		for (int i = 0; i < 17; i++)
		{
			K1();
			K2();
			K3();
			K4();
			print();
			T++;
			Sleep(5);
			//int a;
			//cin >> a;
		}
		T = 0;
		X1 = 24, Y1 = 12;
		Xc = 12, Yc = 24;
		X3 = 0, Y3 = 12;
		X4 = 12, Y4 = 0;
		chek = 0;
	}

	//

	return 0;
}

void K1()
{
	Pole[Y1][X1] = ' ';
	if (Y1 == 24)
	{
		X1--;
		Pole[Y1][X1] = '*';
	}
	if (Y1 > 16 && Y1 < 24)
	{
		Y1++;
		X1--;
		Pole[Y1][X1] = '*';
	}
	if (Y1 < 17)
	{
		Y1++;
		Pole[Y1][X1] = '*';
	}
}

void K2()
{
	Pole[Yc][Xc] = ' ';

	if (Yc < 18)
	{
		Yc--;
		Pole[Yc][Xc] = '*';
	}
	if (Yc > 17 && chek == 5)
	{
		Yc--;
		Xc--;
		Pole[Yc][Xc] = '*';
	}
	if (chek < 5)
	{
		Xc--;
		Pole[Yc][Xc] = '*';
		chek++;
	}
}

void K3()
{
	Pole[Y3][X3] = ' ';
	if (Y3 == 0)
	{
		X3++;
		Pole[Y3][X3] = '*';
	}
	if (Y3 < 8 && Y3 > 0)
	{
		Y3--;
		X3++;
		Pole[Y3][X3] = '*';
	}
	if (Y3 > 7)
	{
		Y3--;
		Pole[Y3][X3] = '*';
	}
}

void K4()
{
	Pole[Y4][X4] = ' ';

	if (X4 == 24)
	{
		Y4++;
		Pole[Y4][X4] = '*';
	}
	if (X4 > 16 && X4 < 24)
	{
		Y4++;
		X4++;
		Pole[Y4][X4] = '*';
	}
	if (X4 < 17)
	{
		X4++;
		Pole[Y4][X4] = '*';
	}
}


void print()
{
	system("cls");
	for (int i = 0; i < 25; i++)
	{
		for (int o = 0; o < 25; o++)
		{
			cout << Pole[i][o];
		}
		cout << endl;
	}
	cout << T;
}