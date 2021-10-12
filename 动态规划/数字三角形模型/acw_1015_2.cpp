#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int f[N][N];
int a[N][N];
int n, m;

void solve() {
    memset(f, 0xcf, sizeof f);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    f[1][1] = a[1][1];
    for (int i = 2; i <= m; i++) f[1][i] = a[1][i] + f[1][i - 1];
    for (int i = 2; i <= n; i++) f[i][1] = a[i][1] + f[i - 1][1];

    for (int i = 2; i <= n; i++)
        for (int j = 2; j <= m; j++)
            f[i][j] = a[i][j] + max(f[i - 1][j], f[i][j - 1]);

    cout << f[n][m] << endl;

}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}