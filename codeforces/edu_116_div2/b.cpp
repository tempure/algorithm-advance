#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int t = 1;
  cin >> t;
  while (t --) {
    ll n, k;
    ll cur = 1, ans = 0;
    cin >> n >> k;
    while ( n > cur && k >= cur) {
      cur *= 2;
      ans += 1;
    }
    cout << ans + (n - cur + k - 1) / k << endl;
  }
  return 0;
}