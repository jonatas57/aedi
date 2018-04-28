#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

typedef vector<double> vdouble;
typedef vector<string> vstring;
typedef vector<double>::iterator dit;
typedef vector<string>::iterator sit;

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
	void ler(vdouble aux) {
		for (int i = 0;i <= grau;i++) {
			coef[i] += aux[i];
		}
	}
	void print() {
		bool p = false;
		for (int i = grau;i >= 0;i--) {
			string m = "";
			if (coef[i] != 0) {
				if ((coef[i] > 0 && i < grau) && p) {
					cout << "+";
				}
				if (coef[i] != 1 || i == 0) {
					if (coef[i] == -1) {
						m += "-";
					}
					else {
						char *aux = new char[30];
						sprintf(aux, "%.0f", coef[i]);
						m += aux;
					}
				}
				if (i >= 1) {
					m += "x";
				}
				if (i > 1) {
					m += "^";
					m += to_string(i);
				}
			}
			cout << m;
			if (m != "") p = true;
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

void check() {
	cout << "check" << endl;
}

vstring getMono(string s, int l) {
	vstring m;
	int i = 0, last = 0;
	do {
		i++;
		if (s[i] == '+' || s[i] == '-' || s[i] == '\0') {
			m.push_back(s.substr(last, i - last));
			last = i;
		}
	} while (s[i] != '\0');
	return m;
}
vdouble getNum(vstring s, int l) {
	vdouble num;
	for (sit it = s.begin();it != s.end();it++) {
		string ss = *it;
		int ls = ss.length();
		int var;
		string c, e = "0";
		var = ss.find('x', 0);
		if (var == -1) {
			c = ss;
		}
		else if (var == 0) {
			c = "1.0";
		}
		else if (var == 1 && !isdigit(ss[0])) {
			c = ss[0];
			c += "1.0";
		}
		else {
			c = ss.substr(0, var);
			if ((int)c.find('.', 0) == -1) c += ".0";
		}
		if (var == ls - 1) {
			e = "1";
		}
		else if (var != - 1) {
			e = ss.substr(var + 2);
		}
		int ie = stoi(e, nullptr, 10);
		while (ie >= (int)num.size()) {
			num.push_back(0);
		}
		*(num.begin() + ie) += stod(c, nullptr);
	}
	return num;
}
polinomio stop(string s, int l) {
	vdouble aux = getNum(getMono(s, l), l);
	int t = aux.size();
	polinomio p(t - 1);
	p.ler(aux);
	return p;
}

int main() {
	string s;
	cin >> s;
	int l = 1;
	for (int i = 1;s[i] != '\0';i++) {
		if (s[i] == '+' || s[i] == '-') {
			l++;
		}
	}
	polinomio p = stop(s, l);
	p.print();
	return 0;
}
