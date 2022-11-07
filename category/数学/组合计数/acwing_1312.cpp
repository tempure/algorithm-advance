#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
mt19937 mrand(random_device{}());
const ll mod = 1000000007;
int rnd(int x) { return mrand() % x;}
ll mulmod(ll a, ll b) {ll res = 0; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = (res + a) % mod; a = 2 * a % mod;} return res;}
ll powmod(ll a, ll b) {ll res = 1; a %= mod; assert(b >= 0); for (; b; b >>= 1) {if (b & 1)res = res * a % mod; a = a * a % mod;} return res;}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a;}
//snippet-head

// https://www.acwing.com/solution/content/8867/  详细的题解
//答案就是C(r-l+n+1, r-l+1) - 1 再取模

const int p = 1e6 + 3; //质数

ll qmi(ll a, ll b) {
    ll res = 1; a %= p;
    while (b) {
        if (b & 1) res = res * a % p;
        b >>= 1;
        a = a * a % p;

    }
    return res;
}

int c(int a, int b) { //逆元求组合数
    // return res;
    if (a < b) return 0; //不管为了正确性还是时间来说都请加上这句话
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
    int t; cin >> t;
    while (t --) {
        int n, l, r;
        cin >> n >> l >> r;
        cout << ((lucas(r - l + n + 1, r - l + 1) - 1) % p + p) % p << endl;
    }
    return 0;
}