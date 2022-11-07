#include <bits/stdc++.h>
using namespace std;

/*
将每一棵基环树在环和周围的树的连接处断开 然后树上dp
f[i][1] 表示 选i 那么和i连接的点都不能选 就是f[j][0]
f[i][0] 就是 不选i 那么周围的点可选可不选 就是max(f[j][0], f[j][1])
*/

typedef long long ll;

const int N = 1000010, INF = 1e9;

int n;
int h[N], e[N], rm[N], w[N], ne[N], idx; //rm[]表示边是否被删除
ll f1[N][2], f2[N][2];
bool st[N], ins[N];
ll ans;

inline void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs_f(int u, int ap, ll f[][2]) { //ap代表不能选的点
    for (int i = h[u]; i != -1; i = ne[i]) {
        if (rm[i]) continue;
        int j = e[i];
        dfs_f(j, ap, f);
        f[u][0] += max(f[j][0], f[j][1]);
    }

    f[u][1] = -INF;
    if (u != ap) {
        f[u][1] = w[u];
        for (int i = h[u]; i != -1; i = ne[i]) {
            if (rm[i]) continue;
            int j = e[i];
            f[u][1] += f[j][0];
        }
    }
}

void dfs_c(int u, int from) {
    st[u] = ins[u] = true;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j])  dfs_c(j, i);
        else if (ins[j]) {
            rm[i] = 1;
            dfs_f(j, -1, f1); //不选j
            dfs_f(j, u, f2); //选j
            ans += max(f1[j][0], f2[j][1]);
        }
    }
    ins[u] = false;
}

int main() {
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(b, i); //建外向树
        w[i] = a; //点权
    }

    for (int i = 1; i <= n; i++)
        if (!st[i])
            dfs_c(i, -1);
    printf("%lld\n", ans);

    return 0;
}