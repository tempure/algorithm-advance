#include <bits/stdc++.h>
using namespace std;


//本质就是考了floyd算法
//f[i][j]对于当前循环到的k，意思就是仅仅用1~k号点更新求出的全局最短路，也就是当前所有的f[i][j]
//那么只需要在每个k里面求完floyd之后再对当前求的所有f[i][j]求和即可

int n, m, x, y, z;
long long f[501][501], ans;
int main( ) {
    scanf("%d %d", &n, &m);
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= m; i ++) {
        scanf("%d %d %d", &x, &y, &z);
        f[x][y] = z;
    }
    for (int i = 1; i <= n; i ++) f[i][i] = 0;

    for (int k = 1; k <= n; k ++) {
        for (int i = 1; i <= n; i ++)
            for (int j = 1; j <= n; j ++) {
                // if (i == j || j == k || k == i) continue; //加上优化会更快 不加也能AC
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        for (int i = 1; i <= n; i ++)
            for (int j = 1; j <= n; j ++) {
                if (f[i][j] == 0x3f3f3f3f3f3f3f3fLL) continue;
                ans += f[i][j];
            }
    }
    cout << ans << endl;
    return 0;
}