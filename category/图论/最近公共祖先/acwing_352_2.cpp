#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 10, M = N * 2;
int n, m;
int h[N], e[M], ne[M], idx, w[M];
int depth[N], fa[N][17]; // 0~16
int q[N];
int d[N]; //差分数组

int ans = 0;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void bfs() {
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[1] = 1;
    int hh = 0, tt = 0;
    q[0] = 1;
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                q[++tt] = j;
                fa[j][0] = t;
                for (int k = 1; k <= 16; k++)
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
            }
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int k = 16; k >= 0; k --)
        if (depth[fa[a][k]] >= depth[b])
            a = fa[a][k];
    if (a == b) return a;

    for (int k = 16; k >= 0; k--)
        if (fa[a][k] != fa[b][k]) {
            a = fa[a][k];
            b = fa[b][k];
        }
    return fa[a][0];
}

int dfs(int u, int fa) {
    int res = d[u];
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j != fa) {
            int s = dfs(j, u);
            if (s == 0) ans += m;
            else if (s == 1) ans++;
            res += s; //子树求和
        }
    }
    return res;
}

void solve() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }

    bfs();
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        int p = lca(a, b);
        d[a] += 1, d[b] += 1, d[p] -= 2;
    }
    dfs(1, -1);
    cout << ans << endl;
}

int main() {
    solve();
    return 0;
}