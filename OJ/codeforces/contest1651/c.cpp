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

//https://www.bilibili.com/video/BV1U3411W7uj
//https://codeforces.com/contest/1651/submission/149117381

/*
不存在割点， 要处理的就是拐角的4个点必须有2个出边才行
上下枚举一遍，然后和只连2条边，就是最左边上下 最右边上下
以及三条边，以及四条边的连法取min即可
*/

constexpr int inf = 1E9;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }

    int ans = std::min(std::abs(a[0] - b[0]) + std::abs(a[n - 1] - b[n - 1]),
                       std::abs(a[0] - b[n - 1]) + std::abs(a[n - 1] - b[0]));

    int a0 = inf, b0 = inf, a1 = inf, b1 = inf;
    for (int i = 0; i < n; i++) {
        a0 = std::min(a0, std::abs(a[0] - b[i]));
        a1 = std::min(a1, std::abs(a[n - 1] - b[i]));
        b0 = std::min(b0, std::abs(b[0] - a[i]));
        b1 = std::min(b1, std::abs(b[n - 1] - a[i]));
    }

    ans = std::min({1LL * ans, 1LL * std::abs(a[0] - b[0]) + a1 + b1,
                    1LL * std::abs(a[0] - b[n - 1]) + a1 + b0,
                    1LL * std::abs(a[n - 1] - b[0]) + a0 + b1,
                    1LL * std::abs(a[n - 1] - b[n - 1]) + a0 + b0
                   });

    ans = std::min(1LL * ans, 1LL * a0 + a1 + b0 + b1);

    std::cout << ans << "\n";
}

int main() {
    int t = 1;
    cin >> t;
    while (t --) solve();
    return 0;
}