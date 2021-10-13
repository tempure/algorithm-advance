#include <bits/stdc++.h>
using namespace std;

/*2021 10.13 update
不能分开跑2次DP的原因是，DP要满足无后效性
第一次跑完是在第一次的全局最优，第二次是在第一次基础上的局部最优
这有后效性的两次不一定是全局最优

https://www.acwing.com/solution/content/15868/
*/

const int N = 55;
int w[N][N];
int f[2 * N][N][N];

void solve() {
    int m, n;
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> w[i][j];
    for (int k = 2; k <= m + n; k++)
        for (int i1 = 1; i1 <= m; i1 ++)
            for (int i2 = 1; i2 <= m; i2++) {
                int j1 = k - i1, j2 = k - i2;
                if (j1 >= 1 && j1 <= n && j2 >= 1 && j2 <= n) {
                    int t = w[i1][j1];
                    if (i1 != i2) t += w[i2][j2];
                    int &x = f[k][i1][i2];

                    x = max(x, f[k - 1][i1 - 1][i2 - 1] + t);  // 下 下
                    x = max(x, f[k  - 1][i1 - 1][i2] + t); //下 右
                    x = max(x, f[k - 1][i1][i2 - 1] + t);// 右下
                    x = max(x, f[k - 1][i1][i2] + t); //下下
                }
            }
    cout << f[n + m][m][m] << endl;
}

int main() {
    solve();
    return 0;
}