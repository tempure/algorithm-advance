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

//https://atcoder.jp/contests/abc245/editorial/3659
//推公式题 感觉不是很懂代码细节啊。。。。
//不太喜欢这种恶心人的题啊。。。。

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int>a(n + 1), b(m + 1), c(n + m + 1);
    for (int i = 0; i <= n; i++)cin >> a[i];
    for (int i = 0; i <= n + m; i++)cin >> c[i];
    for (int i = m; i >= 0; i--) {
        b[i] = c[i + n] / a[n];
        for (int j = 0; j <= n; j++)c[i + j] -= b[i] * a[j];
    }
    for (int i = 0; i < m; i++)cout << b[i] << " ";
    cout << b[m] << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}