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
	int* coef;
	Polinomio(int a) {
		deg = a;
		coef = (int *)calloc(a + 1, sizeof(int));
	}
	void print() {
		for (int i = 0;i <= deg;i++) {
			cout << coef[i] << ' ';
		}
		cout << endl;
	}
	Polinomio operator+(Polinomio &pol) {
		Polinomio res(this->deg > pol.deg ? this->deg : pol.deg);
		for (int i = 0;i < deg;i++) {
			res.coef[i] += this->coef[i] + pol.coef[i];
		}
		return res;
	}
	Polinomio operator*(Polinomio &pol) {
		int p1 = this->deg, p2 = pol.deg;
		Polinomio res(p1 + p2);
		res.print();
		for (int i = 0;i < p1;i++) {
			for (int j = 0;j < p2;j++) {
				res.coef[i + j] += this->coef[i] * pol.coef[j];
			}
		}
		res.print();
		return res;
	}
	~Polinomio() {}
};

double* det(double ***M, int n) {
  if (n == 1) return M[0][0];
  return NULL;
}

int main() {
  int n;
  cin >> n;
  Polinomio p(n);
  for (int i = 0;i <= n;i++) {
  	cin >> p.coef[i];
  }
	printf("p = ");
	p.print();
  p = p * p;
  p.print();
  return 0;
}
