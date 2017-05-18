/* 1009 */

#include <iostream>
#include <cmath>

using namespace std;

int main () {

  int n;

  cin >> n;

  int *a = new int[n];
  int *b = new int[n];
  int *c = new int[n];

  for (int i = 0; i < n; i++) {

    cin >> a[i];
    cin >> b[i];
  }

  for (int i = 0; i < n; i++) {

    a[i] = a[i] % 10;
    b[i] = b[i] % 4;

    if (b[i] == 0) {

      b[i] = 4;
    }

    c[i] = pow (a[i], b[i]);
    c[i] = c[i] % 10;

    if (c[i] == 0) {

      c[i] = 10;
    }

    cout << c[i] << endl;
  }

  return 0;
}