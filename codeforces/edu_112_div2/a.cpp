#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void solve() {
    ll n;
    cin >> n;
    ll res = 0;
    res = (ll)n * (2.5);
    if (res % 10 > 5) res += (10 - res % 10);
    if (res % 10 > 0 && res % 10 < 5) res += (5 - res % 10);
    if (n < 6) res = 15;
    cout << res << endl;
}

int main() {
    int t;
    cin  >> t;
    while (t --) solve();
    return 0;
}