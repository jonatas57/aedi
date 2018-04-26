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
<<<<<<< HEAD
	~Polinomio() {}
	void print() {
		for (int i = 0;i <= deg;i++) {
 		 	printf(i == 0 ? "%.0f" : "%+.0f", coef[i]);
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
=======
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
>>>>>>> d10306740cc720c5e50af1312c7cccaabdc3418f
		}
		return res;
	}
	Polinomio operator*(Polinomio &pol) {
<<<<<<< HEAD
		int p1 = this->deg, p2 = pol.deg, p3 = p1 + p2;
		Polinomio res(p3);
		for (int i = 0;i <= p1;i++) {
			for (int j = 0;j <= p2;j++) {
=======
		int p1 = this->deg, p2 = pol.deg;
		Polinomio res(p1 + p2);
		res.print();
		for (int i = 0;i < p1;i++) {
			for (int j = 0;j < p2;j++) {
>>>>>>> d10306740cc720c5e50af1312c7cccaabdc3418f
				res.coef[i + j] += this->coef[i] * pol.coef[j];
			}
		}
		res.print();
		return res;
	}
<<<<<<< HEAD
  Polinomio operator*(double a) {
  	Polinomio b(this->deg);
  	for (int i = 0;i < this->deg;i++) {
  		b.coef[i] = this->coef[i] * a;
  	}
  	return b;
  }
=======
	~Polinomio() {}
>>>>>>> d10306740cc720c5e50af1312c7cccaabdc3418f
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

int main() {
<<<<<<< HEAD
	int n;
	cin >> n;
	
  Polinomio **sec;
  sec = new Polinomio*[n];
  for (int i = 0;i < n;i++) {
  	sec[i] = (Polinomio *)malloc(n * sizeof(Polinomio));
  	for (int j = 0;j < n;j++) {
  		string s;
  		cin >> s;
  		sec[i][j] = stoP(s);
  	}
  }
=======
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
>>>>>>> d10306740cc720c5e50af1312c7cccaabdc3418f
  return 0;
}
