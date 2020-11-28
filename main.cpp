#include <iostream>
#include <math.h>
#include <iomanip>
#include <cmath>
using namespace std;
const double e = 0.000001;
double * g(double **a, double **y, int n) {
   int k = 0, ind;
   double m, t, t1;
    while (k < n) {
         m = a[k][k];
        if (m == 0) {
            for(int i = 0; i < n; i++) {
                if(a[i][k] != 0){
                    ind = i;
                    break;
                }
            }
            for (int i = 0; i < n; i++) {
                t = a[k][i];
                t1 = y[k][i];
                a[k][i] = a[ind][i];
                y[k][i] = y[ind][i];
                a[ind][i] = t;
                y[ind][i] = t1;
            }
            m = a[k][k];
        }
        for (int i = 0; i < n; i++) {
            a[k][i] = a[k][i] / m;
            y[k][i] = y[k][i] / m;
        }
        for (int i = k + 1; i < n; i++) {
            m = a[i][k];
            for (int j = 0; j < n; j++) {
                a[i][j] = a[i][j] - a[k][j] * m;
                y[i][j] = y[i][j] - y[k][j] * m;
            }
        }
        k++;
    }
    for (k = n - 1; k > 0; k--) {
        for(int j = k - 1; j >= 0; j--) {
            m = a[j][k];
            a[j][k] = a[j][k] - a[k][k] * m;
            for (int i = n-1; i >= 0; i--) {
                y[j][i] = y[j][i] - y[k][i] * m;
            }
        }
    }
    return *y;
}
int main() {
  setlocale(LC_ALL, "Russian");
  double **a, **y, **x;
  int n;
  cout << "¬ведите размер матрицы: ";
  cin >> n;
  a = new double*[n];
  y = new double*[n];
  x = new double*[n];
  cout << "¬ведите элементы матрицы: ";
  for (int i = 0; i < n; i++)
  {
    x[i] = new double[n];
    a[i] = new double[n];
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
      x[i][j] = a[i][j];
    }
  }
  for (int i = 0; i < n; i++)
  {
    y[i] = new double[n];
    for (int j = 0; j < n; j++) {
      if (i == j) {
        y[i][j] = 1;
      }
      else {
        y[i][j] = 0;
      }
    }
  }
  g(a, y, n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << fixed << setprecision(2) << y[i][j] << " ";
    }
    cout << endl;
  }
  for (int i = 0; i < 5; i++) cout << endl;
  double **c= new double *[n];
  for (int i = 0; i < n; i++) {
        c[i] = new double[n];
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                c[i][j] += x[i][k] * y[k][j];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (c[i][j] < e) c[i][j]=0;
            cout << fixed << setprecision(2) << c[i][j] << " ";
        }
        cout << endl;
    }
  return 0;
}
