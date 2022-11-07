#include <bits/stdc++.h>
using namespace std;

const int N = 110, M = N * N;
int h[N], ne[M], e[M], idx;
int scc_cnt;
bool in_stk[N];
int dfn[N], timestamp, stk[N], low[N];
int din[N], dout[N];
int top;
int id[N];
int n;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u, in_stk[u] = true;

    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j]) low[u] = min(low[u], dfn[j]);
    }
    if (dfn[u] == low[u]) {
        ++scc_cnt;
        int y;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
        } while (y != u);
    }
}

void solve() {
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int t;
        while (cin >> t && t) add(i, t);
    }

    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);

    for (int i = 1; i <= n; i++)
        for (int j = h[i]; ~j; j = ne[j]) {
            int k = e[j];
            int a = id[i];
            int b = id[k];
            if (a != b) {
                dout[a]++;
                din[b]++;
            }
        }

    int a = 0, b = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (!din[i]) a++;
        if (!dout[i])b++;
    }
    cout << a << endl;

    if (scc_cnt == 1) cout << 0 << endl;
    else cout << max(a, b) << endl;
}

int main() {
    solve();
    return 0;
}