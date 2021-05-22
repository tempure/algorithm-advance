#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//01背包 每件物品 最多用一次 也就是用1次 或者0次

/*
一维优化，内存j逆着循环的解释:
朴素的二维的状态转移方程，第一个优化之后是恒等式，就不用了
第二个方程原本为 f[i][j] = max(f[i][j], f[i-1][j-v[i]] + w[i])
对于f[i-1][j-v[i]], 对于当前循环的i，其j-v[i]是f[i-1][j-v[i]] 而不是 f[i][j-v[i]]
但是一维情况内层的j如果也是递增枚举的话, j-v[i]会在j之前被算，也就是j-v[i]不是i-1层的j-v[i]
由于第一维只有2种，本来就可以用滚动数组来优化，如果我们逆序枚举j，那么计算j-v[i]会在j之后算，
当计算f[j] = max(f[j], f[j - v[i]] + w[i]); 时候，此时的j-v[i]是旧的j-v[i],旧是指第一维是旧的，
那么肯定就是f[i-1][j-v[i]]了，因为第一维度只有2种可能
*/

const int N = 1010;
int n, m;   //m表示背包的容积 n表示物品个数
int v[N], w[N];
int f[N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i];

    for (int i = 1; i <= n; i++)
        for (int j = m; j >= v[i]; j--) {

            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    cout << f[m] << endl;

    return 0;
}