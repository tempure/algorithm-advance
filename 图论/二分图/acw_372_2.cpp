#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define x first
#define y second

/*
第一次写的那个理解是错的，注释也是错的
st[]数组，也就是dfs时候的判重数组，作用是在寻找增广路的过程中，也就是抢别人女朋友的过程中
标记这个女生已经被“抢了”，让她男朋友重新配对的时候不要再找原来这个女朋友了...

另外，匈牙利算法可以理解为有顺序的进行的，每次dfs都是在之前的局面继续dfs，这个局面是指上一次dfs后的match[]数组结果

所以才需要双for枚举所有待匹配的点进行dfs 复杂度O(N*M)
*/

const int N = 100;
int n, m;
pii mc[N][N];
bool g[N][N], st[N][N];

int dx[4] = { -1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

bool dfs(int x, int y) {
    for (int i = 0; i < 4; i++) {
        int a = x + dx[i], b = y + dy[i];
        if (a < 1 | a > n || b < 1 || b > n) continue;
        if (st[a][b] || g[a][b]) continue;

        pii t = mc[a][b];
        st[a][b] = true;
        if (t.x == 0 || dfs(t.x, t.y)) {
            mc[a][b] = {x, y};
            return true;
        }
    }
    return false;
}

void solve() {
    cin >> n >> m;
    while (m -- ) {
        int x, y;
        cin >> x >> y;
        g[x][y] = true;
    }

    int res = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i + j & 1 && !g[i][j]) {
                memset(st, 0, sizeof st);
                if (dfs(i, j)) res++;
            }
    cout << res << endl;
}

int main() {
    solve();
    return 0;
}