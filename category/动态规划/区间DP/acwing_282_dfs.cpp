#include <bits/stdc++.h>
using namespace std;


//记忆化搜索写法，本质还是 DP
//与区间DP复杂度一样都是O(N^3)

const int N = 310;
int f[N][N], s[N];
int n;

int dfs(int l, int r) {
    if (f[l][r] != 0x3f3f3f3f) return f[l][r];
    for (int k = l; k < r; k++)
        f[l][r] = min(f[l][r], dfs(l, k) + dfs(k + 1, r));
    f[l][r] += s[r] - s[l - 1];
    return f[l][r];
}

int main() {
    cin >> n;
    memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] += s[i - 1];
        f[i][i] = 0;
    }
    dfs(1, n);
    cout << f[1][n] << endl;
}