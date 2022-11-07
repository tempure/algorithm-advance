#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int A[N], B[N];

int main() {
  int n;
  cin >> n;
  double curlen = 0;
  double curt = 0;
  double sumt = 0;
  for (int i = 1; i <= n; i++) {
    cin >> A[i] >> B[i];
    sumt += 1.0 * A[i] / B[i];
  }
  // cout << sumt << endl;
  for (int i = 1; i <= n; i++) {
    // cout << curt << " *** " << curlen << endl;

    if (curt <= sumt / 2 && curt + 1.0 * A[i] / B[i] > sumt / 2) {
      printf("%.8lf\n", curlen + (sumt / 2 - curt) * 1.0 * B[i]);
      break;
    }
    else {
      curt += 1.0 * A[i] / B[i];
      curlen += A[i];
    }
  }
  return 0;
}