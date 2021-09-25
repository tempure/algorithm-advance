#include <bits/stdc++.h>
using namespace std;


//考虑每个点和其子树的连接边

const int N = 1e5 + 10, M = 2 * N;

int n;
int h[N], e[M], ne[M], idx;
int ans;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int dfs(int u, int fa) {
    int sz = 1;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        int s = dfs(j, u);
        if (s % 2 == 0) ans++;
        sz += s;
    }
    return sz;
}

void solve() {
    memset(h, -1, sizeof h);
    cin >> n;
    if (n & 1) {
        cout << -1 << endl;
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    dfs(1, -1);
    cout << ans << endl;
}

int main() {
    solve();
    return 0;
}