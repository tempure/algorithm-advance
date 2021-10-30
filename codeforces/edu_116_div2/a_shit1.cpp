#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t --) {
    string s;
    cin >> s;
    if (s.size() <= 3) {
      if (s.size() == 1) {
        cout << s << endl;
        continue;
      }
      else if (s.size() == 2) {
        if (s == "aa") {
          cout << "ab" << endl;
        }
        else if (s == "bb") {
          cout << "ab" << endl;
        }
        else {
          cout << s << endl;
        }
      }
    }
    else {
      for (int i = 0; i < s.size() - 2; i++) {
        if (s[i] == 'a' && s[i + 1] == 'b') {
          s[i + 2] = 'a';
        }
      }
      cout << s << endl;
    }
  }
  return 0;
}