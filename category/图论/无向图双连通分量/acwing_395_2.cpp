#include <bits/stdc++.h>
using namespace std;

const int N = 5010, M = 20010;
int n, m;
int edcc_cnt;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], id[N], top;
bool is_brige[M];
int d[N]; //出度 + 入度

//求 EDCC，然后独立的非EDCC是拓扑结构，亮亮配对连边整体构成EDCC

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u, int from) { //点 边
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j, i);
            low[u] = min(low[u], low[j]);
            if (dfn[u] < low[j]) //回溯过程中找割边 这个割边回溯到的是搜索树的边，也就是DFS序的边
                is_brige[i] = is_brige[i ^ 1] = true;
        }
        else if (i != (from ^ 1)) //u->j 不要搜j->u的这条反向边
            low[u] = min(low[u], dfn[j]);
    }
    if (dfn[u] == low[u]) {
        ++edcc_cnt;
        int y;
        do {
            y = stk[top--];
            id[y] = edcc_cnt;
        } while (y != u);
    }
}

void solve() {
    memset(h, -1, sizeof h);
    cin >> n >> m;

    while (m --) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    tarjan(1, -1);

    for (int i = 0; i < idx; i++)
        if (is_brige[i])
            d[id[e[i]]]++;
    int cnt = 0;
    for (int i = 1; i <=  edcc_cnt; i++)
        if (d[i] == 1) cnt++;
    cout << (cnt + 1) / 2 << '\n';
}

int main() {
    solve();
    return 0;
}