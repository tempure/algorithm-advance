#include <bits/stdc++.h>
using namespace std;

/*2021.9.28 update
题目数据要求是 k <= n, 此时 S(n,k) 才有意义 不然答案就是0

理解 (n-1) * f[n-1][k]:
将第n个元素插入目前n-1个元素组成的圆排列中
也就是对于目前n-1个元素的所有k划分的圆排列中，每个圆排列都可以插到n-1个元素中的任意一个后面
*/

//==================old content============================//
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