#include <bits/stdc++.h>
using namespace std;

/*
用状态压缩DP 以及bitset优化空间
先求拓扑序，然后从后往前DP，每到一个点就往后遍历所有该点能到点
*/

const int N = 30010;

int n, m;
int h[N], e[N], ne[N], idx;
int d[N], q[N];
bitset<N> f[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void topsort() {
    int hh = 0, tt = -1;
    for (int i = 1; i <= n; i ++)
        if (!d[i]) q[++tt] = i;

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (--d[j] == 0) q[++tt] = j;
        }
    }
}

void solve() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m --) {
        int a, b;
        cin >> a >> b;
        d[b]++;
        add(a, b);
    }
    topsort();

    for (int i = n - 1; ~i; i --) {
        int j = q[i];
        f[j][j] = 1;
        for (int p = h[j]; ~p; p = ne[p])
            f[j] |= f[e[p]];
    }
    for (int i = 1; i <= n; i++) cout << f[i].count() << '\n';
}

int main() {
    solve();
    return 0;
}