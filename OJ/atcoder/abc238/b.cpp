#include<bits/stdc++.h>

using namespace std;

//https://atcoder.jp/contests/abc238/editorial/3364

int main() {
  int n;
  cin >> n;
  vector<bool> fl(360, false);
  fl[0] = true;
  int p = 0;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    p += a; p %= 360;
    fl[p] = true;
  }
  int res = 0, cur = 0;
  for (int i = 0; i <= 360; i++) {
    if (fl[i % 360]) {
      res = max(res, cur);
      cur = 0;
    }
    cur++;
  }
  cout << res << '\n';
}