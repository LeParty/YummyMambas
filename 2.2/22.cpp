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

vector<int> q, p, n, Fn, e, d, m;
vector<vector<int>> c, cm;
vector<int> ed = { { 1 } }, nol = {0};
vector<vector<int>> base = { {7}, {{1},{1}}, {{1},{3}}, {{1},{7}}, {{1},{9}}, {{2},{3}}, {{2},{9}}, {{3},{1}}, {{3},{7}}, {{4},{1}}, {{4},{3}}, {{4},{7}}, {{5},{3}}, {{5},{9}}, {{6},{1}}, {{6},{7}}, {{7},{1}}, {{7},{3}}, {{7},{9}}, {{8},{3}}, {{8},{9}}, {{9},{7}}, {{1},{0},{1}}, {{1},{0},{3}}, {{1},{0},{7}}, {{1},{0},{9}}, {{1}, {1}, {3}}, {{1},{2},{7}}, {{1},{3},{1}}, {{1},{3},{7}}, {{1},{3},{9}}, {{1}, {4}, {9}}, {{1}, {5}, {1}} };

vector<int> ubrnol(vector<int>a) // убираем нули из начала числа( 00340 -> 340)
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
	return a;
}

vector<int> create(vector<int> mas) // Создание рандомного числа указанной длины
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
			if (i == (number - 1))
			{
				int hz;
				for (int j = 1; j < 2; j++)
				{
					hz = rand() % 10;
					if ((hz % 2) == 0)
					{
						j--;
					}
				}
				mas.push_back(hz);
			}
			else
			{
				int hz = rand() % 10;
				mas.push_back(hz);
			}
		}
	}
	return mas;
}

void PscreateQP()
{
	int ps1,ps2;
	ps1 = rand() % base.size();
	q = base[ps1];

	for (int i = 1; i < 2; i++)
	{
		ps2 = rand() % base.size();
		if (ps2 == ps1)
		{
			i--;
			continue;
		}
		p = base[ps2];
	}
}

void ProvVec() // сортирует первое и второе число по убыванию (чтобы первое всегда было больше второго)
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

void ShowVector(vector<int> mas, bool o)// Выводит нужный вектор на экран
{
	for (int i = 0; i < mas.size(); i++)
	{
		cout << mas[i];
	}
	if (o == 1)
	cout << endl;
}

void func() //Позволяет ввести вектора q и p с клавиатуры(полезно для проверок)
{
	string number;
	cin >> number;

	for (int i = 0; i < number.length(); i++)
	{
		const char tmp = number.c_str()[i];
		q.push_back(atoi(&tmp));
	}

	ShowVector(q, 1);

	cin >> number;

	for (int i = 0; i < number.length(); i++)
	{
		const char tmp = number.c_str()[i];
		p.push_back(atoi(&tmp));
	}

	ShowVector(p, 1);
}

vector<int> Umn(vector<int> mas1, vector<int> mas2) // Умножение двух векторов
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

	res = ubrnol(res);

	return res;
}

string Mul(string d1, string d2)
{
	string rez;
	int a, b, tmp_mul, tmp_add;
	int i_t = d2.length() - 1;
	int j_t = d1.length() - 1;
	int k_t = d1.length() + d2.length();
	for (int i = 0; i < k_t; i++)
	{
		rez += "0";
	}
	k_t--;
	for (int i = i_t, k; i >= 0; i--)
	{
		k = k_t - i_t + i;
		tmp_mul = tmp_add = 0;
		for (int j = j_t; j >= 0; j--, k--)
		{
			a = (int(d1[j]) - 48)*(int(d2[i]) - 48) + tmp_mul;
			tmp_mul = a / 10;
			b = int(rez[k]) - 48 + (a % 10) + tmp_add;
			tmp_add = b / 10;
			rez[k] = char((b % 10) + 48);
		}
		if (tmp_mul)
		{
			tmp_add += tmp_mul;
		}
		if (tmp_add)
		{
			rez[k] = char(tmp_add + 48);
		}
	}
	return rez;
}

vector<int> Umn2(vector<int> a, vector<int> b)
{
	string d1_t, d2_t;

	//cout << endl;
	for (int i = 0; i < a.size(); i++)
	{
		d1_t += char(a[i] + 48);
	}
	for (int i = 0; i < b.size(); i++)
	{
		d2_t += char(b[i] + 48);
	}

	//cout << "Str: ";
	//cout << d1_t << endl;
	//cout << "Str: ";
	//cout << d2_t << endl;

	string line;

	line = Mul(d1_t, d2_t);
	//cout << line;
	//cout << endl;

	vector<int>resUm;
	for (int i = 0; i < line.length(); i++)
	{
		resUm.push_back(int(line[i]) - 48);
	}

	//cout << "Resultat = ";
	//ShowVector(resUm, 1);
	//cout << endl;
	resUm = ubrnol(resUm);
	return resUm;
}

