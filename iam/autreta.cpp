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
	~Polinomio() {}
	Polinomio operator+(Polinomio &pol) {
		Polinomio res(this->deg);
		for (int i = 0;i < deg;i++) {
			res.coef[i] = this->coef[i] + pol.coef[i];
		}
		return res;
	}
	Polinomio operator*(Polinomio &pol) {
		Polinomio res(2 * this->deg);
		for (int i = 0;i < deg;i++) {
			for (int j = 0;j < deg;j++) {
				res.coef[i + j] += this->coef[i] * pol.coef[j];
			}
		}
		return res;
	}
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
  p = p * p;
  for (int i = 0;i <= p.deg;i++) {
  	cout << p.coef[i] << endl;
  }
  return 0;
}