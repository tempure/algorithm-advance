#include <bits/stdc++.h>
#define ll long long
using namespace std;

//https://www.cnblogs.com/zdragon1104/p/12734682.html
//区间DP + 贪心
//先考虑A[i] 最大的放在左边还是右边，递减考虑
//递归先求小区间
//f[l][r] 表示rearrange区间[l,r]后区间[l,r]的最大值

const int N = 2e3 + 5;
ll f[N][N];
pair<int, int> p[N];

ll cal(int cnt, int l, int r) {
    if (l > r) return 0;
    if (~f[l][r]) return f[l][r];
    ll ans = 1LL * p[cnt].first * abs(p[cnt].second - l) + cal(cnt + 1, l + 1, r);
    ans = max(ans, 1LL * p[cnt].first * abs(p[cnt].second - r) + cal(cnt + 1, l, r - 1));
    return f[l][r] = ans;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        p[i] = {x, i};
    }
    sort(p + 1, p + n + 1, [](pair<int, int> a, pair<int, int> b) {
        return a.first > b.first;
    });
    memset(f, -1, sizeof f);
    printf("%lld\n", cal(1, 1, n));
    return 0;
}