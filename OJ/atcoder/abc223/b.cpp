#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;
  int len = s.size();
  string MIN = s;
  string MAX = s;
  for (int i = 0; i < len; i++) {
    string t = "";
    for (int j = i; j < len; j++)
      t += s[j];
    for (int k = 0; k < i; k++)
      t += s[k];
    if (t < MIN) MIN = t;
    if (t > MAX) MAX = t;
  }
  cout << MIN << endl;
  cout << MAX << endl;
  return 0;
}