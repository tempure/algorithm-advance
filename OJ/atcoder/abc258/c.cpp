#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  string s;
  cin >> s;
  int shift = 0;
  while (q--) {
    int op, x;
    cin >> op >> x;
    if (op == 1) {
      shift = (shift + n - x) % n;
    } else {
      cout << s[(shift + x - 1) % n] << '\n';
    }
  }
  return 0;
}
