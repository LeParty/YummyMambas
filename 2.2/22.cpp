//22
#include "stdafx.h" 
#include <math.h>
#include <iostream> 
#include <conio.h> 
#include <string> 
#include <windows.h> 
#include <fstream>
#include <time.h>
#include <ctime>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <sstream>
#include <conio.h>
using namespace std;

int q, p, n, Fn, e;
bool chek = 0;
int encrypt( int i, int e,  int n);
/* void file2()
{
	string c;
	ofstream file1("txt.txt");
	getline(cin, c);
	file1 << c;
	file1.close();

} */ 

void create();
void proverka(int);
void createE();
string msg;
int main()
{
	fstream file3;
	srand(time(0));
	create();
	cout << "q = " << q << " p = " << p << endl;
	n = q * p;
	cout << "n = " << n << endl;
	Fn = (q - 1)*(p - 1);
	cout << "F(n) = " << Fn << endl;
	createE();
	ofstream file1("test.txt");
    int encryptedText[100];
	getline(cin, msg);
	for ( int i = 0; i < msg.length(); i++)
	{
		encryptedText[i] = encrypt(msg[i],e, n);

	return 0;
}

void create()
{
	for (int i = 0; i < 1; i++)
	{
		q = rand() % 100;
		proverka(q);
		if (chek == 1)
		{
			i--;
			chek = 0;
		}
	}
	for (int i = 0; i < 1; i++)
	{
		p = rand() % 100;
		proverka(p);
		if (chek == 1)
		{
			i--;
			chek = 0;
		}
	}
}

void proverka(int chislo)
{
	float w1, w2;
	w1 = sqrt(chislo);
	w2 = modf(w1, &w2);
	w1 = w1 - w2;
	for (float i = 2.0; i < w1 + 1; i++)
	{
		float w3, w4;
		w3 = chislo / i;
		w4 = modf(w3, &w4);
		if (w4 == 0)
		{
			chek = 1;
			cout << "-";
			return;
		}
	}
}

void createE()
{
	float w9, w10;
	w9 = sqrt(Fn);
	w10 = modf(w9, &w10);
	w9 = w9 - w10;
	int* FnM = new int[w9 + 1];
	for (int i = 0; i < w9 + 1; i++)
	{
		FnM[i] = 0;
	}
	int o = 0;
	for (float i = 2.0; i < w9 + 1; i++)
	{
		float w11, w12;
		w11 = Fn / i;
		w12 = modf(w11, &w12);
		if (w12 == 0)
		{
			FnM[o] = i;
			FnM[o + 1] = w11;
			o = o + 2;
		}
	}
	for (int P = 0; P < 1; P++)
	{
		e = rand() % (Fn - 3) + 2;
		float w5, w6;
		w5 = sqrt(e);
		w6 = modf(w5, &w6);
		w5 = w5 - w6;
		int* EM = new int [w5+1];
		for (int I = 0; I < w5 + 1; I++)
		{
			EM[I] = 1;
		}
		o = 0;
		for (float i = 2.0; i < w5 + 1; i++)
		{
			float w7, w8;
			w7 = e / i;
			w8 = modf(w7, &w8);
			if (w8 == 0)
			{
				EM[o] = i;
				EM[o + 1] = w7;
				o = o + 2;
			}
		}
		for (int j = 0; j < w5 + 1; j++)
		{
			for (int l = 0; l < w9 + 1; l++)
			{
				if (EM[j] == FnM[l])
				{
					P--;
					j = w5 + 1;
					break;
				}
			}
		}
	}
	cout << "e = " << e << endl;
}