#include <iostream>
#include <algorithm>
//#pragma GCC optimize(2)
using namespace std;
const int p = 1e9 + 7;
typedef long long ll;

//https://atcoder.jp/contests/abc205/editorial/2080

// lucas求组合数 + 逆元 处理除法
//卡特兰数换参数
//y = x + k
//然后找出非法点关于y = x + k 的对称点
//如果没有y=x+k的限制，有C(m+n,n)条路径，然后减去不合法的即可

ll qmi(ll a, ll b) {
    ll res = 1; a %= p;
    while (b) {
        if (b & 1) res = res * a % p;
        b >>= 1;
        a = a * a % p;

    }
    return res;
}

ll c(int a, int b) {
    //逆元求组合数
    if (a < b) return 0;
    int down = 1, up = 1;
    for (int i = a, j = 1; j <= b; i--, j++) {
        down = (ll)down * j % p;
        up = (ll)up * i % p;
    }
    return (ll)up * qmi(down, p - 2) % p;
}

ll lucas(ll a, ll b) { //递归求lucas
    if (a < p && b < p) return c(a, b);
    return c(a % p, b % p) * lucas(a / p, b / p) % p;
}

int main() {
    // int n; cin >> n;
    int n, m, k;
    cin >> n >> m >> k;
    if (n > m + k) {
        cout << 0 << endl;
        return 0;
    }
    // cout << lucas(2 * n, n) % p * qmi(n + 1, p - 2, p) % p << endl;
    cout << ((lucas(m + n, n) % p - lucas(m + n, m + k + 1) % p) % p + p) % p;
    return 0;
}