#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < n; i++)
using namespace std;
using Graph = vector<vector<int>>;
using ll = long long;
using P = pair<int, int>;
//https://atcoder.jp/contests/abc174/submissions/18413793
//二分答案

const int INF = 10001000;

ll k;

bool f(int x, vector<int> &a) {
  ll sum = 0;
  for (int t : a) {
    sum += (t - 1) / x; //注意这里的技巧 长为t=7，6， x=3 举例试试
  }
  return sum <= k;
}

int main() {
  ll n;
  cin >> n >> k;
  vector<int> a(n);
  rep(i, n) cin >> a[i];

  // int x;
  // cin >> x;
  // if (f(x, a)) {cout << "Yes" << endl;}
  // else cout << "No" << endl;

  ll right, left;
  right = 1000000000;
  left = 0;

  while (right - left > 1) {
    ll mid = (left + right) / 2;
    if (f(mid, a)) {
      right = mid;
    }
    else {
      left = mid;
    }
  }

  cout << right << endl;

  return 0;
}