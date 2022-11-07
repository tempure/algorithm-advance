#include <bits/stdc++.h>
using namespace std;

int main() {
  int t; cin >> t;
  while (t --) {
    int n;
    cin >> n;
    bool flag = true;
    for (int i = 1; i <= n; i++) {
      int x;
      cin >> x;
      bool found = false;
      for (int j = i + 1; j >= 2; j--) {
        if (x % j) {
          found = true;
          break;
        }
      }
      flag &= found;
    }
    if (flag) puts("YES");
    else puts("NO");
  }
}