vector<int> minusq(vector<int> a, vector<int> b) // Вычитание двух векторов
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
	return res;
}

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
			while (a >= b)
			{
				a = minusq(a, b);
			}
			a = ubrnol(a);
			if (a.size() == 0)
			{
				a.push_back(0);
			}
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
				while (b_copy_s.size() > a.size())
				{
					a.insert(a.begin(), 0);
				}
			}
			else
			{
				b_copy = b;
				vector<int> del = {};
				vector<int> na = {};

				na.resize(b.size() + 1);

				for (int i = 0; i < (b.size() + 1); i++)
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

				b_copy = Umn2(b_copy, del);

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
	if (a.size() == 0)
	{
		a.push_back(0);
	}
	return a;
}

vector<int> delenieOst(vector<int> a, vector<int> b)
{
	if (a.size() > b.size())
	{
		a = vich(a, b);
	}
	else
	{
		if (a.size() == b.size())
		{
			if (a > b)
			{
				a = vich(a, b);
			}
		}
	}

	return a;
}

vector<int> Prostoe(vector<int> a, vector<int> b)//Алгоритм Евклида (ищет общий делитель у двух чисел)
{
	a = vich(a, b);
	a = ubrnol(a);
	if (a.size() == 0)
	{
		return b;
	}
	else
	{
		return Prostoe(b, a);
	}
}

vector<int> F_n(vector<int> a, vector<int> b)// Функция Эйлера Fn = (q - 1) * (p - 1);
{
	a = minusq(a, ed);
	b = minusq(b, ed);
	vector<int> res = Umn2(a, b);
	return res;
}

vector<int> ecreate(vector<int> a)//Создание случайной e (Экспаненты) взаимнопростой с Fn
{
	vector<int> res;
	bool k = 0;
	for (int i = 1; i < 2; i++)
	{
		if (k == 1)
		{
			int hz_t = rand() % Fn.size() + 1;
			int hz;
			for (int j = 0; j < hz_t; j++)
			{
				if (j == 0 && hz_t == 1)
				{
					hz = rand() % 8 + 2;
					res.push_back(hz);
				}
				else
				{
					if (j == 0)
					{
						hz = rand() % 9 + 1;
						res.push_back(hz);
					}
					else
					{
						hz = rand() % 10;
						res.push_back(hz);
					}
				}
			}
		}

		if (k == 0)
		{
			res = { {3} };

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
				k = 1;
				i--;
				continue;
			}
		}
		
		while (res.size() < Fn.size())
		{
			res.insert(res.begin(), 0);
		}
		if (res >= Fn)
		{
			res = minusq(res, res);
			res = ubrnol(res);
			k = 1;
			i--;
			continue;
		}
		else
		{
			vector<int> tmp;

			tmp = Prostoe(a, res);
			tmp = minusq(tmp, ed);
			tmp = ubrnol(tmp);

			if (tmp.size() == 0)
			{
				res = ubrnol(res);
				return res;
			}
			else
			{
				res = minusq(res, res);
				res = ubrnol(res);
				k = 1;
				i--;
			}
		}
	}
}

vector<int> plusq(vector<int> a, vector<int> b)// Сложение двух векторов(чисел)
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
		res.insert(res.begin(), a);
		c_copy = c_copy / 10;
	}
	return res;
}

vector<int> delenie(vector<int> a, vector<int> b)// Деление двух векторов (13/2 = 6)
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
				b_copy = Umn2(b_copy, del);

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

vector<int> Stepen(vector<int> a, vector<int> s)// Возводит указанное число в указанную степень(степень указывается в двоичной системе)
{
	int k;
	vector<vector<int>> mas;
	mas.resize(s.size());
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
			if (i == 1)
			{
				mas[0] = Umn2(mas[0], mas[0]);
			}
			mas[0] = Umn2(mas[0], mas[i]);
			i++;
			break;
		}
		if (i == 1)
		{
			mas[0] = Umn2(mas[0], mas[0]);
		}
		//mas[0] = mas[0] * mas[i];
		mas[0] = Umn2(mas[0], mas[i]);

		mas[0] = Umn2(mas[0], mas[0]);
		//cout << ".";
	}

	return mas[0];
}

