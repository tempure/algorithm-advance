#include <iostream>
using namespace std;

/*
自然数拆分 完全背包解法

f[i][j]表示从[1,i]中以完全背包的方式选择，总和为j
转移方程和完全背包一样：f[i][j] = f[i-1][j] + f[i][j-v[i]] + w[i]
但是本题是求方案数，改写为：f[i][j] = f[i-1][j] + f[i][j-i] // f[i-1][j]就是不选i这个数 f[i][j-i]就是选一个i
求的是方案数，那就不用加什么w[i],没有这个数组了，每个物品的权值是0，体积是本身的数值大小i

最后优化到一维即可

当采用正序循环时，对应着每个i可以选无数次, 也对应f[i][j] = f[i,j-v[i]] + w[i] 这个均处于i阶段的2个状态之间的转移方程
*/

const int N = 1010;
int f[N];

const int mod = 1e9 + 7;

int main() {
    int n; cin >> n;

    f[0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            f[j] = (f[j] + f[j - i]) % mod;

    cout << f[n] << endl;

    return 0;
}