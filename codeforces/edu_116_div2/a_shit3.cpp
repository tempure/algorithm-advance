#include <bits/stdc++.h>
using namespace std;

int main() {
  int t = 1;
  cin >> t;
  while (t --) {
    string s;
    cin >> s;
    int n = s.size();
    if (s == "bab") {
      cout << "bbb" << endl;
      continue;
    }
    else if (s == "aba") {
      cout << "aaa" << endl;
      continue;
    }
    if (s[0] == 'a' &&  s[1] ==  'b') {
      s[n - 1] = 'a';
    }
    else if (s[0] == 'b' && s[1] == 'a') {
      s[n - 1] = 'b';
    }
    else if (s[0] == 'a' && s[1] == 'a') {
      if (s[n - 2] == 'a' && s[n - 1] == 'b') {
        s[n - 1] = 'a';
      }
      else if (s[n - 2] == 'b' && s[n - 1] == 'a') {
        s[n - 2] = 'a';
      }
    }
    else if (s[0] == 'b' && s[1] == 'b') {
      if (s[n - 2] == 'a' && s[n - 1] == 'b') {
        s[n - 2] = 'b';
      }
      else if (s[n - 2] == 'b' && s[n - 1] == 'a') {
        s[n - 1] = 'b';
      }
    }
    cout << s << endl;
  }
  return 0;
}
