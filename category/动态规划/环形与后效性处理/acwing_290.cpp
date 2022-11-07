#include <bits/stdc++.h>
using namespace std;

//Codeforces24D DP+高斯消元 后效性处理（行内关系成环）
//https://www.acwing.com/video/1963/
//https://www.acwing.com/activity/content/code/content/592411/
//https://www.acwing.com/solution/content/5167/

/*
不需要裸的高斯，矩阵中每行只有2到3个数不是零，所以可以O(m)消元。
每行消元一次，总复杂度O(N*M)
*/

const int N = 1010;
int n, m, x, y;
double f[N][N], d[N][N];

void work() {
    //先用每行的主元消去下面一行
    for (int i = 1; i <= m; i++) {
        double w = 1.0 / d[i][i];
        d[i][i] *= w;
        d[i][m + 1] *= w;
        if (i == m) break;
        d[i][i + 1] *= w;
        w = d[i + 1][i] / d[i][i];
        d[i + 1][i] -= w * d[i][i];
        d[i + 1][i + 1] -= w * d[i][i + 1];
        d[i + 1][m + 1] -= w * d[i][m + 1];
    }
    //现在每行主元都是1，但是主元d[i][i]上面一个元素还没消去
    //此时不用再消了，直接模拟一下消去的过程，把增广列的答案算出来就足够了
    for (int i = m - 1; i; i--)
        d[i][m + 1] -= d[i + 1][m + 1] * d[i][i + 1];
}

int main() {
    cin >> n >> m >> x >> y;
    for (int i = n - 1; i >= x; i--) { //每行内做高斯消元
        d[1][1] = d[m][m] = -2 / 3.0;
        d[1][2] = d[m][m - 1] = 1 / 3.0;
        for (int j = 2; j < m; j++) {
            d[j][m + 1] = -f[i + 1][j] / 4.0 - 1;
            d[j][j] = -3 / 4.0;
            d[j][j - 1] = d[j][j + 1] = 1 / 4.0;
        }
        if (m == 1) d[1][1] = -1 / 2.0;
        d[1][m + 1] = -f[i + 1][1] / 3.0 - 1;
        d[m][m + 1] = -f[i + 1][m] / 3.0 - 1;
        if (m == 1) d[m][m + 1] = -f[i + 1][m] / 2.0 - 1;
        work();
        for (int j = 1; j <= m; j++) f[i][j] = d[j][m + 1];
    }
    printf("%.4f\n", f[x][y]);
    return 0;
}