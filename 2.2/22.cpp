//22

#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <time.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

vector<int> q, p;

vector<int> create(vector<int> mas)
{
	cout << "Vvedite dlinu chisla " << endl;
	int number;
	cin >> number;

	for (int i = 0; i < number; i++)
	{
		if (i == 0)
		{
			int hz = rand() % 9 + 1;
			mas.push_back(hz);
		}
		else
		{
			int hz = rand() % 10;
			mas.push_back(hz);
		}
	}
	return mas;
}

void ShowVector(vector<int> mas)
{
	for (int i = 0; i < mas.size(); i++)
	{
		cout << mas[i];
	}
	cout << endl;
}

void func()
{
	string number;


	cin >> number;

	for (int i = 0; i < number.length(); i++)
	{
		const char tmp = number.c_str()[i];
		q.push_back(atoi(&tmp));
	}

	ShowVector(q);

	cin >> number;

	for (int i = 0; i < number.length(); i++)
	{
		const char tmp = number.c_str()[i];
		p.push_back(atoi(&tmp));
	}

	ShowVector(p);
}

vector<int> Umn(vector<int> mas1, vector<int> mas2)
{
	vector<int> res;
	vector<vector<int>> mul;

	for (int i = mas1.size() - 1; i >= 0; i--)
	{
		vector<int> tmp;

		for (int j = mas2.size() - 1; j >= 0; j--)
		{
			int tmpcalc = mas1[i] * mas2[j];
			tmp.push_back(tmpcalc);
		}
		tmp.insert(tmp.begin(), mas1.size() - i - 1, 0);
		mul.push_back(tmp);
	}

	int maxsize = 0;
	for (int i = 1; i < mul.size(); i++)
	{
		if (mul[i].size() > maxsize)
			maxsize = mul[i].size();
	}

	mul[0].resize(maxsize);

	for (int i = 1; i < mul.size(); i++)
	{
		for (int j = 0; j < mul[i].size(); j++)
		{
			mul[0][j] += mul[i][j];
		}
	}

	int c = 0;

	for (int i = 0; i < mul[0].size(); i++)
	{
		int tmp = mul[0][i];
		mul[0][i] = (tmp + c) % 10;
		c = (tmp + c) / 10;
	}
	//mul[0][mul[0].size() - 1] += c;

	int c_copy = c;

	while (c_copy > 1)
	{
		int a = c_copy % 10;
		mul[0].push_back(a);
		c_copy = c_copy / 10;
	}

	for (int i = 0; i < mul[0].size(); i++)
	{
		res.push_back(mul[0][mul[0].size() - 1 - i]);
	}

	return res;
	//return mul[0];
}

vector<int> vich(vector<int> mas1, vector<int> mas2)
{
	/*
	int h = mas1.size() - mas2.size();
	if (h >= 3)
	{
	vector<int> mas2tmp = mas2;
	for (int i = 0; i < h - 1; i++)
	{
	mas2tmp.push_back(0);
	//mas2 = mas2 * 10;
	}
	mas1 = vich(mas1, mas2tmp);
	//return vich(mas1, mas2);
	}
	*/
	if (mas1.size() < mas2.size())
	{
		mas1.insert(mas1.begin(), mas2.size() - mas1.size(), 0);
		return vich(mas2, mas1);
	}
	if (mas2.size() < mas1.size())
	{
		mas2.insert(mas2.begin(), mas1.size() - mas2.size(), 0);
		//return vich(mas2, mas1);
	}
	if (mas1.size() == mas2.size())
	{
		if (mas1[0] < mas2[0])
		{
			return vich(mas2, mas1);
		}
		else
		{
			vector<int> res;
			int c = 0;

			for (int j = mas1.size() - 1; j >= 0; j--)
			{

				if ((mas1[j] - c) >= mas2[j])
				{
					int a = mas1[j] - c - mas2[j];
					res.push_back(a);
					c = 0;
				}
				if ((mas1[j] - c) < mas2[j])
				{
					int a = mas1[j] + 10 - c - mas2[j];
					c = 1;
					res.push_back(a);
				}
			}
			vector<int> res1;
			for (int i = 0; i < res.size(); i++)
			{
				res1.push_back(res[res.size() - 1 - i]);
			}
			return res1;
		}
	}
}

vector<int> Evklid(vector<int> mas1, vector<int> mas2)
{
	bool Ch = 0;
	for (int i = 0; i < mas2.size(); i++)
	{
		if (mas2[i] != 0)
		{
			Ch = 1;
			break;
		}
	}
	if (Ch == 0)
	{
		return mas1;
	}
	if (Ch == 1)
	{
		Ch = 0;
		//vector<int> tmp = mas1;
		while (mas1 >= mas2)
		{
			mas1 = vich(mas1, mas2);
		}
		return Evklid(mas2, mas1);
	}
}

/*
vector<int> Prostoe(vector<int> mas)
{
int G = mas.size() / 2 + 1;
int g = 0;
for (int i = 0; i < G; i++)
{

}

}
*/

int main()
{
	srand(time(0));
	//func();
	//vector<int>resUm = Umn(q, p);
	//ShowVector(resUm);

	q = create(q);
	ShowVector(q);

	p = create(p);
	ShowVector(p);

	//vector<int>resUm = Umn(q, p);
	//ShowVector(resUm);

	//vector<int>resVi = vich(q, p);
	//ShowVector(resVi);

	vector<int>resEv = Evklid(q, p);
	cout << "obshii delitel = ";
	ShowVector(resEv);





	return 0;
}

