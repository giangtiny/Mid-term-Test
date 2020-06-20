#include<fstream>
#include<iostream>
#include<stack>
#define MAXCOLS 10
#define MAXROWS 1000
using namespace std;



void readFile(string path, int& n, int& m, int a[][MAXCOLS])
{
	ifstream is(path);
	if (is.fail())
	{
		cout << "Cant open file!" << endl;
		return;
	}
	is >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			is >> a[i][j];
	}
}

void writeFile1(string path, int n, int m, int a[][MAXCOLS])
{
	ofstream os(path);
	if (os.fail())
	{
		cout << "Cant open file!" << endl;
		return;
	}

	os << n << " "<<m<<endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			os << a[i][j] << " ";

		os << endl;
	}
}


void writeFile2(string path, int n, int m, int a[][MAXCOLS])
{
	ofstream os(path);
	if (os.fail())
	{
		cout << "Cant open file!" << endl;
		return;
	}

	os << n <<endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			os << a[i][j] << " ";

		os << endl;
	}
}


void taoHoanVi(int& n, int pos, int* a, int &m, int b[][MAXCOLS])
{
	if (pos == n)
	{
		for (int i = 0; i < n; i++)
		{
			b[m][i] = a[i];
		}
		m++;
	}
	else
	{
		for (int i = pos ; i < n; i++)
		{
			swap(a[pos], a[i]);
			taoHoanVi(n, pos + 1, a, m, b);
			swap(a[pos], a[i]);
		}
	}

}

void hoanVi(string path, int n)
{
	int b[MAXROWS][MAXCOLS];
	int a[MAXROWS];

	int m = 0;

	for (int i = 0; i < n; i++)
		a[i] = i + 1;

	taoHoanVi(n, 0, a, m, b);
	writeFile1(path, m, n, b);
}


bool kiemtraLienke(int a[MAXROWS], int m)
{
	int check = 0;
	stack<int> s;
	for (int i = 0; i < m; i++)
	{
		if (a[i] % 2 == 0)
			s.push(a[i]);
		else
		{
			if (s.empty())
			{
				s.push(a[i]);
				check++;
			}
			else
			{
				if (s.top() % 2 == 0)
					check++;
				s.push(a[i]);
			}
		}
	}

	if (check == 1)
		return true;

	return false;
}

void dayLeLienKe(int n, int m, int& rn, int& rm, int a[][MAXCOLS], int b[][MAXCOLS])
{
	rn = 0;
	rm = m;
	for (int i = 0; i < n; i++)
	{
		if (kiemtraLienke((int*)a[i], m))
		{
			for (int k = 0; k < m; k++)
				b[rn][k] = a[i][k];
			rn++;
		}
	}
}

void Cau3(string output1,string output2, int n)
{
	int a[MAXROWS][MAXCOLS], b[MAXROWS][MAXCOLS];
	int m, rn, rm;
	hoanVi(output1, n);
	readFile(output1, n, m, a);
	dayLeLienKe(n, m, rn, rm, a, b);
	writeFile2(output2, rn, rm, b);
}

int main() {
	int n,op;
	cout << "Chon cau can lam: " << endl;
	cin >> op;
	if (op == 3)
	{
		cin >> n;
		Cau3("hoanvi.txt", "ketqua.txt", n);
	}
	else if (op == 1)
	{
		cin >> n;
		hoanVi("hoanvi.txt", n);
	}
	else
	{
		int n, m, rn, rm;
		int a[MAXROWS][MAXCOLS], b[MAXROWS][MAXCOLS];

		readFile("input.txt", n, m, a);
		dayLeLienKe(n, m, rn, rm, a, b);
		writeFile2("output.txt", rn, rm, b);
	}
}