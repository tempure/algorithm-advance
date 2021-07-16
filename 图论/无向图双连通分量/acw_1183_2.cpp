#include <bits/stdc++.h>
using namespace std;

/*
此题不需要保存VDCC，只在求VDCC的过程中更新答案，所以不需要栈
*/

const int N = 10010, M = 30010;
int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], ts;
int root, ans;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++ts;
    int tree_cnt = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if (dfn[u] <= low[j]) tree_cnt++;
        }
        else low[u] = min(low[u], dfn[j]);
    }
    if (u != root && tree_cnt) tree_cnt++;
    ans = max(ans, tree_cnt);
}

void solve() {
    memset(dfn, 0, sizeof dfn);
    memset(h, -1, sizeof h);
    idx = ts = 0;
    ans = 0;
    while (m -- ) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    int cnt = 0;
    for (root = 0; root < n; root++)
        if (!dfn[root]) {
            cnt++; //连通块数量
            tarjan(root);
        }
    cout << ans + cnt - 1 << endl;
}

int main() {
    while (cin >> n >> m, n || m)
        solve();
    return 0;
}