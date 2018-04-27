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
int getMono(string s, string **ss) {

}
polinomio stop(string s) {
	string ss = getMono(s);
	double *aux = getNum(ss);
	int l = sizeof(s) / sizeof(double);
	polinomio p(l - 1);
	p.ler(aux);
	return p;
}

int main() {
	string s, t, *ss;
	cin >> s;
	ss = new string[getMono(s)];
	/*polinomio p = stop(s);
	p.print();
	p = p * 2;
	p.print();
	p = p + p;
	p.print();*/
	return 0;
}
