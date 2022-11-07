#include <bits/stdc++.h>
using namespace std;

void solve() {
    int a, b, c, m;
    cin >> a >>  b >> c >> m;
    int other = a + b + c - max({a, b, c});
    int L = a + b + c - 1 - 2 * other;
    int R = a - 1 + b - 1 + c - 1;
    cout << (L <= m && m <= R ? "YES" : "NO") << '\n';
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}