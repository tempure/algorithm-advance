#include <bits/stdc++.h>
using namespace std;

//POJ3666
//https://www.acwing.com/video/399/
//https://www.acwing.com/solution/content/4956/

//贪心 + 线性DP

const int N = 2010, INF = 0x3f3f3f3f;
int a[N], b[N];
int f[N][N];
int n;

int dp() {
    for (int i = 1; i <= n; i++) b[i] = a[i];
    sort(b + 1, b + n + 1); //A'[]
    for (int i = 1; i <= n; i++) {
        int minv = INF;
        for (int j = 1; j <= n; j++) {
            minv = min(minv, f[i - 1][j]);
            f[i][j] = minv + abs(a[i] - b[j]);
        }
    }
    int res = INF;
    for (int i = 1; i <= n; i++) res = min(res, f[n][i]);
    return res;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)cin >> a[i];
    int res = dp();
    reverse(a + 1, a + 1 + n);
    res = min(res, dp());
    cout << res << endl;
}

int main() {
    solve();
    return 0;
}