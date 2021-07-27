#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
值得思考的是当 n 不能整除p的时候，其实本质上是n往下减直到能整除p的那个数开始算
因为除是下取整，所以对于枚举的每个p，都不一定是n整除的数，而是能整除p的那个数和其互素的数的结果
*/

const int N = 1e7 + 10;
int n;
int primes[N], cnt;
int phi[N];
ll s[N];
bool v[N];

void get_euler(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!v[i]) {
            primes[cnt++] = i;
            phi[i] = i - 1;
        }

        for (int j = 0; primes[j] * i <= n; j++) {
            int t = primes[j] * i;
            v[t] = 1;
            if (i % primes[j] == 0) {
                phi[t] = phi[i] * primes[j];
                break;
            }
            phi[t] = phi[i] * (primes[j] - 1);
        }
    }
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + phi[i];
}

void solve() {
    cin >> n;
    get_euler(n);
    ll res = 0;
    for (int i = 0; i < cnt; i++) {
        int p = primes[i];
        res += s[n / p] * 2 - 1;
    }
    cout << res << endl;
}

int main() {
    solve();
    return 0;
}