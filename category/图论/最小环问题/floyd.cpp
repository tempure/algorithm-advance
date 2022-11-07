//https://zhuanlan.zhihu.com/p/342293693

//限制条件：无向图

#include <bits/stdc++.h>
using namespace std;

const int N = 1e3, INF = 0x3f3f3f3f;
int edge[N][N];
int dis[N][N]; //不能复用 dis，要开一个edge单独存边
int n, m;

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j) edge[i][j] = dis[i][j] = INF; //初始化
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        edge[u][v] = edge[v][u] = min(edge[u][v], w);
        dis[u][v] = dis[v][u] = edge[u][v];
    }

    //floyd
    int ans = INF;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i < k; i++) //k是分割点，所以不能等于k
            for (int j = i + 1; j < k; j++) // 注意这里i,j不能相等
                ans = min(ans, dis[i][j] + edge[j][k] + edge[k][i]);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    }
    if (ans == INF) printf("No solution.\n");
    else printf("%d\n", ans);
}

int main() {
    solve();
    return 0;
}