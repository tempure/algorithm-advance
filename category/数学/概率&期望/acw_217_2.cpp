#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, M = 2 * N;
int n, m;
int h[N], e[M], ne[M], w[M], idx;
int dout[N];
double f[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

double dfs(int u) {
    if (f[u] >= 0) return f[u]; //f[]是浮点数，不能用f[u]==-1这种判断
    if (u == n) return f[u] = 0; //终点
    f[u] = 0; //当前点先初始置为0 然后再加
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        f[u] += (w[i] + dfs(j)) / dout[u];  //递归反向搜
    }
    return f[u];
}

void solve() {
    memset(f, -1, sizeof f);
    memset(h, -1, sizeof h);
    cin >> n >> m;
    while (m --) {
        int a, b, c;
        cin >> a >> b >> c;
        dout[a]++;
        add(a, b, c);
    }
    printf("%.2lf\n", dfs(1));
}

int main() {
    solve();
    return 0;
}