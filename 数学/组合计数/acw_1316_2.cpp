#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
注意题解枚举1～2*n 的时候是每个数都必然安排位置，也就是当前数前面的数全部安排完了
*/

const int N = 2e6 + 10;
ll p;
int n;
int primes[N], cnt;
bool st[N];

void sieve(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int get(int n, int p) {
    int res = 0;
    while (n) {
        res += n / p;
        n /= p;
    }
    return res;
}

ll C(int x, int y) {
    ll res = 1;
    for (int i = 0; i < cnt; i++) {
        int pi = primes[i];
        int s = get(x, pi) - get(y, pi) - get(x - y, pi);
        while (s --) res = res * pi % p;
    }
    return res;
}

void solve() {
    cin >> n;
    sieve(2 * n);
    cin >> p;
    cout << (C(n * 2, n) - C(n * 2, n - 1) % p + p) % p << endl;
}

int main() {
    solve();
    return 0;
}