#include <bits/stdc++.h>
using namespace std;

//POJ2228
//https://www.acwing.com/video/1965/

/*
DP环形问题的处理
断开环后，当作线性DP处理的时候，会有一种边界情况漏掉
所以直接做2次DP，第一次就当漏掉的做
第二次强制让状态方程满足漏掉的这种情况，然后重新做一次DP
*/

//f[i][j][0/1]  前i个小时选j个小时，且第i个小时没休息/休息(0/1)的最大恢复体力

const int N = 4010, M = 4010;
int n, m, f[2][M][2], w[N], ans; //f用滚动数组优化

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];
    if (m == 0) { cout << 0 << endl; return 0;}
    memset(f, 0xcf, sizeof f);
    f[1 & 1][0][0] = 0;
    f[1 & 1][1][1] = 0; //第一次DP 漏掉N休息1熟睡的情况
    for (int i =  2; i <= n; i++)
        for (int j = 0; j <= m; j++) {
            f[i & 1][j][0] = max (f[(i - 1) & 1][j][0], f[(i - 1) & 1][j][1]);
            if (j - 1 >= 0) f[i & 1][j][1] = max (f[(i - 1) & 1][j - 1][0], f[(i - 1) & 1][j - 1][1] + w[i]);
        }

    ans = max (f[n & 1][m][1], f[n & 1][m][0]);

    //第二次DP
    memset(f, 0xcf, sizeof f);
    f[1 & 1][1][1] = w[1]; //第N小时休息，第1小时熟睡 强制补充这种情况
    //以下内容和第一次DP相同
    for (int i = 2; i <= n; i ++)
        for (int j = 0; j <= m; j ++) {
            f[i & 1][j][0] = max (f[(i - 1) & 1][j][0], f[(i - 1) & 1][j][1]);
            if (j - 1 >= 0) f[i & 1][j][1] = max (f[(i - 1) & 1][j - 1][0], f[(i - 1) & 1][j - 1][1] + w[i]);
        }
    ans = max (ans, f[n & 1][m][1]); //第N天强制休息得到的结果取max
    cout << ans << endl;
    return 0;
}