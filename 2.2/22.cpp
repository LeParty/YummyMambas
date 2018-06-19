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

vector<int> q, p, n, Fn, e, m;
vector<int> ed = { { 1 } }, nol = {0};

vector<int> ubrnol(vector<int>a)
{
	int noli = 0;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] == 0)
		{
			noli++;
		}
		if (a[i] != 0)
		{
			break;
		}
	}

	a.erase(a.begin(), a.begin() + noli);
	/*
	if (a.size() == 0)
	{
		a.push_back(0);
	}
	*/
	return a;
}

typedef std::string  T_num_s;
///
void  del_leading_zero(T_num_s&  a)
{
	while (a.size() > 1
		&& a[0] == '0')
	{
		a.erase(0, 1);
	}
}
///
bool less_for_big_int(T_num_s  a, T_num_s  b)
{
	del_leading_zero(a);
	del_leading_zero(b);

	return  a.size() == b.size() ? a < b : a.size() < b.size();
}
///
void  reduce_big_int(T_num_s&  minuend, const T_num_s&  subtrahend)
{
	for (T_num_s::size_type cur_pos = 0; cur_pos < subtrahend.size(); ++cur_pos)
	{
		T_num_s::size_type  minuend_cur_pos = minuend.size() - 1 - cur_pos;
		T_num_s::size_type  subtrahend_cur_pos = subtrahend.size() - 1 - cur_pos;

		char&        cur_minuend_dig_ref = minuend[minuend_cur_pos];
		const char&  cur_subtrahend_dig_ref = subtrahend[subtrahend_cur_pos];

		if (cur_minuend_dig_ref >= cur_subtrahend_dig_ref)
		{
			cur_minuend_dig_ref -= cur_subtrahend_dig_ref - '0';
		}
		else
		{
			(cur_minuend_dig_ref -= cur_subtrahend_dig_ref - '0') += 10;
			for (int i = 1; ; ++i)
			{
				if (minuend[minuend_cur_pos - i] == '0')
				{
					minuend[minuend_cur_pos - i] = '9';
				}
				else
				{
					--minuend[minuend_cur_pos - i];
					break;
				}
			}
		}
		del_leading_zero(minuend);
	}
	del_leading_zero(minuend);
}
///
void  inc_big_int(T_num_s&  a)
{
	for (T_num_s::size_type cur_pos = a.size() - 1;; --cur_pos)
	{
		if (a[cur_pos] < '9')
		{
			++a[cur_pos];
			return;
		}
		else
		{
			a[cur_pos] = '0';
			if (cur_pos == 0)
			{
				a.insert(0, "1");
				return;
			}
		}
	}
}
///
T_num_s  div_big_int(const T_num_s&  a, const T_num_s&  b)
{
	if (b == "0")
	{
		return  "division into zero";
	}

	T_num_s  res = "0";
	T_num_s  minuend = a;
	T_num_s  subtrahend = b;

	while (subtrahend.size() < minuend.size())
	{
		subtrahend += '0';
	}

	for (;;)
	{
		while (!less_for_big_int(minuend, subtrahend))
		{
			reduce_big_int(minuend, subtrahend);
			inc_big_int(res);
		}
		if (subtrahend.size() <= b.size())
		{
			break;
		}

		subtrahend.erase(subtrahend.size() - 1);
		res += '0';
		del_leading_zero(res);
	}

	return  res;
}

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

void ProvVec()
{
	if (q.size() > p.size())
	{
		return;
	}
	if (q.size() < p.size())
	{
		vector<int> q_v = q;
		q = p;
		p = q_v;
		return;
	}
	if (q.size() == p.size())
	{
		if (q < p)
		{
			vector<int> q_v = q;
			q = p;
			p = q_v;
		}
		return;
	}
	return;
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

	if (mas1.size() == 1 && mas2.size() == 1)
	{
		int g = mas1[0] * mas2[0];
		if ((g / 10) > 0)
		{
			int n = g;
			g = g / 10;
			res.push_back(g);
			g = n;
			g = g % 10;
			res.push_back(g);
		}
		else
		res.push_back(g);
	}
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

	int c_copy = c;

	while (c_copy >= 1)
	{
		int a = c_copy % 10;
		mul[0].push_back(a);
		c_copy = c_copy / 10;
	}

	for (int i = 0; i < mul[0].size(); i++)
	{
		res.push_back(mul[0][mul[0].size() - 1 - i]);
	}

	int noli = 0;
	for (int i = 0; i < res.size(); i++)
	{
		if (res[i] == 0)
		{
			noli++;
		}
		if (res[i] != 0)
		{
			break;
		}
	}

	res.erase(res.begin(), res.begin() + noli);


	return res;
}



