#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, M = 2e6 + 10;

int n, m, mod;
int h[N], hs[N], e[M], ne[M], idx;
int stk[N], timestamp, dfn[N], low[N];
bool in_stk[N];
int sz[N], scc_cnt, id[N], top;
int f[N], g[N];

void add(int h[], int a, int b) {
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

    if (low[u] == dfn[u]) {
        ++scc_cnt;
        int y;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            sz[scc_cnt]++;
        } while (y != u);
    }
}

void solve() {
    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);
    cin >> n >> m >> mod;

    while (m --) {
        int a, b;
        cin >> a >> b;
        add(h, a, b);
    }

    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);

    unordered_set<long long> S;
    for (int i = 1; i <= n; i++)
        for (int j = h[i]; ~j; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            long long hash = 1000000ll * a + b;
            if (a != b && !S.count(hash)) { //两个SCC之间只加一条边 优化
                add(hs, a, b);
                S.insert(hash);
            }
        }

    /*
    拓扑序是 DFS 的逆序，因为scc_cnt是在回溯的时候求的
    而DP是按照拓扑序来的，所以scc_cnt递减顺序来DP
    */
    for (int i = scc_cnt; i; i--) {
        if (!f[i]) {
            f[i] = sz[i];
            g[i] = 1;
        }
        for (int j = hs[i]; ~j; j = ne[j]) {
            int k = e[j];
            if (f[k] < f[i] + sz[k]) {
                f[k] = f[i] + sz[k];
                g[k] = g[i];
            }
            else if (f[k] == f[i] + sz[k])
                g[k] = (g[k] + g[i]) % mod;
        }
    }

    //这里遍历的时候和顺序没关系，顺序逆序都可以
    int maxf = 0, sum = 0;
    for (int i = 1; i <= scc_cnt; i++)
        if (f[i] > maxf) {
            maxf = f[i];
            sum = g[i];
        }
        else if (f[i] == maxf)
            sum = (sum + g[i]) % mod;

    cout << maxf << endl;
    cout << sum << endl;
}

int main() {
    solve();
    return 0;
}