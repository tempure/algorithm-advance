#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 50010;
int primes[N], cnt, mu[N], sum[N]; //mu is mobius function, sum[] is the prefix sum of mu[]
bool st[N]; //for linear sieve

void init() { //pre calc mobius function value and its sum
    mu[1] = 1; // (-1)^0
    for (int i = 2; i < N; i++) {
        if (!st[i]) primes[cnt++] = i, mu[i] = -1;
        for (int j = 0; primes[j] *i < N; j++) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
            mu[primes[j] * i] = -mu[i];
        }
    }
    for (int i = 1; i < N; i++) sum[i] = sum[i - 1] + mu[i];
}

int g(int k, int x) {
    return k / (k / x);
}

ll f(int a, int b, int k) {
    a = a / k, b = b / k;
    ll res = 0;
    int n = min(a, b);
    for (int l = 1, r; l <= n; l = r + 1) {  // l is d', enume d', when d' > min(a,b), the f(n) will be zero
        r = min(n, min(g(a, l), g(b, l)));
        res += 1ll * (sum[r] - sum[l - 1]) * (a / l) * (b / l);
    }
    return res;
}

// 太卡常了，用 main + while(t--) solve(), 居然 tle，而且必须要用 scanf
int main() {
    init();
    int T;
    scanf("%d", &T);
    while (T -- ) {
        int a, b, c, d, k;
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        printf("%lld\n", f(b, d, k) - f(a - 1, d, k) - f(b, c - 1, k) + f(a - 1, c - 1, k));
    }
    return 0;
}