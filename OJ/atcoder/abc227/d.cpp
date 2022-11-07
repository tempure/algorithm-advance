#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
#define x first
#define y second
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

//https://atcoder.jp/contests/abc227/editorial/2919

const int N = 2e5 + 10;
ll a[N];

void solve() {
    ll n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    ll l = 0, r = 1e18 / k; //注意二分右边界，要 /k 才是可以安排的project总数
    while (l < r) {
        ll sum = 0;
        ll mid = (l + r + 1) >> 1;
        for (int i = 0; i < n; i++) sum += min(a[i], mid);
        if (k * mid <= sum) l = mid;
        else r = mid - 1;
    }
    cout << l << endl;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}