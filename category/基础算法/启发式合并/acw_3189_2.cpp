#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
const int N = 1e5 + 10, M = 2 * N;
int h[N], e[M], ne[M], idx;
int color[N], son[N], sz[N], cnt[N];
ll ans[N], sum;
int mx;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a] , h[a] = idx++;
}

int dfs_son(int u, int father) {
    sz[u] = 1;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == father) continue;
        sz[u] += dfs_son(j, u);
        if (sz[j] > sz[son[u]]) son[u] = j;
    }
    return sz[u];
}

void update(int u, int father, int sign, int pson) {
    int c = color[u];
    cnt[c] += sign;
    if (cnt[c] > mx) mx = cnt[c], sum = c;
    else if (cnt[c] == mx) sum += c;

    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == father || j == pson) continue;
        update(j, u, sign, pson);
    }
}

void dfs(int u, int father, int op) {
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == father || j == son[u]) continue;
        dfs(j, u, 0);
    }
    if (son[u]) dfs(son[u], u, 1); // 叶子节点没有son 所以要if判断
    update(u, father, 1, son[u]);

    ans[u] = sum;
    if (!op) update(u, father, -1, 0), sum = mx = 0;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> color[i];
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    dfs_son(1, -1);
    dfs(1, -1, 1); //root is heavy node 0 means light node

    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
}

int main() {
    solve();
    return 0;
}