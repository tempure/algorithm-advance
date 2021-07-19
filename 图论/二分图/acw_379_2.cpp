#include <bits/stdc++.h>
using namespace std;

/*
最小路径覆盖和最小路径重复覆盖都是对于DAG而言的
DAG本身就是二分图，可以用匈牙利算法求最大匹配

最小路径覆盖：选出不重复的路径，也就是所有路径都不能有相同的点，覆盖所有DAG上的点
最小路径重复覆盖：可以有重复的点，也就是多个路径经过同一个点

最小路径重复覆盖先在DAG上求一次传递闭包，然后再求最大匹配，覆盖的路径数量就是点数-最大匹配

对于传递闭包可以解决重复覆盖的理解：考虑最简单的两条路径交叉，如果不能重复，那就要绕过交界点，最少要三条路径覆盖
如果有了传递闭包，那么交界点处比如是a->b->c，b是交界点，那么floyd后a->c直接有边，可以绕过b，这样求出的路径是2条了
*/

const int N = 210, M = 30010;
int n, m;
bool st[N], g[N][N]; //g存图
int mc[N];

bool dfs(int x) {
    for (int i = 1; i <= n; i++)
        if (g[x][i] && !st[i]) {
            st[i] = true;
            int t = mc[i];
            if (t == 0 || dfs(t)) {
                mc[i] = x;
                return true;
            }
        }
    return false;
}

void solve() {
    cin >> n >> m;
    while (m --) {
        int a, b;
        cin >> a >> b;
        g[a][b] = true;
    }

    //floyd
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                g[i][j] |= g[i][k] & g[k][j];

    int res = 0;
    for (int i = 1; i <= n; i++) {
        memset(st, 0, sizeof st);
        if (dfs(i)) res++;
    }
    cout << n - res << endl;
}

int main() {
    solve();
    return 0;
}