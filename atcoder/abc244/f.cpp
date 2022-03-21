#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc244/editorial/3617
//题意好迷。。神迷题
int n, m;
vector<int> G[20];
int dist[1 << 17][17];

int main(void)
{
  cin >> n >> m;
  int u, v;
  for (int i = 1; i <= m; i++) {
    cin >> u >> v;
    u--, v--;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  int N = 1 << n;
  for (int i = 0; i < N; i++) for (int j = 0; j < n; j++) dist[i][j] = inf;
  queue<pair<int, int>> Q;
  for (int i = 0; i < n; i++) dist[1 << i][i] = 1, Q.push({1 << i, i});

  while (Q.size()) {
    int s = Q.front().first, v = Q.front().second; Q.pop();
    for (auto u : G[v]) {
      int ns = s ^ (1 << u);
      if (dist[ns][u] < inf) continue;
      dist[ns][u] = dist[s][v] + 1;
      Q.push({ns, u});
    }
  }

  long long ans = 0;
  for (int i = 1; i < N; i++) {
    int mn = inf;
    for (int j = 0; j < n; j++) mn = min(mn, dist[i][j]);
    ans += mn;
  }
  cout << ans << endl;

  return 0;
}
