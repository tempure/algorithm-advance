#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

//statement of D is really ambiguous
// I don't understand it well...

int main(void)
{
  int m;
  cin >> m;

  vector<int> G[10];
  int u, v;
  for (int i = 1; i <= m; i++) {
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  int p; string s = "999999999";
  for (int i = 1; i <= 8; i++) {
    cin >> p;
    s[p - 1] = i + '0';
  }

  queue<string> Q;
  Q.push(s);
  map<string, int> mp;
  mp[s] = 0;

  while (Q.size()) {
    string s = Q.front(); Q.pop();
    for (int i = 1; i <= 9; i++) if (s[i - 1] == '9') v = i;

    for (auto u : G[v]) {
      string t = s;
      swap(t[u - 1], t[v - 1]);
      if (mp.count(t)) continue;
      mp[t] = mp[s] + 1;
      Q.push(t);
    }
  }
  if (mp.count("123456789") == 0) cout << -1 << endl;
  else cout << mp["123456789"] << endl;

  return 0;
}
