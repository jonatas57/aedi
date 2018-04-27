#include <iostream>

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
			coef[i] = aux[i];
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
string* getMono(string s) {
	string *t;
	int g = 0, fp = 0, fm = 0, last = 0;
	while (true) {
		fp = s.find('+', last);
		fm = s.find('-', last);
		f = f1 == -1 ? f2 : (f2 == -1 ? f1 : (f1 <= f2 ? f1 : f2);
	}
	return t;
}
polinomio stop(string s) {
	string *ss = getMono(s);
	double *aux = getNum(ss);
	int l = sizeof(aux) / sizeof(double);
	polinomio p(l - 1);
	p.ler(aux);
	return p;
}

int main() {
	string s;
	cin >> s;
	polinomio p = stop(s);
	p.print();
	p = p * 2;
	p.print();
	p = p + p;
	p.print();
	return 0;
}