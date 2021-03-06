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
void clean();
void print();
int T = 0;
int X1 = 24, Y1 = 12;
int Xc = 12, Yc = 24;
int X3 = 0, Y3 = 12;
int X4 = 12, Y4 = 0;
int Y = 0, X = 0;

int main()
{
	clean();
	for (;;)
	{
		for (int i = 0; i < 24; i++)
		{
			K1();
			K2();
			K3();
			K4();
			print();
			T++;
			Sleep(10);
			//int a;
			//cin >> a;
		}
		T = 0;
		X1 = 24, Y1 = 12;
		Xc = 12, Yc = 24;
		X3 = 0, Y3 = 12;
		X4 = 12, Y4 = 0;
	}

	//

	return 0;
}

void K1()
{
	Pole[Y1][X1] = ' ';
	clean();
	if (T < 12)
	{
		Y1++;
		Pole[Y1][X1] = '*';
		X = 12;
		for (int i = 0; i < 12; i++)
		{
			Y = (((X - X1)*(12 - Y1)) / (12 - X1)) + Y1;
			Pole[Y][X] = '*';
			X++;
		}
	}
	if (T > 11)
	{
		X1--;
		Pole[Y1][X1] = '*';
		Y = 12;
		for (int i = 0; i < 12; i++)
		{
			X = (((Y - Y1)*(12 - X1)) / (12 - Y1)) + X1;
			Pole[Y][X] = '*';
			Y++;
		}
	}
}

void K2()
{
	Pole[Yc][Xc] = ' ';
	if (T < 12)
	{
		Xc--;
		Pole[Yc][Xc] = '*';
		Y = 12;
		for (int i = 0; i < 12; i++)
		{
			X = (((Y - Yc)*(12 - Xc)) / (12 - Yc)) + Xc;
			Pole[Y][X] = '*';
			Y++;
		}
	}
	if (T > 11)
	{
		Yc--;
		Pole[Yc][Xc] = '*';
		X = 12;
		for (int i = 0; i < 12; i++)
		{
			Y = (((X - Xc)*(12 - Yc)) / (12 - Xc)) + Yc;
			Pole[Y][X] = '*';
			X--;
		}
	}
}

void K3()
{
	Pole[Y3][X3] = ' ';
	if (T < 12)
	{
		Y3--;
		Pole[Y3][X3] = '*';
		X = 12;
		for (int i = 0; i < 12; i++)
		{
			Y = (((X - X3)*(12 - Y3)) / (12 - X3)) + Y3;
			Pole[Y][X] = '*';
			X--;
		}
	}
	if (T > 11)
	{
		X3++;
		Pole[Y3][X3] = '*';
		Y = 12;
		for (int i = 0; i < 12; i++)
		{
			X = (((Y - Y3)*(12 - X3)) / (12 - Y3)) + X3;
			Pole[Y][X] = '*';
			Y--;
		}
	}
}

void K4()
{
	Pole[Y4][X4] = ' ';

	if (T < 12)
	{
		X4++;
		Pole[Y4][X4] = '*';
		Y = 0;
		for (int i = 0; i < 12; i++)
		{
			X = (((Y - Y4)*(12 - X4)) / (12 - Y4)) + X4;
			Pole[Y][X] = '*';
			Y++;
		}
	}
	if (T > 11)
	{
		Y4++;
		Pole[Y4][X4] = '*';
		X = 12;
		for (int i = 0; i < 12; i++)
		{
			Y = (((X - X4)*(12 - Y4)) / (12 - X4)) + Y4;
			Pole[Y][X] = '*';
			X++;
		}
	}
}


void print()
{
	system("cls");
	for (int i = 0; i < 25; i++)
	{
		for (int p = 0; p < 7; p++)
		{
			cout << Pole[q][p];
		}
		cout << endl;
	}
	cout << T;
}

void clean()
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
	

	//Pole[0][12] = '*';
	//Pole[12][12] = '*';
	//Pole[12][0] = '*';
	//Pole[24][12] = '*';
}