vector<int> minusq(vector<int> a, vector<int> b)
{
	vector<int> res;
	res.resize(a.size());
	if (a.size() > b.size())
	{
		while (a.size() > b.size())
		{
			b.insert(b.begin(), 0);
		}
	}
	int c = 0;
	for (int i = a.size() - 1; i >= 0; i--)
	{
		if (a[i] >= (b[i] + c))
		{
			res[i] = a[i] - b[i] - c;
			c = 0;
		}
		else
		{
			if (a[i] < (b[i] + c))
			{
				res[i] = (a[i] + 10) - (b[i] + c);
				c = 1;
			}
		}
	}

	//res = ubrnol(res);

	return res;
}



bool GG = 0, Gg = 0;

vector<int> vich(vector<int> a, vector<int> b) // Деление с остатком (выдаёт остаток от деления)
{
	vector<int> b_copy_s = b;

	while (b_copy_s.size() < a.size())
	{
		b_copy_s.insert(b_copy_s.begin(), 0);
	}

	while (a >= b_copy_s)
	{
		a = ubrnol(a);

		if (a.size() == b.size())
		{
			while (a > b)
			{
				a = minusq(a, b);
			}
			if (a == b)
			{
				a = minusq(a, b);
			}
			a = ubrnol(a);
			return a;
		}
		else
		{
			vector<int> b_copy = b;

			while (b_copy.size() < a.size())
			{
				b_copy.push_back(0);
			}

			if (a > b_copy)
			{
				a = minusq(a, b_copy);
			}
			else
			{
				b_copy = b;
				int uravn = a.size() - b.size();

				vector<int> del = {};
				vector<int> na = {};

				na.resize(b.size() + 1);

				for (int i = 0; i < b.size() + 1; i++)
				{
					na[i] = a[i];
				}

				b_copy.insert(b_copy.begin(), 0);

				int dil = 0;

				while (na > b_copy)
				{
					na = minusq(na, b_copy);
					dil++;
				}

				del.push_back(dil);

				if (b_copy.size() > del.size())
				{
					del.insert(del.begin(), 0);
				}

				b_copy = Umn(b_copy, del);

				while (b_copy.size() < a.size())
				{
					b_copy.push_back(0);
				}

				if (b_copy > a)
				{
					b_copy.erase(b_copy.begin() + b_copy.size() - 1, b_copy.begin() + b_copy.size());
				}

				a = minusq(a, b_copy);

				while (b_copy_s.size() > a.size())
				{
					a.insert(a.begin(), 0);
				}
			}
		}
	}
	a = ubrnol(a);
	return a;
}


vector<int> Prostoe(vector<int> a, vector<int> b)
{
	a = vich(a, b);
	if (a.size() == 0)
	{
		return b;
	}
	else
	{
		return Prostoe(b, a);
	}
}

vector<int> F_n(vector<int> a, vector<int> b)
{
	a = minusq(a, ed);
	b = minusq(b, ed);
	vector<int> res = Umn(a, b);
	return res;
}

vector<int> ecreate(vector<int> a)
{
	vector<int> res;

	for (int i = 1; i < 2; i++)
	{
		int hz = rand() % 8 + 2;
		res.push_back(hz);

		//ShowVector(res);
		vector<int> tmp;

		tmp = Prostoe(a, res);
		tmp = minusq(tmp, ed);
		tmp = ubrnol(tmp);

		if (tmp.size() == 0)
		{
			return res;
		}
		else
		{
			res = minusq(res, res);
			res = ubrnol(res);

			//int b; // пауза для проверки
			//cin >> b;
			i--;
		}
	}
}

vector<int> plusq(vector<int> a, vector<int> b)
{
	vector<int> res;
	res.resize(a.size());
	int min_dl = a.size();
	if (a.size() < b.size())
	{
		min_dl = a.size();
		res.resize(b.size());
		res = b;
	}
	if (a.size() > b.size())
	{
		min_dl = b.size();
		res.resize(a.size());
		res = a;
	}

	for (int i = 0; i < min_dl; i++)
	{
		res[res.size() - 1 - i] = a[a.size() - 1 - i] + b[b.size() - 1 - i];
	}

	int c = 0;

	for (int i = 0; i < res.size(); i++)
	{
		int tmp = res[res.size()- 1 - i];
		res[res.size() - 1 - i] = (tmp + c) % 10;
		c = (tmp + c) / 10;
	}

	int c_copy = c;

	while (c_copy >= 1)
	{
		int a = c_copy % 10;
		//res.push_back(a);
		res.insert(res.begin(), a);
		c_copy = c_copy / 10;
	}
	return res;
}

