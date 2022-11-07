//预处理逆元模素数求组合数是O(N)的，N是组合数C(N,M)的N
//卢卡斯是O(P*logM)的，P是模的素数 注意题目范围使用


//题解：https://www.acwing.com/solution/content/8867/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int p = 1e6 + 3; //mod

ll qmi(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

ll C(int a, int b) {
    if (a < b) return 0;
    int down = 1, up = 1;
    for (int i = a, j = 1; j <= b; i --, j++) {
        down = 1ll * down * j % p;
        up = 1ll * up * i % p;
    }
    return 1ll * up * qmi(down, p - 2) % p;
}

ll lucas(ll a, ll b) { //递归求lucas
    if (a < p && b < p) return C(a, b);
    return C(a % p, b % p) * lucas(a / p, b / p) % p;
}

void solve() {
    int n, l, r;
    cin >> n >> l >> r;
    cout << ((lucas(r - l + n + 1, r - l + 1) - 1) % p + p) % p << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t -- ) solve();
    return 0;
}