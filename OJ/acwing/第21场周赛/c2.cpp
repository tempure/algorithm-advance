#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//较好的题解：https://www.acwing.com/solution/content/70457/

ll phi(ll c) {
    ll res = c;
    for (int i = 2; i <= c / i; i++)
        if (c % i == 0) {
            while (c % i == 0) c /= i;
            res = res / i * (i - 1);
        }
    if (c > 1) res  = res / c * (c - 1);
    return res;
}

void solve() {
    ll a, m;
    cin >> a >> m;
    m /= __gcd(a, m);
    cout << phi(m) << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}