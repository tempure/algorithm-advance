#include <bits/stdc++.h>
#define mp(a, b) make_pair(a, b)
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

//https://atcoder.jp/contests/abc191/submissions/19971196
/*
貌似不用题解说的把边反向然后求，但是估计这些做法本质都是一样的（?)
直接对每个点dijkstra一次，然后做完暴力找这个点的邻接点来更新答案
*/

vector<vector<pll>> g;
int n;

ll calc(int s) {
    vector<ll> dis(n + 1, 1LL << 60);
    dis[s] = 0;
    std::priority_queue<pll, vector<pll>, greater<>> pq;
    pq.push(mp(0, s));
    while (!pq.empty()) {
        ll now = pq.top().S, d = pq.top().F;
        pq.pop();
        if (d != dis[now]) continue;
        for (pll i : g[now]) {
            if (d + i.S < dis[i.F]) {
                dis[i.F] = d + i.S;
                pq.push(mp(d + i.S, i.F));
            }
        }
    }
    ll ans = 1LL << 60;
    for (int i = 1; i <= n; i++) {
        for (pll j : g[i]) {
            if (j.F != s) continue;
            ans = min(ans, dis[i] + j.S);
        }
    }
    return ans == (1LL << 60) ? -1 : ans;
}

int main() {
    int m;
    cin >> n >> m;
    g.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(mp(v, w));
    }

    for (int i = 1; i <= n; i++) {
        cout << calc(i) << "\n";
    }
    return 0;
}