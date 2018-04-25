#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <cctype>

using namespace std;

void check() {
	cout << "check" << endl;
}

double* multVec(double *a, double *b, int n) {
  double *c = new double[n];
  for (int i = 0;i < n;i++) {
    if (a[i] != 0) {
      for (int j = 0;j < n;j++) {
        if (i + j < n) c[i + j] += a[i] * b[j];
      }
    }
  }
  return c;
}
double* multVec(double *a, double b, int n) {
  double* c = (double*)calloc(n, sizeof(double));
  for (int i = 0;i < n;i++) {
    c[i] = a[i] * b;
  }
  return c;
}
double* sumVec(double *a, double *b, int n) {
  double *c = new double[n];
  for (int i = 0;i < n;i++) {
    c[i] = a[i] + b[i];
  }
  return c;
}
double* poli(string s) {
  double* p = (double *)calloc(6, sizeof(double));
  string coef = "", ex = "", var = "";
  bool c = true, e = false, sig = true, flo = false;
  for (int i = 0;;i++) {
    if (isalpha(s[i]) || s[i] == '^') {
      var = s[i];
      c = false;
      e = true;
    }
    else if (isdigit(s[i]) || s[i] == '.') {
      if (c) {
        coef += s[i];
        flo = true;
      }
      else {
        ex += s[i];
      }
    }
    else if (s[i] == '+' || s[i] == '-' || s[i] == '\0') {
      if (i == 0) {
        sig = s[i] == '+';
      }
      else {
        if (coef == "") {
          coef += "1.0";
        }
        else if (!flo) {
          coef += ".0";
        }
        if (ex == "") ex = e ? "1" : "0";
        int iex = stoi(ex, nullptr, 10);
        double dcoef = stod(coef, nullptr);
        p[iex] += dcoef * (sig ? 1 : -1);
        coef = "";
        ex = "";
        c = true;e = false;sig = true;flo = false;
      }
      if (s[i] == '\0') return p;
    }
  }
}
double* det(double ***M, int n) {
  if (n == 1) return M[0][0];
  double* d = (double*)calloc(n, sizeof(double));
  for (int i = 0;i < n;i++) {
    double ***N = new double**[n - 1];
    for (int j = 0;j < n - 1;j++) {
      N[j] = new double*[n - 1];
      for (int k = 0;k < n - 1;k++) {
        N[j][k] = new double[n - 1];
        for (int l = 0;l < n - 1;l++) {
          N[j][k][l] = M[j + 1][k >= i ? k + 1 : k][l];
        }
      }
    }
    double *aux = det(N, n - 1);
    for (int z = 0;z < n;z++) {
      cout << "-";
    }
    cout << aux[0] << endl;
    d = sumVec(d, multVec(aux, multVec(N[0][i], (i % 2 == 0 ? -1.0 : 1.0), n), n), n);
  }
  return d;
}


int main() {
  int n;
  cin >> n;
	double ***sec = new double**[n];
  for (int i = 0;i < n;i++) {
    sec[i] = new double*[n];
    for (int j = 0;j < n;j++) {
      sec[i][j] = new double[n];
    }
  }

  string s = "";
  for (int i = 0;i < n;i++) {
    for (int j = 0;j < n;j++) {
      cin >> s;
      sec[i][j] = poli(s);
    }
  }

  double *d = det(sec, n);
  cout << d[0] << endl;
	return 0;
}
