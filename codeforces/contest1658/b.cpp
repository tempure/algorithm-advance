#include <bits/stdc++.h>
using namespace std;

//神秘结论数学题 我真的服
//https://codeforces.com/blog/entry/101302

const int MOD = 998244353;

void solve() {
    int n; cin >> n;
    if (n & 1) {
        cout << "0\n";
        return;
    }
    long long ans = 1;
    for (int i = 1; i <= n / 2; ++i) {
        ans *= 1LL * i * i % MOD;
        ans %= MOD;
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}