vector<int> delenie(vector<int> a, vector<int> b)
{
	vector<int> b_copy_s = b, res = {1};
	vector<vector<int>> resultat;

	while (b_copy_s.size() < a.size())
	{
		b_copy_s.insert(b_copy_s.begin(), 0);
	}
	int o = 0;
	if (a < b_copy_s)
	{
		return nol;
	}
	while (a >= b_copy_s)
	{
		a = ubrnol(a);
		res = minusq(res, res);
		res = ubrnol(res);
		if (a.size() == b.size())
		{
			int ch = 0;
			while (a >= b)
			{
				a = minusq(a, b);
				ch++;
			}
			res.push_back(ch);
			if (resultat.size() < (o + 1))
			{
				resultat.resize(o + 1);
			}
			resultat[o] = res;
			while (b_copy_s.size() > a.size())
			{
				a.insert(a.begin(), 0);
			}
			//a = ubrnol(a);
			//return a;
		}
		else
		{
			vector<int> b_copy = b;
			int ch_2 = 0;
			while (b_copy.size() < a.size())
			{
				b_copy.push_back(0);
				ch_2++;
			}

			if (a >= b_copy)
			{
				int ch = 0;
				while(a >= b_copy)
				{ 
				a = minusq(a, b_copy);
				ch++;
				}
				res.push_back(ch);
				if (resultat.size() < (o + 1))
				{
					resultat.resize(o + 1);
				}
				resultat[o] = res;
				for (int i = 0; i < ch_2; i++)
				{
					resultat[o].push_back(0);
				}
			}
			else
			{
				b_copy = b;
				
				vector<int> del = {};
				vector<int> na = {};

				na.resize(b.size() + 1);

				for (int i = 0; i < b.size() + 1; i++)
				{
					na[i] = a[i];
				}

				b_copy.insert(b_copy.begin(), 0);

				int dil = 0;

				while (na >= b_copy)
				{
					na = minusq(na, b_copy);
					dil++;
				}
				if (dil < 10)
				{
					del.push_back(dil);

					res.push_back(dil);
				}
				if (dil == 10)
				{
					del.push_back(1);
					del.push_back(0);
					res.push_back(1);
					res.push_back(0);
				}

				dil = 0;
				b_copy = Umn(b_copy, del);

				while (b_copy.size() < a.size())
				{
					b_copy.push_back(0);
					dil++;
				}

				if (b_copy > a)
				{
					b_copy.erase(b_copy.begin() + b_copy.size() - 1, b_copy.begin() + b_copy.size());
					dil--;
				}

				for (int i = 0; i < dil; i++)
				{
					res.push_back(0);
				}

				a = minusq(a, b_copy);

				while (b_copy_s.size() > a.size())
				{
					a.insert(a.begin(), 0);
				}
				if (resultat.size() < (o + 1))
				{
					resultat.resize(o + 1);
				}
				resultat[o] = res;
			}

		}
		o++;
	}
	//a = ubrnol(a);
	for (int i = 1; i < resultat.size(); i++)
	{
		resultat[0] = plusq(resultat[0], resultat[i]);
	}
	return resultat[0];
}

vector<int>DVA(vector<int> q1) // переводит число в двоичную систему
{
	//func();
	vector<int> q_dva;

	vector<int> d, dv = { { 2 } };
	int d2;

	for (;;)
	{
		d = vich(q1, dv);
		d = ubrnol(d);

		if (d.size() == 0)
		{
			d.push_back(0);
			q_dva.push_back(0);
		}
		else
		{
			q_dva.push_back(1);
		}

		q1 = delenie(q1, dv);
		q1 = ubrnol(q1);
		if (q1.size() == 0)
		{
			break;
		}
	}

	vector<int> res;
	res.resize(q_dva.size());
	for (int i = 0; i < q_dva.size(); i++)
	{
		res[i] = q_dva[q_dva.size() - 1 - i];
	}
	return res;
}

