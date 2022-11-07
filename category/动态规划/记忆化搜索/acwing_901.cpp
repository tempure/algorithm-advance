#include <iostream>
#include <cstring>
using namespace std;

/*
记忆化搜索: 因为每个点的最远距离必然是定值，如果某点已经求出，那么搜索其他点遇到该点时，直接加上该点的距离即可，不用再搜
*/

const int N = 310;

int n, m;
int h[N][N];
int f[N][N];  // f[i][j]  表示h[i][j] 为起点的最长路径长度

int dx[4] = { -1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int dp(int x, int y) {
    int &v = f[x][y];  //用v表示状态 引用 来更新 f[x][y] 记忆化搜索，已经算过直接返回
    if (v != -1) return v;

    v = 1; //该点没有搜过，初始最远距离为1 距离是能经过点的个数
    for (int i = 0; i < 4; i++) {
        int a = x + dx[i], b = y + dy[i];
        if (a >= 1 && a <= n && b >= 1 && b <= m && h[a][b] < h[x][y])
            v = max(v, dp(a, b) + 1);
    }

    return v;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> h[i][j];

    memset(f, -1, sizeof f); //初始化为 - 1 代表还没有算过

    int res = 0;
    for (int i = 1; i <= n; i++) //每个点都搜一遍
        for (int j = 1; j <= m; j++)
            res = max(res , dp(i, j));

    cout << res << endl;

    return 0;
}