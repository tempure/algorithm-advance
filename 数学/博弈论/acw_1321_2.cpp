#include <bits/stdc++.h>
using namespace std;

const int N = 55, M = 50060;
int f[N][M];

int dp(int a, int b) {
    int &v = f[a][b];
    if (v != -1) return v;
    if (!a) return b % 2;
    if (b == 1) return dp(a + 1, 0);

    if (a && !dp(a - 1, b)) return v = 1;
    if (b && !dp(a, b - 1)) return v = 1;
    if (a >= 2 && !dp(a - 2, b + (b ? 3 : 2))) return v = 1;
    if (a && b && !dp(a - 1, b + 1)) return v = 1;

    return v = 0;
}

void solve() {
    // memset(f, -1, sizeof f);
    int n;
    scanf("%d", &n);
    int a = 0, b = 0;
    for (int i = 0; i < n ; i++) {
        int x;
        scanf("%d", &x);
        if (x == 1) a ++;
        else b += b ? x + 1 : x;
    }
    if (dp(a, b)) puts("YES");
    else puts("NO");
}

int main() {
    memset(f, -1, sizeof f);
    int t = 1;
    scanf("%d", &t);
    while (t --) solve();
    return 0;
}
