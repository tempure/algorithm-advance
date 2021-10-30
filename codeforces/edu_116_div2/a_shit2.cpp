#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t --) {
    string s;
    cin >> s;
    // if (s.size() <= 3) {
    //   if (s.size() == 1) {
    //     cout << s << endl;
    //     continue;
    //   }
    //   else if (s.size() == 2) {
    //     if (s == "aa") {
    //       cout << "ab" << endl;
    //     }
    //     else if (s == "bb") {
    //       cout << "ab" << endl;
    //     }
    //     else {
    //       cout << s << endl;
    //     }
    //   }
    //   continue;
    // }
    int len = s.size();
    int cnt = 0;
    int cnt1 = 0;
    int cnt2 = 0;
    for (int i = 0; i < s.size() - 1; i++) {
      if (s[i] == 'a' && s[i + 1] == 'b') cnt1++;
      if (s[i] == 'b' && s[i + 1] == 'a') cnt2++;
    }
    // int len = s.size();
    if (s[0] == 'a' && s[1] == 'b' && cnt1 > cnt2) {
      if (s[len - 2] == 'a' && s[len - 1] == 'b') { //ab
        s[len - 1] = 'a';
      }
      else if (s[len - 2] == 'a' && s[len - 1] == 'a') { //aa
        s[len - 2] = 'b';
      }
      else if (s[len - 2] == 'b' && s[len - 1] == 'b') { //bb
        s[len - 1] = 'a';
      }
      cout << s << endl;
    }
    else if (s[0] == 'b' && s[1] == 'a' && cnt2 > cnt1) {
      if (s[len - 2] == 'b' && s[len - 1] == 'a') { //ba
        s[len - 2] = 'a';
      }
      else if (s[len - 2] == 'a' && s[len - 1] == 'a') { //aa
        s[len - 1] = 'b';
      }
      else if (s[len - 2] == 'b' && s[len - 1] == 'b') { //bb
        s[len - 2] = 'a';
      }
      cout << s << endl;
    }
    else {
      cout << s << endl;
    }
  }
}