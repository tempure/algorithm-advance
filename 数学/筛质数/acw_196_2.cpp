#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 10;
int primes[N], cnt;
bool v[N];

/*
每个数x必然存在一个<=sqrt(x)的质因子，所以每个合数x都可以用sqrt(x)内的质因子来筛掉
所以可以用sqrt(INT_MAX)内的质数筛掉所有int范围内的质数，也就是埃氏筛的思路

所以对于每个询问[l,r]，从小到大枚举素数，然后删去这个区间内所有该素数的倍数
假设当前枚举素数是p,第一个比l大的且是p的倍数的数是 ceil(l/p) * p, 也就是 (l + p - 1) / p * p (小技巧)
一个坑是注意不要不要筛p，因为p是p的倍数，而且p是素数，所以要从2*p开始筛，取个max
*/

void sieve(int n) {
    memset(v, 0, sizeof v);
    for (int i = 2; i <= n; i++) {
        if (!v[i]) primes[cnt++] = i;
        for (int j = 0; 1ll * primes[j] * i <= n; j++) {
            v[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

void solve() {
    int l, r;
    while (cin >> l >> r) {
        sieve(50000); //复用了 primes数组 每次要筛一次，也可以没必要，新开一个数组记录[l,r]区间内的素数
        memset(v, 0, sizeof v);
        for (int i = 0; i < cnt; i++) {
            ll p = primes[i];
            for (ll j = max(p * 2, (l + p - 1) / p * p); j <= r; j += p)
                v[j - l] = true;
        }
        cnt = 0;
        for (int i = 0; i <= r - l; i++)
            if (!v[i] && i + l >= 2) primes[cnt++] = i + l; //特判1不是素数
        if (cnt < 2) puts("There are no adjacent primes.");
        else {
            int minp = 0, maxp = 0;
            for (int i = 0; i + 1 < cnt; i++) {
                int d = primes[i + 1] - primes[i];
                if (d < primes[minp + 1] - primes[minp]) minp = i;
                if (d > primes[maxp + 1] - primes[maxp]) maxp = i;
            }
            printf("%d,%d are closest, %d,%d are most distant.\n", primes[minp], primes[minp + 1], primes[maxp], primes[maxp + 1]);
        }
    }
}

int main() {
    solve();
    return 0;
}