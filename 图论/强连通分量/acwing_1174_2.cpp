#include <bits/stdc++.h>
using namespace std;

/*
考虑拓扑图的情况：那么只有出度为0的点个数只有一个，答案是1，否则是0

所以先求SCC缩点为拓扑图，缩点操作就是得出的id[N],dout[N]，sz[N]数组
如果存在一个SCC的出度为0，那么这个SCC的大小就是答案，否则答案为0
*/

const int N = 1e4 + 10, M = 5 * N;
int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int dout[N]; //每个SCC的出边度数
int id[N], scc_cnt, sz[N]; //sz 每个强连通分量的大小，最坏情况每个点都是一个强连通，所以数组要开N

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++ timestamp;
    stk[++top] = u, in_stk[u] = true; //注意是 ++top，不是top++

    for (int i =  h[u]; ~i; i = ne[i]) {
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
            y = stk[top--]; //top就是当前stack顶
            id[y] = scc_cnt;
            sz[id[y]]++;
        } while (u != y);
    }
}

void solve() {
    memset(h, -1, sizeof h);
    cin >> n >> m;
    while (m --) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }

    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);

    for (int i = 1; i <= n; i++)
        for (int j = h[i]; ~j; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a != b) dout[a]++;
        }

    int zeros = 0, sum = 0;
    for (int i = 1; i <= scc_cnt; i++)
        if (!dout[i]) {
            zeros++;
            sum += sz[i]; //出度为0的SCC的大小 唯一一个 就是答案
            if (zeros > 1) {
                sum = 0;
                break;
            }
        }
    cout << sum << endl;
}

int main() {
    solve();
    return 0;
}