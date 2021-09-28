#include <bits/stdc++.h>
using namespace std;

/*
注意区分隔板法；处理的那种问题，那个问题是初始所有元素都有序排成一个序列
考虑用完全排列来计算这个问题也不行，因为一个被分割集合内的元素都是无序的

考虑递推 for 循环的细节，与第一类斯特林数一样，因为外层循环和内层循环都是递增枚举
所以对于S(n,k), 当k > n 的时候，必然递推后值还是0
*/


//========================old content==================
/*
第二类斯特林数：f[n][k]表示将n个不同元素划分为k个非空子集
和第一类斯特林数不同的就是第二类不需要排列，只需要划分
同样O(N^2)递推：f[n][k] = f[n-1][k-1] + k*f[n-1][k]
*/

const int N = 1010, mod = 1e9 + 7;
int f[N][N];
int n, k;

void solve() {
    cin >> n >> k;
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++)
            f[i][j] = (f[i - 1][j - 1] + 1ll * j * f[i - 1][j]) % mod;
    cout << f[n][k] << endl;
}

int main() {
    solve();
    return 0;
}