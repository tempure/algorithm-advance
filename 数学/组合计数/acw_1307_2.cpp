#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, mod = 5000011;
int f[N];

void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= k + 1; i++) f[i] = i + 1;
    for (int i = k + 2; i <= n; i++)
        f[i] = (f[i - 1] + f[i - k - 1]) % mod;
    cout << f[n] << endl;
}

int main() {
    solve();
    return 0;
}