#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <cctype>

using namespace std;

void check() {
	cout << "check" << endl;
}

class Polinomio {
public:
	int deg;
	double* coef;
	Polinomio(int a) {
		deg = a;
		coef = (double *)calloc(a + 1, sizeof(double));
	}
	void print() {
		for (int i = deg;i >= 0;i--) {
 		 	printf(i == deg ? "%.0f" : "%+.0f", coef[i]);
 		 	if (i >= 1) cout << "x";
 		 	if (i > 1) printf("^%d", i);
	  }
 		cout << endl;
	}
	Polinomio operator+(Polinomio &pol) {
		int p1 = this->deg, p2 = pol.deg;
		int p3 = p1 > p2 ? p1 : p2;
		Polinomio res(p3);
		for (int i = 0;i <= p3;i++) {
			int a = i <= this->deg ? this->coef[i] : 0;
			int b = i <= pol.deg ? pol.coef[i] : 0;
			res.coef[i] = a + b;
		}
		return res;
	}
	Polinomio operator*(Polinomio &pol) {
		int p1 = this->deg, p2 = pol.deg, p3 = p1 + p2;
		Polinomio res(p3);
		for (int i = 0;i < p1;i++) {
			for (int j = 0;j < p2;j++) {
				res.coef[i + j] += this->coef[i]* pol.coef[j];
			}
		}
		return res;
	}
	  Polinomio operator*(double a) {
  	Polinomio b(this->deg);
  	for (int i = 0;i < this->deg;i++) {
  		b.coef[i] = this->coef[i] * a;
  	}
  	return b;
  }
	~Polinomio() {}
};

Polinomio det(Polinomio **M, int n) {
  if (n == 1) return M[0][0];
  Polinomio res(M[0][0].deg), **aux;
  aux = new Polinomio*[n - 1];
  for (int i = 0;i < n - 1;i++) {
  	aux[i] = (Polinomio *)malloc((n - 1) * sizeof(Polinomio));
  }
  for (int k = 0;k < n;k++) {
  	for (int i = 0;i < n - 1;i++) {
  		for (int j = 0;j < n - 1;j++) {
  			aux[i][j] = M[i + 1][j >= k ? j + 1 : j];
  		}
  	}
  	Polinomio cof = det(aux, n - 1) * M[0][k];
  	cof = cof * (k % 2 == 0 ? 1.0 : -1.0);
  	res = res + cof;
  }
  return res;
}
double* getCoef(string s) {
	int l = s.length();
	int i;
	for (i = 0;i < l && !isalpha(s[i]);i++);
	double *aux = new double[2];
	if (i == 0) {
		aux[0] = 1.0;
	}
	if (i == l) {
		aux[1] = 0.0;
	}
	else if (i == l - 1) {
		aux[1] = 1.0;
	}
	else {
		aux[0] = stod(s.substr(0, i), nullptr);
		string e = s.substr(i + 2);
		aux[1] = stod(e, nullptr);
	}
	return aux;
}
Polinomio stoP(string s) {
	Polinomio p(3);
	int f1 = 0, f2 = 0, last = 0;
	while (1) {
		f1 = s.find('+', last);
		f2 = s.find('-', last);
		cout << f1<<' ' << f2<<endl;
		int f = f1 == -1 ? f2 : (f2 == -1 ? f1 : (f1 < f2 ? f1 : f2));
		cout << f << endl;
		if (f == -1) break;
		else if (f != 0) {
			cout << "viva" << endl;
			string sub = s.substr(last, last - f);
			double *aux = new double[2];
			aux = getCoef(sub);
			p.coef[(int)aux[1]] = aux[0];
			last = f;
cout << last << endl;
		}
	}
	return p;
}

int main() {
	string s;
	cin >> s;
	Polinomio p = stoP(s);
	p.print();
	return 0;
}
