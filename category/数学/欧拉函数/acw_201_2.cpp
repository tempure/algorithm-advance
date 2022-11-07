#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1010;
int n;
int primes[N], cnt;
int phi[N];
int kase = 1;
bool v[N];

void euler(int n) {
    memset(v, 0, sizeof v);
    cnt = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!v[i]) {
            primes[cnt++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; primes[j] <= n / i; j++) {
            int t = primes[j] * i;
            v[t] = 1;
            if (i % primes[j] == 0) {
                phi[t] = phi[i] * primes[j];
                break;
            }
            phi[t] = phi[i] * (primes[j] - 1);
        }
    }
}

void solve() {
    cin >> n;
    euler(n);
    ll res = 0;
    for (int i = 2; i <= n; i++) res += phi[i];
    res = 3 + 2 * res;
    printf("%d %d %lld\n", kase++, n, res);
}

int main() {
    int t;
    cin >> t;
    while (t --) solve();
    return 0;
}