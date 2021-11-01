#include <bits/stdc++.h>
using namespace std;

const int N = 55;

int n;
char g[N][N];
int dx[4] = { -1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
bool st1[N][N], st2[N][N];

void dfs(int x, int y, bool st[][N]) {
    st[x][y] = true;
    for (int i = 0; i < 4; i ++ ) {
        int a = x + dx[i], b = y + dy[i];
        if (a >= 0 && a < n && b >= 0 && b < n && !st[a][b] && g[a][b] == '0')
            dfs(a, b, st);
    }
}

void solve() {
    cin >> n;
    int sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;
    sx --, sy --, tx --, ty --; //下标从0开始
    for (int i = 0; i < n; i++) cin >> g[i];

    dfs(sx, sy, st1);
    if (st1[tx][ty]) cout << 0 << '\n';
    else {
        dfs(tx, ty, st2);
        int res = 1e8;
        for (int i = 0; i < n; i ++ )
            for (int j = 0; j < n; j ++ )
                if (st1[i][j])
                    for (int x = 0; x < n; x ++ )
                        for (int y = 0; y < n; y ++ )
                            if (st2[x][y])
                                res = min(res, (i - x) * (i - x) + (j - y) * (j - y));
        cout << res << endl;
    }
}

int main() {
    int t = 1;
    //cin >> t;
    while (t --) solve();
    return 0;
}
