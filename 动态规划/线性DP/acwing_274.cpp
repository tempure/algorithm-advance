#include <bits/stdc++.h>
using namespace std;

//CH5102 Mobile Service
//solution from  lydrainbowcat
//https://www.acwing.com/video/1977/

const int N = 210;
const int M = 1010;
int f[2][N][N], p[M], c[N][N];
int n, m;

void solve() {
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            cin >> c[i][j];
    for (int i = 1; i <= n; i++) cin >> p[i];
    p[0] = 3; //z position init
    memset(f, 0x3f, sizeof f);
    f[0][1][2] = 0;
    for (int i = 1; i <= n; i++)
        for (int x = 1; x <= m; x++)
            for (int y = 1; y <= m; y++)
                if (f[i - 1 & 1][x][y] != 0x3f3f3f3f) { // 滚动数组优化
                    int z = p[i - 1];
                    // the problem doesn't allow two people at the same place
                    if (y != p[i] && z != p[i]) f[i & 1][y][z] = min(f[i & 1][y][z], f[i - 1 & 1][x][y] + c[x][p[i]]);
                    if (x != p[i] && z != p[i]) f[i & 1][x][z] = min(f[i & 1][x][z], f[i - 1 & 1][x][y] + c[y][p[i]]);
                    if (x != p[i] && y != p[i]) f[i & 1][x][y] = min(f[i & 1][x][y], f[i - 1 & 1][x][y] + c[z][p[i]]);
                    f[i - 1 & 1][x][y] = 0x3f3f3f3f;
                }
    int ans = 1 << 30;
    for (int x = 1; x <= m; x++)
        for (int y = 1; y <= m; y++)
            ans = min(ans, f[n & 1][x][y]);
    cout << ans << endl;
}

int main() {
    solve();
    return 0;
}