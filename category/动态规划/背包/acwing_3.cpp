#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//完全背包

/*
将完全背包的集合划分理解为第i种物品选了0，1，2....k个，而不是”选或者不选“
这样状态转移方程就是f[i][j] = max(f[i][j],f[i-1][j-k*v[i]] + k*w[i])
这样不选第i种物品是在k=0的情况就包含了，k意思是第i种物品选k个
一维优化中，将01背包中j的逆序该为顺序枚举，意味着每个j都是同一层i转移的，也就意味着每种物品可以用无限多个
*/

const int N = 1010;
int n, m;   //m表示背包的容积 n表示物品个数
int v[N], w[N];
int f[N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i];

    for (int i = 1; i <= n; i++)
        for (int j = v[i]; j <= m; j++) { //和01背包唯一不同的地方
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    cout << f[m] << endl;

    return 0;
}