vector<int> Stepen(vector<int> a, vector<int> s)
{
	int k;
	vector<vector<int>> mas;
	mas.resize(s.size());
	//vector<int> ed = { 1 };
	for (int i = 0; i < s.size(); i++)
	{
		k = s[i];
		if (i == s.size() - 1)
		{
			if (k == 0)
			{
				mas[i].push_back(1);
				i++;
				break;
			}
			mas[i] = a;
			i++;
			break;
		}
		if (k == 1)
		{
			mas[i] = a;
		}
		if (k == 0)
		{
			mas[i].push_back(1);
		}
	}
	for (int i = 1; i < mas.size(); i++)
	{
		if (i == mas.size() - 1)
		{
			mas[0] = Umn(mas[0], mas[i]);
			i++;
			break;
		}
		if (i == 1)
		{
			mas[0] = Umn(mas[0], mas[0]);
		}
		//mas[0] = mas[0] * mas[i];
		mas[0] = Umn(mas[0], mas[i]);

		mas[0] = Umn(mas[0], mas[0]);
	}

	return mas[0];
}




int main()
{
	srand(time(0));
	//func(); // Ввод чисел с клавиатуры

	//create - создание чисел заданной длины
	{
		/*
		q = create(q);
		//ShowVector(q);
		p = create(p);
		//ShowVector(p);
		ProvVec();
		*/
	}

	//show - вывод чисел q и p
	{
		/*
	cout << "q = ";
	ShowVector(q);

	cout << "p = ";
	ShowVector(p);
	*/
	}

	//Евклид, поиск общего делителя
	{
	/*
	vector<int>resEvklid = Prostoe(q, p);
	cout << "Obshii delitel' = ";
	ShowVector(resEvklid);
	*/
	}

	//Вычитание
	{
	//vector<int>resUm = minusq(q, p);
	//resUm = ubrnol(resUm);
	//ShowVector(resUm);
	}

	//Деление с остатком
	{
		//vector<int>resVi = vich(q, p);
		//ShowVector(resVi);
	}

	//Деление без остатка(Илья\нужно подогнать под вектора)
	/*
	for (;;)
	{
		std::cout << "a = ";
		T_num_s  a;
		std::cin >> a;
		del_leading_zero(a);

		std::cout << "b = ";
		T_num_s  b;
		std::cin >> b;
		del_leading_zero(b);

		std::cout << "a / b = "
			<< div_big_int(a, b)
			<< std::endl
			<< std::endl
			<< std::endl;
	}

	*/

	//Умножение
	{
	/*
	vector<int>resUm = Umn(q, p);
	ShowVector(resUm);
	*/
	}

	//Сложение
	/*
	vector<int> sum = plusq(q, p);
	ShowVector(sum);
	*/

	//Деление
	
	{
	/*
	vector<int> delen = delenie(q, p);
	ShowVector(delen);
	*/
	}
	

	//Перепод числа в двоичный код
	{
		/*
		e = { 104 };
		vector<int> e_dv = DVA(e);
		ShowVector(e_dv);
		*/
	}

	//Довольно быстрое возведение в степень )) 
	{
		
		//m = create(m);
		m = { {6}, {7} };
		ShowVector(m);
		//func();
		//ShowVector(q);
		cout << endl;

		e = { {1},{3},{0},{1} }; // изначальная степень(в десятиричной системе)
		ShowVector(e);
		cout << endl;

		vector<int> e_dv = DVA(e); // Та же степень, но уже в двоичной системе
		ShowVector(e_dv);
		cout << endl;
		vector<int> shif = Stepen(m, e_dv);//возводим число в нужную степень

		ShowVector(shif);
		cout << endl;
		
	}



	//RSA алг.
	/*
	{
		//create - создание чисел заданной длины
		{
			q = create(q);
			//ShowVector(q);
			p = create(p);
			//ShowVector(p);
			ProvVec();
			//Проверка на простоту!!!!!!!!!!!
		}
		//show - вывод чисел q и p
		{
			cout << "q = ";
			ShowVector(q);
			cout << endl;

			cout << "p = ";
			ShowVector(p);
			cout << endl;
		}
		//Вычисляем n - модуль.
		{
			n = Umn(q, p);
			cout << "n = ";
			ShowVector(n);
			cout << endl;
		}
		//Вычисляем F(n) = (q - 1)(p - 1);
		{
			Fn = F_n(q, p);
			cout << "Fn = ";
			ShowVector(Fn);
			cout << endl;
		}
		//Подбираем e (1 < e < Fn), взаимнопростую с Fn; 
		{
			e = ecreate(Fn);
			cout << "e = ";
			ShowVector(e);
			cout << endl;
		}
		


	
	}
	*/



	return 0;
}

