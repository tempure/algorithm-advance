#include <bits/stdc++.h>
using namespace std;

//https://atcoder.jp/contests/abc191/editorial/730

int main() {
  int h, w;
  char s[110][110];
  cin >> h >> w;
  for (int i = 0; i < h; i++) cin >> s[i];
  int ans = 0;
  for (int i = 0; i < h - 1; i++)
    for (int j = 0; j < w - 1; j++) {
      int cnt = 0;
      if (s[i][j] == s[i][j + 1]) cnt++;
      if (s[i][j] == s[i + 1][j]) cnt++;
      if (s[i][j] == s[i + 1][j + 1]) cnt++;
      if (cnt == 0 || cnt == 2) ans++;
    }
  cout << ans << endl;
  return 0;
}