void textq() // Ввод текст с клавы и преобразование его в кодировку
{
	cout << "Vvedite text dlia shifracii: ";
	string m_t;
	cin >> m_t;
	//cout << m_t << endl;

	int tmp;
	vector<int> m_tmp;
	int l = m_t.length();
	//cout << l << endl;
	m_tmp.resize(l);

	for (int i = 0; i < l; i++)
	{
		tmp = (int)m_t[i];
		m_tmp[i] = tmp;
	}
	
	//ShowVector(m_tmp, 1);
	//cout << endl;
	m = m_tmp;
}

void shif()
{
	vector<int> tmp;
	vector<int> tmp_rev;
	
	for (int i = 0; i < m.size(); i++)
	{
		
		tmp = minusq(tmp, tmp);
		tmp = ubrnol(tmp);

		tmp_rev = tmp;


		int t = m[i];

		while (t > 0)
		{
			int t_t = t % 10;
			t = t / 10;
			tmp_rev.push_back(t_t);
		}

		for (int i = 0; i < tmp_rev.size(); i++)
		{
			tmp.push_back(tmp_rev[tmp_rev.size() - 1 - i]);
		}
		//ShowVector(tmp);

		//c[0] = tmp^e mod n;
		

		vector<int> c_tmp;

		//tmp = m;

		//c_tmp = Stepen(tmp, DVA(e));

		//cout << endl;
		//cout << "simvol: ";
		//ShowVector(tmp, 1);
		//cout << "V stepeni ";
		//ShowVector(e, 1);
		//cout << "raven: ";
		//ShowVector(c_tmp, 1);
		//cout << endl;
		
		vector<int> result = ed, ed_tmp = nol;

		while (ed_tmp.size() < e.size())
		{
			ed_tmp.insert(ed_tmp.begin(), 0);
		}
		for (ed_tmp; ed_tmp < e; ed_tmp = plusq(ed_tmp, ed))
		{
			result = Umn2(tmp, result);
			result = delenieOst(result, n);
		}

		//cout << "shifr simvola: ";
		//ShowVector(result, 1);
		//cout << endl;
		
		c[i] = result;



		//c_tmp = delenieOst(c_tmp, n);
		//cout << "shifr simvola: ";
		//ShowVector(c_tmp, 1);
		//cout << endl;
		//c[i] = c_tmp;
	}
}

vector<int> createD(vector<int> a)
{
	vector<int> res, k;
	
	k = ed;

	for(;;)
	{
		k = plusq(k, a);

		res = delenieOst(k, e);
		res = ubrnol(res);
		if (res.size() == 0)
		{
			res = delenie(k, e);
			if (res != e)
			{
				return res;
			}
		}
	}
}

void decript()
{
	vector<int> current, result = ed, ed_tmp = nol;
	cm.resize(m.size());
	for (int i = 0; i < c.size(); i++)
	{
		result = ed, ed_tmp = nol;
		current = c[i];
		//cout << "current start = ";
		//ShowVector(current, 1);
		//cout << endl;


		while (ed_tmp.size() < d.size())
		{
			ed_tmp.insert(ed_tmp.begin(), 0);
		}
		for (ed_tmp; ed_tmp < d; ed_tmp = plusq(ed_tmp, ed))
		{
			result = Umn2(current, result);

			result = delenieOst(result, n);
			//cout << ".";
		}

		cm[i] = result;
		
		//current = Stepen(c[0], DVA(d));

		//result = delenieOst(current, n);


		//cout << endl;
		//cout << "Decript = ";
		//ShowVector(result, 1);
		//cout << endl;

	}
}



