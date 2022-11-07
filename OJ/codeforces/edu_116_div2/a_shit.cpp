#include <bits/stdc++.h>
using namespace std;

int main() {
  int t = 1;
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
      continue;
    }
    int len = s.size();
    int cnt = 0;
    int cnt1 = 0;
    int cnt2 = 0;
    for (int i = 0; i < s.size() - 1; i++) {
      if (s[i] == 'a' && s[i + 1] == 'b') cnt1++;
      if (s[i] == 'b' && s[i + 1] == 'a') cnt2++;
    }
    if (cnt1 == 0) {
      cout << string(len, 'a') << endl;
      continue;
    }
    else if (cnt2 == 0) {
      cout << string(len, 'b') << endl;
      continue;
    }
    if (cnt1 == cnt2) {
      cout << s << endl;
      continue;
    }
    else {
      if (cnt1 > cnt2) {
        for (int i = 0; i < s.size() - 1; i++) {
          if (s[i] == 'b' && s[i +  1] == 'b') {
            cnt2++;
            s[i + 1] = 'a';
          }
          if (cnt2 == cnt1) {
            cout << s << endl;
            break;
          }
        }
        if (cnt1 > cnt2) {
          for (int i = 0; i < s.size() - 1; i++) {
            if (s[i] == 'a' && s[i +  1] == 'b') {
              cnt1--;
              s[i + 1] = 'a';
            }
            if (cnt2 == cnt1) {
              cout << s << endl;
              break;
            }
          }
        }
      }
      else if ( cnt2 > cnt1) {
        for (int i = 0; i < s.size() - 1; i++) {
          if (s[i] == 'a' && s[i +  1] == 'a') {
            cnt1++;
            s[i + 1] = 'b';
          }
          if (cnt2 == cnt1) {
            cout << s << endl;
            break;
          }
        }
        if (cnt2 > cnt1) {
          for (int i = 0; i < s.size() - 1; i++) {
            if (s[i] == 'b' && s[i +  1] == 'a') {
              cnt2--;
              s[i + 1] = 'b';
            }
            if (cnt2 == cnt1) {
              cout << s << endl;
              break;
            }
          }
        }
      }
    }
  }
}