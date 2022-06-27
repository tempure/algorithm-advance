#include<bits/stdc++.h>
using namespace std;

const long long mod = 10000000000;

//大数求快速幂取模技巧
//https://blog.csdn.net/pfccWang/article/details/78136359
//ans = 9110846700

long long fexp(long long x, long long y) {
    long long ans = 1;
    while (y) {
        if (y & 1) {
            ans = ans * (x / 13331) % mod * 13331 + ans * (x % 13331);
            ans = ans % mod;
        }
        x = x * (x / 13331) % mod * 13331 + x * (x % 13331);
        x %= mod;
        y >>= 1;
    }
    return ans;
}

int main() {
    long long n = 1000;
    long long ans = 0;
    for (long long i = 1; i <= n; i++) {
        ans += fexp(i, i);
        ans %= mod;
    }
    cout << ans << endl;
    return 0;
}