#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
using ll = long long;

/*
题意为给定一个DFS序（欧拉序）求满足该序列的 不同构 树结构的数量
区间DP/记忆化搜索
此为记忆化搜索写法

https://www.acwing.com/solution/content/10533/
https://www.acwing.com/activity/content/code/content/592398/
https://www.acwing.com/video/1969/  lyd 讲解
*/

const int N = 310, mod = 1e9;
char s[N];
ll f[N][N];

ll dfs(int l, int r) {
    if (l > r) return 0;
    if (l == r) return 1;
    if (f[l][r] != -1) return f[l][r];
    if (s[l] != s[r]) return 0;
    f[l][r] = 0;
    for (int k = l + 2; k <= r; k++)
        (f[l][r] += dfs(l + 1, k - 1) * dfs(k, r)) %= mod;
    return f[l][r];
}

int main() {
    scanf("%s", s + 1);
    memset(f, -1, sizeof f);
    cout << dfs(1, strlen(s + 1)) << endl;
    return 0;
}