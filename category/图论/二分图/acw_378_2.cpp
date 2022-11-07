#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define x first
#define y second

const int N = 110;
bool st[N][N], g[N][N];
pii mc[N][N];

int dx[8] = { -2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int n, m, k;

bool dfs(int x, int y) {
    for (int i = 0; i < 8; i++) {
        int a = x + dx[i], b = y + dy[i];
        if (a < 1 || a > n || b < 1 || b > m) continue;
        if (g[a][b] || st[a][b]) continue;
        st[a][b] = true;
        pii t = mc[a][b];
        if (t.x == 0 || dfs(t.x, t.y)) {
            mc[a][b] = {x, y};
            return true;
        }
    }
    return false;
}

void solve() {
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x  >> y;
        g[x][y] = true;
    }
    int res = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if ((j + i) & 1 || g[i][j]) continue;
            memset(st, 0, sizeof st);
            if (dfs(i, j)) res ++;
        }
    cout << n * m - res - k << endl;
}

int main() {
    solve();
    return 0;
}