int main()
{
	srand(time(0));
	
	//func(); // Ввод чисел с клавиатуры

	//create - создание чисел заданной длины
	{
		
		//q = create(q);
		//ShowVector(q, 1);
		//p = create(p);
		//ShowVector(p, 1);
		//ProvVec();
		
	}

	//show - вывод чисел q и p
	{
		
		//cout << "q = ";
		//ShowVector(q, 1);

		//cout << "p = ";
		//ShowVector(p, 1);
	
	}

	//Umn2 Умножение быстрее
	{
		
		//vector<int> resUm2 = Umn2(q, p);
		//cout << "Resultat: ";
		//ShowVector(resUm2, 1);
		//cout << endl;
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
		
		//vector<int>resVi = delenieOst(q, p);
		//ShowVector(resVi);
		
	}

	//Умножение
	{
	
	//vector<int>resUm = Umn(q, p);
	//ShowVector(resUm, 1);

	}

	//Сложение
	/*
	vector<int> sum = plusq(q, p);
	ShowVector(sum);
	*/

	//Деление
	/*
	{
	
	vector<int> delen = delenie(q, p);
	ShowVector(delen);

	}
	*/

	//Перевод числа в двоичный код
	{
		/*
		e = { 4 };
		vector<int> e_dv = DVA(e);
		ShowVector(e_dv);
		*/
	}

	//Довольно быстрое возведение в степень )) 
	{
		/*
		m = create(m);
		//m = { {6}, {5} };
		
		ShowVector(m, 1);
		//func();
		//ShowVector(q);
		cout << endl;

		e = { {9}, {0}, {0}, {0} }; // изначальная степень(в десятиричной системе)
		ShowVector(e, 1);
		cout << endl;

		vector<int> e_dv = DVA(e); // Та же степень, но уже в двоичной системе
		ShowVector(e_dv, 1);

		cout << endl;
		vector<int> shif = Stepen(m, e_dv);//возводим число в нужную степень

		ShowVector(shif, 1);
		cout << endl;
		*/
	}

	//Провека на простоту
	{
	


	}

	//Ввод текста//тесты с шифрацией
	{
	//	textq();

		//cout << endl;

	//	ShowVector(m);
	}

	//Шифрация
	{
		//c.resize(1);
		//shif();



		//c[0] = m[0];
	}

	//RSA алг.
	
	
	{
		//Генерация ключей
		{

			//create - создание чисел заданной длины
			{
				//q = create(q);
				//ShowVector(q);
				//p = create(p);
				//ShowVector(p);
				//ProvVec();
				PscreateQP();
				ProvVec();

				//q = { { 8 },{ 6 },{ 3 } };
				//p = { {6},{3}, {1}};
				//q = { {1}, {8}, {1} };
				//p = { {1}, {7}, {9} };
			}
			//show - вывод чисел q и p
			{
				cout << "q = ";
				ShowVector(q, 1);
				cout << endl;
	
				cout << "p = ";
				ShowVector(p, 1);
				cout << endl;
			}
			//Вычисляем n - модуль.
			{
				n = Umn(q, p);
				cout << "n = ";
				ShowVector(n, 1);
				cout << endl;
			}
			//Вычисляем F(n) = (q - 1)(p - 1);
			{
				Fn = F_n(q, p);
				cout << "Fn = ";
				ShowVector(Fn, 1);
				cout << endl;
			}
			//Подбираем e (1 < e < Fn), взаимнопростую с Fn; 
			{
				e = ecreate(Fn);
				//e = { 3 };
				cout << "e = ";
				ShowVector(e, 1);
				cout << endl;
			}
			//Вычисляем d
			{
				d = createD(Fn);
				//d = { {6}, {1}, {1},{1},{5}, {7}, {9} };
				cout << "d = ";
				ShowVector(d, 1);
			}
			//Отдельно сохраняем и выводим открытый и закрытый ключи
			{
				vector<vector<int>> S;
				S.resize(3);
				S[0] = e;
				S[1] = n;
				S[2] = d;

				cout << endl;
				cout << "Open key = { ";
				ShowVector(S[0], 0);
				cout << " ; ";
				ShowVector(S[1], 0);
				cout << " }" << endl << endl;
				
				cout << "Sicret key = { ";
				ShowVector(S[2], 0);
				cout << " ; ";
				ShowVector(S[1], 0);
				cout << " }" << endl << endl;
				// S = {e, n}
				// секр. ключ = {d, n}
			}
		}
		//Шифрация
		{
		//Водим текст
			{
				textq();

				cout << endl;

				cout << "Text: ";
				ShowVector(m, 1);
			}
		//Шифруем каждый символ
			{
				//c = m^e mod n
				//m = { { 1 },{ 1 },{ 1 },{ 1 },{ 1 },{ 1 } };
				c.resize(m.size());
				shif();
			}
		//Показываем шифр
			{
				//cout << c; ("c" вывести в эдитбоксину)
				cout << "Cript = ";
				for (int i = 0; i < c.size(); i++)
				{
					ShowVector(c[i], 0);
					cout << " ";
				}
				cout << endl;
			}
		}
		//Расшифровка
		{
			//Вычисляем исходное сообщение
			{
				cout << endl;
				decript();
			}
			//Выводим его
			{
				cout << "Decript = ";
				for (int i = 0; i < cm.size(); i++)
				{
					ShowVector(cm[i], 0);
					cout << " ";
				}
				cout << endl;

				cout << "Decript = ";
				string cs;
				int C = 0;
				for (int i = 0; i < cm.size(); i++)
				{
					C = 0;
					for (int j = 0; j < cm[i].size(); j++)
					{
						C = C * 10 + cm[i][j];
					}

					cs += (char)C;
				}
				cout << cs;
				cout << endl;
			}
		}
	}
	return 0;
}

