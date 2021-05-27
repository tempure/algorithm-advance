#include <iostream>
using namespace std;

/*
自然数划分 lunatic 版 另一种DP方法 O(N^2)

f[i][j]： 总和为i,用了j个数的方案总数
f[i][j] = f[i-1][j-1] + f[i - j][j]

将集合分为当前选的所有数中的最小值就是1，以及最小值大于1两部分

第一部分，在集合中减去一个1，那么f[i][j] = f[i-1][j-1]
第二部分，给集合中的每个数减去一个1, f[i][j] = f[i-j][j] //集合中数的个数不变

为什么这么划分和转移，以及正确性？ 我也不会！
*/

const int N = 1010, mod = 1e9 + 7;

int n;
int f[N][N];

int main() {
    cin >> n;
    f[0][0] = 1;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            f[i][j] = (f[i - 1][j - 1] + f[i - j][j]) % mod;

    int res = 0;
    for (int i = 1; i <= n; i++) res = (res + f[n][i]) % mod;

    cout << res << endl;

    return 0;
}