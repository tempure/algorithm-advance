#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 50010;
int primes[N], cnt, mu[N], sum[N], h[N];
bool st[N];

int g(int k, int x) {
    return k / (k / x);
}

void init() {
    mu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!st[i]) primes[cnt++] = i, mu[i] = -1;
        for (int j = 0; primes[j] * i < N; j++) {
            st[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
            mu[i * primes[j]] = -mu[i];
        }
    }
    for (int i = 1; i < N; i++) sum[i] = sum[i - 1] + mu[i];
    for (int i = 1; i < N; i++) {
        for (int l = 1, r; l <= i; l = r + 1) {
            r = min(i, g(i, l));
            h[i] += (r - l + 1) * (i / l);
        }
    }
}


int main() {
    init();
    int t;
    cin >> t;
    while (t --) {
        int n, m;
        scanf("%d%d", &n, &m);
        ll res = 0;
        int k = min(n, m);
        for (int l = 1, r; l <= k; l = r + 1) {
            r = min(k, min(g(n, l), g(m, l)));
            res += 1ll * (sum[r] - sum[l - 1]) * h[n / l] * h[m / l];
        }
        printf("%lld\n", res);
    }
    return 0;
}