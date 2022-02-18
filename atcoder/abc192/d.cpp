#include <bits/stdc++.h>
using namespace std;

//https://atcoder.jp/contests/abc192/submissions/20292851


int main() {
  string X;
  cin >> X;
  long long M;
  cin >> M;
  int N = X.size();
  int d = 0;
  for (int i = 0; i < N; i++) {
    d = max(d, X[i] - '0');
  }
  if (N == 1) {
    if (d <= M) {
      cout << 1 << endl;
    } else {
      cout << 0 << endl;
    }
  } else {
    long long tv = d, fv = M + 1;
    while (fv - tv > 1) {
      long long mid = (tv + fv) / 2;
      long long sum = 0;
      bool big = false;
      for (int i = 0; i < N; i++) {
        if (sum > M / mid) {
          big = true;
          break;
        }
        sum *= mid;
        sum += X[i] - '0';
      }
      if (sum > M) {
        big = true;
      }
      if (big) {
        fv = mid;
      } else {
        tv = mid;
      }
    }
    cout << tv - d << endl;
  }
}