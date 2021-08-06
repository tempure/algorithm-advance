#include <bits/stdc++.h>
using namespace std;

const int N = 2010, M = 6010;
int h[N], e[M], ne[M], idx;
int f[N];
int n, m, k;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int sg(int u) {
    if (f[u] != -1) return f[u];
    set<int> S;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        S.insert(sg(j));
    }
    for (int i = 0; ; i++)
        if (!S.count(i)) {
            f[u] = i;
            break;
        }
    return f[u];
}

void solve() {
    memset(h, -1, sizeof h);
    memset(f, -1, sizeof f);
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }

    int res = 0;
    for (int i = 0; i < k; i++) {
        int x; cin >> x;
        res ^= sg(x);
    }
    if (res) puts("win");
    else puts("lose");
}

int main() {
    solve();
    return 0;
}