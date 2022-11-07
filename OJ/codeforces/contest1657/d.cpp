#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define fi first
#define se second
#define endl '\n'
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
//head

//https://codeforces.com/contest/1657/submission/150494087

//出什么模拟题？有病吧。。。。

using i64 = long long;
void solve() {
    int n, C;
    std::cin >> n >> C;

    std::vector<i64> f(C + 1);
    for (int i = 0; i < n; i++) {
        int c, d, h;
        std::cin >> c >> d >> h;
        f[c] = std::max(f[c], 1LL * d * h);
    }

    for (int i = 1; i <= C; i++) {
        for (int j = 2 * i; j <= C; j += i) {
            f[j] = std::max(f[j], f[i] * (j / i));
        }
    }

    for (int i = 1; i <= C; i++) {
        f[i] = std::max(f[i - 1], f[i]);
    }

    int m;
    std::cin >> m;

    for (int i = 0; i < m; i++) {
        int d;
        i64 h;
        std::cin >> d >> h;

        int j = std::upper_bound(f.begin(), f.end(), d * h) - f.begin();
        if (j > C) {
            j = -1;
        }
        std::cout << j << " \n"[i == m - 1];
    }
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}