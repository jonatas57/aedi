#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

class polinomio {
private:
	int grau;
	double *coef;
public:
	polinomio(int a) {
		grau = a;
		coef = (double*)calloc(a + 1, sizeof(double));
	}
	void ler() {
		for (int i = 0;i <= grau;i++) {
			cin >> coef[i];
		}
	}
	void ler(double *aux) {
		for (int i = 0;i <= grau;i++) {
			coef[i] += aux[i];
		}
	}
	void print() {
		for (int i = 0;i <= grau;i++) {
			printf("%.0f ", coef[i]);
		}
		cout << endl;
	}
	polinomio operator*(polinomio &pol) {
		int g1 = this->grau, g2 = pol.grau;
		polinomio res(g1 + g2);
		for (int i = 0;i <= g1;i++) {
			for (int j = 0;j <= g2;j++) {
				res.coef[i + j] += this->coef[i] * pol.coef[j];
			}
		}
		return res;
	}
	polinomio operator*(double a) {
		polinomio res(this->grau);
		for (int i = 0;i <= grau;i++) {
			res.coef[i] = this->coef[i] * a;
		}
		return res;
	}
	polinomio operator*(int a) {
		return *this * (double)a;
	}
	polinomio operator+(polinomio &pol) {
		polinomio res(this->grau);
		for (int i = 0;i <= grau;i++) {
			res.coef[i] = this->coef[i] + pol.coef[i];
		}
		return res;
	}
};
string* getMono(string s, int l) {
	string *m = new string[l];
	int i = 0, last = 0, c = 0;
	do {
		i++;
		if (s[i] == '+' || s[i] == '-' || s[i] == '\0') {
			m[c] = s.substr(last, i - last);
			c++;
			last = i;
		}
	} while (s[i] != '\0');
	return m;
}
double* getNum(string *s, int l) {
	
	double *num = NULL;
	return num;
}
polinomio stop(string s, int l) {
	string *ss = getMono(s, l);
	double *aux = getNum(ss, l);
	polinomio p(l - 1);
	p.ler(aux);
	return p;
}

int main() {
	string s, t, *ss;
	cin >> s;
	int l = 1;
	for (int i = 1;s[i] != '\0';i++) {
		if (s[i] == '+' || s[i] == '-') l++;
	}
	ss = getMono(s, l);
	for (int i = 0;i < l;i++) cout << ss[i] << endl;
	
	//polinomio p = stop(s, l);
	return 0;
}
