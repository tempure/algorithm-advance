#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t --) {
    string s;
    cin >> s;
    int len = s.size();
    if (s[len - 1] == s[0]) cout << s << endl;
    else {
      s[len - 1] = ((s[len - 1] - 'a') ^ 1) + 'a';
      cout << s << endl;
    }
  }
  return 0;
}