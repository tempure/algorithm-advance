#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;

/*
化简+阶乘分解
分解之后次幂数直接计算约数个数即可
*/

const int N = 1e6 + 10;
int primes[N], cnt;
bool v[N];

void sieve(int n) {
    for (int i = 2; i <= n; i++) {
        if (!v[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++) {
            v[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

void solve() {
    int n;
    cin >> n;
    sieve(n);
    ll res = 1;
    for (int i = 0; i < cnt ; i++) {
        int p = primes[i];
        int s = 0;
        for (int j = n; j; j /= p) s += j /  p;
        res = res * (2 * s + 1) % mod;
    }
    cout << res << endl;
}

int main() {
    solve();
    return 0;
}