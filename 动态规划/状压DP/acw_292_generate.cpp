#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

//292. 炮兵阵地 《算法竞赛进阶指南》, NOI2001
//解法二：三进制状压，DFS生成法转移
//https://www.acwing.com/video/1961/

int n, m;
char a[105][12];
int f[105][59049];
int p[12];

void dfs(int row, int state, int x, int ns, int cnt, int last) { //x是列 cnt填2的个数 last 上一个 填2的列位置
    if (x == m) {
        f[row][ns] = max(f[row][ns], f[row - 1][state] + cnt);
        return;
    }
    // 2下面只能填1
    if (state / p[x] % 3 == 2) { //这里的下面是指第x列的下面，然后计算完x列，考虑下一列的下面一格，ns目的是下一行的状态
        dfs(row, state, x + 1, ns + 1 * p[x], cnt, last);
        return;
    }
    // 1下面只能填0
    if (state / p[x] % 3 == 1) {
        dfs(row, state, x + 1, ns, cnt, last);
        return;
    }
    // 填2
    if (a[row][x] == 'P' && x - last >= 3) {
        dfs(row, state, x + 1, ns + 2 * p[x], cnt + 1, x);
    }
    // 填0
    dfs(row, state, x + 1, ns, cnt, last);
}

int main() {
    cin >> n >> m;
    p[0] = 1;
    for (int i = 1; i <= m; i++) p[i] = p[i - 1] * 3;
    for (int i = 1; i <= n; i++) scanf("%s", a[i]);
    memset(f, 0xcf, sizeof(f));
    f[0][0] = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p[m]; j++) {
            if (f[i][j] < 0) continue;
            dfs(i + 1, j, 0, 0, 0, -3);
        }
    int ans = 0;
    for (int j = 0; j < p[m]; j++)
        ans = max(ans, f[n][j]);
    cout << ans << endl;
}