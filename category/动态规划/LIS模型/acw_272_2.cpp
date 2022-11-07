#include <bits/stdc++.h>
using namespace std;

/* 2021 10.14 update
I still can't understand it well ... it's difficult to know why this dp is right...

f[i][j]: a[](1~i) b[](1~j) LCIS

1. a[j] == b[j], choose a[i] -> because a[i]==b[j], so consider penultimate position f[i-1][k], k is from 1~j-1
2. a[i] != b[j], don't choose a[i] -> f[i-1][j]
*/

const int N = 3010;
int a[N], f[N][N], b[N];
int n;

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    for (int i = 1; i <= n; i++) {
        int maxv = 1;
        for (int j = 1; j <= n; j++) {
            f[i][j] = f[i - 1][j];
            if (a[i] == b[j]) f[i][j] = max(f[i][j], maxv);
            if (b[j] < a[i]) maxv = max(maxv, f[i - 1][j] + 1);
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) res = max(res, f[n][i]);
    cout << res << endl;
}

int main() {
    solve();
    return 0;
}