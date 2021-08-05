#include <bits/stdc++.h>
using ll = long long;
using namespace std;

const int N = 50010;
int primes[N], cnt;
bool st[N];
int u[N], sum[N];

void sieve(int n) {
    u[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!st[i]) {
            primes[cnt++] = i;
            u[i] = -1;
        }
        for (int j = 0; primes[j] <= n / i; j++) {
            int t = primes[j] * i;
            st[t] = true;
            if (i % primes[j] == 0) {
                u[t] = 0;
                break;
            }
            u[t] = u[i] * -1;
        }
    }
    for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + u[i];
}

void solve() {
    int a, b, d;
    cin >> a >> b >> d;
    a /= d, b /= d;
    ll res = 0;
    int n = min(a, b);
    for (int l = 1, r; l <= n; l = r + 1) {
        r = min(n, min(a / (a / l), b / (b / l)));
        res += (sum[r] - sum[l - 1]) * 1ll * (a / l) * (b / l);
    }
    cout << res << endl;
}

int main() {
    sieve(N - 1);
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}