#include <bits/stdc++.h>
using namespace std;

const int N = 15;
int n, m, k;
char g[N][N][N];

//就直接 dfs 一遍就行了，然后搜过的地方打上标记

int dx[] = {1, 0, 0, -1, 0, 0};
int dy[] = {0, 1, 0, 0, -1, 0};
int dz[] = {0, 0, 1, 0, 0, -1};

int dfs(int x, int y, int z) {
    g[x][y][z] = '#';
    int res = 1;
    for (int i = 0; i < 6; i++) {
        int a = x + dx[i], b = y + dy[i], c = z + dz[i];
        if (a < 0 || a >= k || b < 0 || b >= n || c < 0 || c >= m) continue;
        if (g[a][b][c] == '#') continue;

        res += dfs(a, b, c);
    }
    return res;
}

int main() {
    cin >> k >> n >> m;
    for (int i = 0; i < k; i++)
        for (int j = 0; j < n; j++)
            cin >> g[i][j];

    int y, z;
    cin >> y >> z;
    y--, z--;  //下标从 0 开始
    cout << dfs(0, y, z) << endl;

    return 0;
}