#include <bits/stdc++.h>
using namespace std;

/*
第一类斯特林数： f[n][k]表示将1~n划分为k个不同的圆排列的方案数
考虑将第n个数放入一个新的圆排列和放入旧的圆排列中即可,本质还是DP
直接O(n^2)递推 f[n][k] = f[n-1][k-1] + (n-1)*f[n-1][k]
*/

typedef long long ll;
const int N = 1010, mod = 1e9 + 7;

int n, k;
int f[N][N];

int main() {
    scanf("%d%d", &n, &k);
    f[0][0] = 1; //规定的边界
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++)
            f[i][j] = (f[i - 1][j - 1] + (ll)(i - 1) * f[i - 1][j]) % mod;

    printf("%d", f[n][k]);

    return 0;
}