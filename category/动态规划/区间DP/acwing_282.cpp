#include <bits/stdc++.h>
using namespace std;
const int N = 310;

/*
f[i][j] 将[i,j]区间内的所有石子合并成一堆的最小代价
所有区间DP问题都是最外层枚举区间长度，然后枚举左端点，右端点由区间长度推出
最后枚举区间内的分割点k，将区间分成2部分来求最值，时间复杂度O(N^3)

转移方程: f[i][j] = min(f[i][j], f[i,k] + f[k+1,j] + s[j] - s[i-1])
*/

int n;
int s[N]; //前缀和
int f[N][N];

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i] += s[i - 1];

    for (int len = 2; len <= n; len++) //长度为1的区间就是一个石子，代价为0，不需要考虑,而且从1开始会错
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            f[i][j] = 2e9;
            for (int k = i; k < j; k++)
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j] + s[j] - s[i - 1]);
        }

    cout << f[1][n] << endl;

    return 0;
}