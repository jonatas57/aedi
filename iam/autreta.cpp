#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <cctype>

using namespace std;

double* multVec(double *a, double *b, int n) {
  double *c = new double[n];
  for (int i = 0;i < n;i++) {
    if (a[i] != 0) {
      for (int j = 0;j < n;j++) {
        c[i + j] += a[i] * b[j];
      }
    }
  }
  return c;
}
double* poli(string s) {
  double* p = (double *)calloc(6, sizeof(double));
  string coef = "", ex = "", var = "";
  bool c = true, e = false;
  for (int i = 0;;i++) {
    if (isalpha(s[i])) {
      var = s[i];
      c = false;
      e = true;
    }
    else if (isdigit(s[i]) || s[i] == '.') {
      if (c) {
        coef += s[i];
      }
      else {
        ex += s[i];
      }
    }
    else {
      if (coef == "-") coef += '1';
      coef += coef == "" ? "1.0" : ".0";
      if (ex == "") ex = e ? "1" : "0";
      int iex = stoi(ex, nullptr, 10);
      double dcoef = stod(coef, nullptr);
      cout << "|" << ex << ' ' << coef << endl;
      printf(">%d, %.2f\n", iex, dcoef);
      p[iex] = dcoef;
      coef = "";
      ex = "";
      c = true;
      e = false;
      if (s[i] == '\0') return p;
    }
  }
}
double* det(double ***M, int n) {
  if (n == 1) return M[0][0];
  return NULL;
}


int main() {
  // int n;
  // cin >> n;
  //
	// double ***sec = new double**[n];
  // for (int i = 0;i < n;i++) {
  //   sec[i] = new double*[n];
  //   for (int j = 0;j < n;j++) {
  //     sec[i][j] = new double[n];
  //   }
  // }
  //
  // string s = "";
  // for (int i = 0;i < n;i++) {
  //   for (int j = 0;j < n;j++) {
  //     cin >> s;
  //     sec[i][j] = poli(s);
  //   }
  // }
  double *p;
  string s;
  cin>>s;
  p = poli(s);
  for (int i = 0;i<6;i++) {
    cout << p[i] << endl;
  }

	return 0;
}
