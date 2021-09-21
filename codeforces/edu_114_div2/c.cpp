#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define um unordered_map
#define pq priority_queue
#define sz(x) ((int)(x).size())
// #define x first
// #define y second
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


// this problem use cin without disbale sync will TLE lol...

const int N = 2e5 + 10;
ll a[N];
ll sum;
int n, m;

void solve() {
    set<ll> s;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
        s.insert(a[i]);
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        ll x, y;
        cin >> x >> y;
        ll mn = 2e18;
        auto it = s.lower_bound(x);
        if (it != s.end()) mn = max(0ll, y - (sum - *it));
        // thins the case that x is 3 and y = 1e18
        //and you have 1 1 1e6, 1e7
        if (it != s.begin()) {
            it --;
            mn = min(mn, x - *it + max(0ll, y - (sum - *it)));
        }
        cout << mn << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t --) solve();
    return 0;
}